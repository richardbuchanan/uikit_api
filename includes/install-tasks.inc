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
 * @param boolean $success
 *   Returns true if the batch operations were successfully run, otherwise
 *   returns false.
 * @param array $results
 *   Contains the results from successfully processed batch operations.
 * @param array $operations
 *   Contains the operations that remain unprocessed.
 */
function uikit_api_finished($success, $results, $operations) {
  if ($success) {
    drupal_cron_run();
    $old_msg = drupal_get_messages();
    drupal_set_message(t('<p>The UIkit API project and default settings for the API module have been configured for you. You can add additional <a href="/admin/config/development/api">projects/branchs/references.</a></p><p>It is also recommended to <a href="/admin/config/development/api/php_branches/new_api">add a new API reference branch</a> for Drupal if you do not plan to add locally stored Drupal code. This will turn Drupal functions/hooks/etc. into links to api.drupal.org.</p>'));
  }
  else {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
    drupal_set_message($message, 'error');
  }
}
