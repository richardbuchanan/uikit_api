<?php

/**
 * @file
 * Process install tasks for the UIkit API development installation profile.
 */

/**
 * Sets variables, resets API branches, and runs cron for API configuration.
 */
function uikit_api_processed() {
  // Set the API module default settings.
  variable_set('api_default_core_compatibility', '7.x');
  variable_set('api_default_project', 'uikit');
  variable_set('api_opensearch_name', 'UIkit API');
  variable_set('api_opensearch_description', 'UIkit API documentation');

  // Re-submit API default settings form to fix branches.
  api_reset_branches();

  // Set the admin theme back to Seven and the front page to the UIkit API.
  variable_set('site_frontpage', 'api/uikit');
}

/**
 * Gets the results from the batch operations.
 *
 * @param bool $success
 *   Returns true if the batch operations were successfully run, otherwise
 *   returns false.
 * @param array $results
 *   Contains the results from successfully processed batch operations.
 * @param array $operations
 *   Contains the operations that remain unprocessed.
 */
function uikit_api_finished($success, $results, $operations) {
  if ($success) {
    // Apply default comment settings to all API pages.
    uikit_api_development_apply_comment_settings();

    // Run cron to parse UIkit theme files.
    drupal_cron_run();

    $old_msg = drupal_get_messages();
    drupal_set_message(t('<p>The UIkit API project and default settings for the API module have been configured for you. You can add additional <a href="/admin/config/development/api">projects/branchs/references.</a></p>'));
  }
  else {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array(
      '%error_operation' => $error_operation[0],
      '@arguments' => print_r($error_operation[1], TRUE),
    ));
    drupal_set_message($message, 'error');
  }
}



/**
 * Applies current default comment settings to existing API nodes.
 */
function uikit_api_development_apply_comment_settings() {
  if (module_exists('comment')) {
    $setting = variable_get('comment_api', 2);
    db_update('node')
      ->condition('type', 'api')
      ->fields(array('comment' => $setting))
      ->execute();
    // This is a query using a WHERE EXISTS, and there is no apparent way
    // to write it using the database API, so use ANSI syntax.
    db_query("UPDATE {node_revision} SET comment = :comment_setting WHERE EXISTS ( SELECT * FROM {node} n WHERE n.type = 'api')", array(':comment_setting' => $setting));
    // Clear the cache so node_load doesn't load old versions.
    entity_get_controller('node')->resetCache();

    // Might as well also make sure that the body field exists for comments.
    if ($setting != 0) {
      $info = (object) array('type' => 'api');
      _comment_body_field_create($info);
    }
  }
}
