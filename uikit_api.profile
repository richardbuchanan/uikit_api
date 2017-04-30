<?php

/**
 * @file
 * Enables modules and site configuration for the uikit_api profile.
 */

/**
 * Implements hook_install_tasks_alter().
 *
 * Allows changing or removing steps from the install process. For example, if
 * you are building an install profile specifically for sites using a certain
 * language, you might want to remove the localization steps and simply
 * configure the language settings yourself.
 *
 * Takes two parameters: &$tasks and $install_state. The $tasks variable
 * contains a structured array of all installation tasks like the one you
 * returned in hook_install_tasks(). Here are the default tasks, in order, as
 * defined by install_tasks():
 *   - install_select_profile
 *     A configuration page to select which profile to install. It doesn't make
 *     any sense to change this, because by the time your profile gets control,
 *     it will have already been chosen.
 *   - install_select_locale
 *     Allows choosing the language to use in the installer.
 *   - install_load_profile
 *     Loads the selected profile into memory.
 *   - install_verify_requirements
 *     Checks whether the current server meets the correct requirements for
 *     installing Drupal.
 *   - install_settings_form
 *     The form used to configure and rewrite settings.php.
 *   - install_system_module
 *     Installs the system module so that the system can be bootstrapped, and
 *     installs the user module so that sessions can be recorded during
 *     bootstrap.
 *   - install_bootstrap_full
 *     Does a full bootstrap of Drupal, loading all core functions and
 *     resources.
 *   - install_profile_modules
 *     Installs and enables all modules on which the profile depends (as defined
 *     in the .info file), and then runs profilename_install() if it exists
 *     (as defined in the .install file).
 *   - install_import_locales
 *     Import available languages into the system.
 *   - install_configure_form
 *     A form to configure site information and settings.
 *
 * Now any tasks defined by the current installation profile are run. Drupal has
 * already been fully bootstrapped, all required modules are already installed
 * and enabled, and the profile itself has also been "installed," so each task
 * should have access to anything a normal Drupal module would be able to
 * access. The final default tasks to run:
 *   - install_import_locales_remaining
 *     Imports additional languages into the system if any have not yet been
 *     imported.
 *   - install_finished
 *     Performs final installation tasks (like clearing caches) and informs the
 *     user that the installation process is complete.
 */
function uikit_api_install_tasks_alter(&$tasks, $install_state) {
  global $install_state;

  if ($GLOBALS['theme'] != 'docs_admin') {
    unset($GLOBALS['theme']);

    drupal_static_reset();
    $GLOBALS['conf']['maintenance_theme'] = 'docs_admin';
    _drupal_maintenance_theme();
  }

  // Skip the locale selection task during profile installation.
  $tasks['install_select_locale']['display'] = FALSE;
  $tasks['install_select_locale']['run'] = INSTALL_TASK_SKIP;
  $install_state['parameters']['locale'] = 'en';
}

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 */
function uikit_api_form_install_configure_form_alter(&$form, $form_state) {
  drupal_set_title(st('Configure UIkit for Drupal API site'));

  // Format a description for the site information field to better describe what
  // has been pre-populated.
  $description = st('<p>The site name, administrator account username and email notification values have been set for easy installation. Change these values to suit your needs.</p>');

  // Pre-populate form values for easy installation.
  $form['site_information']['#description'] = $description;
  $form['site_information']['site_name']['#default_value'] = st('UIkit for Drupal API');
  $form['admin_account']['account']['name']['#default_value'] = st('Administrator');
  $form['update_notifications']['update_status_module']['#default_value'] = array(1, 0);
}

/**
 * Form constructor to configure the UIkit project.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form. The arguments that
 *   drupal_get_form() was originally called with are available in the array
 *   $form_state['build_info']['args'].
 *
 * @return array
 *   Returns nested array of form elements.
 */
function _uikit_api_project_form($form, &$form_state) {
  drupal_set_title(st('Configure UIkit Project'));

  // Load api.admin.inc from the api module.
  module_load_include('inc', 'api', 'api.admin');

  // Construct $form from the api module's api_project_edit_form().
  $form = drupal_get_form('api_project_edit_form');

  // Alter form elements to pre-populate the form values.
  $form['uikit_api'] = array(
    '#type' => 'fieldset',
    '#title' => st('Create UIkit project'),
    '#description' => st('<p>This will create the UIkit project. You are free to change the title of the project, while the other values have been preset for you.</p>'),
    '#weight' => -100,
  );
  $form['project_name']['#value'] = 'uikit';
  $form['project_name']['#disabled'] = TRUE;
  $form['project_title']['#value'] = 'UIkit';
  $form['project_type']['#value'] = 'theme';
  $form['project_type']['#disabled'] = TRUE;
  $form['submit']['#value'] = st('Save and continue');

  return $form;
}

/**
 * Form constructor to configure the UIkit 7.x-2.x branch.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form. The arguments that
 *   drupal_get_form() was originally called with are available in the array
 *   $form_state['build_info']['args'].
 *
 * @return array
 *   Returns nested array of form elements.
 */
function _uikit_7x_2x_api_branch_form($form, &$form_state) {
  drupal_set_title(st('Configure UIkit 7.x-2.x Branch'));

  // Get path to the uikit_api profile.
  $profile_path = drupal_get_path('profile', drupal_get_profile());

  // Load api.admin.inc from the api module.
  module_load_include('inc', 'api', 'api.admin');

  // Construct $form from the api module's api_branch_edit_form().
  $form = drupal_get_form('api_branch_edit_form');

  // Alter form elements to pre-populate the form values.
  $form['uikit_api'] = array(
    '#type' => 'fieldset',
    '#title' => st('Create UIkit 7.x-2.x branch'),
    '#description' => st('<p>This will create a 7.x-2.x branch for the UIkit project. Preset values have been disabled, but you are free to make changes to the rest.</p>'),
    '#weight' => -100,
  );
  $form['project']['#value'] = 'uikit';
  $form['project']['#disabled'] = TRUE;
  $form['core_compatibility']['#value'] = '7.x';
  $form['core_compatibility']['#disabled'] = TRUE;
  $form['preferred']['#value'] = 1;
  $form['preferred']['#disabled'] = TRUE;
  $form['branch_name']['#value'] = '7.x-2.x';
  $form['branch_name']['#disabled'] = TRUE;
  $form['title']['#value'] = 'UIkit 7.x-2.x';
  $form['data']['directories']['#value'] = "$profile_path/sources/uikit-7.x-2.x";
  $form['data']['directories']['#value'] .= PHP_EOL . "$profile_path/documentation/uikit-7.x-2.x";
  $form['data']['directories']['#disabled'] = TRUE;
  $form['update_frequency']['#value'] = 604800;
  $form['update_frequency']['#disabled'] = TRUE;
  $form['submit']['#value'] = st('Save and continue');

  return $form;
}

/**
 * Form constructor to configure the UIkit 7.x-3.x branch.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form. The arguments that
 *   drupal_get_form() was originally called with are available in the array
 *   $form_state['build_info']['args'].
 *
 * @return array
 *   Returns nested array of form elements.
 */
function _uikit_7x_3x_api_branch_form($form, &$form_state) {
  drupal_set_title(st('Configure UIkit 7.x-3.x Branch'));

  // Get path to the uikit_api profile.
  $profile_path = drupal_get_path('profile', drupal_get_profile());

  // Load api.admin.inc from the api module.
  module_load_include('inc', 'api', 'api.admin');

  // Construct $form from the api module's api_branch_edit_form().
  $form = drupal_get_form('api_branch_edit_form');

  // Alter form elements to pre-populate the form values.
  $form['uikit_api'] = array(
    '#type' => 'fieldset',
    '#title' => st('Create UIkit 7.x-3.x branch'),
    '#description' => st('<p>This will create a 7.x-3.x branch for the UIkit project. Preset values have been disabled, but you are free to make changes to the rest.</p>'),
    '#weight' => -100,
  );
  $form['project']['#value'] = 'uikit';
  $form['project']['#disabled'] = TRUE;
  $form['core_compatibility']['#value'] = '7.x';
  $form['core_compatibility']['#disabled'] = TRUE;
  $form['preferred']['#value'] = 0;
  $form['preferred']['#disabled'] = TRUE;
  $form['branch_name']['#value'] = '7.x-3.x';
  $form['branch_name']['#disabled'] = TRUE;
  $form['title']['#value'] = 'UIkit 7.x-3.x';
  $form['data']['directories']['#value'] = "$profile_path/sources/uikit-7.x-3.x";
  $form['data']['directories']['#value'] .= PHP_EOL . "$profile_path/documentation/uikit-7.x-3.x";
  $form['data']['directories']['#disabled'] = TRUE;
  $form['update_frequency']['#value'] = 604800;
  $form['update_frequency']['#disabled'] = TRUE;
  $form['submit']['#value'] = st('Save and continue');

  return $form;
}

/**
 * Form constructor to configure the UIkit 8.x-2.x branch.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form. The arguments that
 *   drupal_get_form() was originally called with are available in the array
 *   $form_state['build_info']['args'].
 *
 * @return array
 *   Returns nested array of form elements.
 */
function _uikit_8x_2x_api_branch_form($form, &$form_state) {
  drupal_set_title(st('Configure UIkit 8.x-2.x Branch'));

  // Get path to the uikit_api profile.
  $profile_path = drupal_get_path('profile', drupal_get_profile());

  // Load api.admin.inc from the api module.
  module_load_include('inc', 'api', 'api.admin');

  // Construct $form from the api module's api_branch_edit_form().
  $form = drupal_get_form('api_branch_edit_form');

  // Alter form elements to pre-populate the form values.
  $form['uikit_api'] = array(
    '#type' => 'fieldset',
    '#title' => st('Create UIkit 8.x-2.x branch'),
    '#description' => st('<p>This will create a 8.x-2.x branch for UIkit project. Preset values have been disabled, but you are free to make changes to the rest.</p>'),
    '#weight' => -100,
  );
  $form['project']['#value'] = 'uikit';
  $form['project']['#disabled'] = TRUE;
  $form['core_compatibility']['#value'] = '8.x';
  $form['core_compatibility']['#disabled'] = TRUE;
  $form['preferred']['#value'] = 1;
  $form['preferred']['#disabled'] = TRUE;
  $form['branch_name']['#value'] = '8.x-2.x';
  $form['branch_name']['#disabled'] = TRUE;
  $form['title']['#value'] = 'UIkit 8.x-2.x';
  $form['data']['directories']['#value'] = "$profile_path/sources/uikit-8.x-2.x";
  $form['data']['directories']['#value'] .= PHP_EOL . "$profile_path/documentation/uikit-8.x-2.x";
  $form['data']['directories']['#disabled'] = TRUE;
  $form['update_frequency']['#value'] = 604800;
  $form['update_frequency']['#disabled'] = TRUE;
  $form['submit']['#value'] = st('Save and continue');

  return $form;
}

/**
 * Form constructor to configure the UIkit 8.x-3.x branch.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form. The arguments that
 *   drupal_get_form() was originally called with are available in the array
 *   $form_state['build_info']['args'].
 *
 * @return array
 *   Returns nested array of form elements.
 */
function _uikit_8x_3x_api_branch_form($form, &$form_state) {
  drupal_set_title(st('Configure UIkit 8.x-3.x Branch'));

  // Get path to the uikit_api profile.
  $profile_path = drupal_get_path('profile', drupal_get_profile());

  // Load api.admin.inc from the api module.
  module_load_include('inc', 'api', 'api.admin');

  // Construct $form from the api module's api_branch_edit_form().
  $form = drupal_get_form('api_branch_edit_form');

  // Alter form elements to pre-populate the form values.
  $form['uikit_api'] = array(
    '#type' => 'fieldset',
    '#title' => st('Create UIkit 8.x-3.x branch'),
    '#description' => st('<p>This will create a 8.x-2.x branch for UIkit project. Preset values have been disabled, but you are free to make changes to the rest.</p>'),
    '#weight' => -100,
  );
  $form['project']['#value'] = 'uikit';
  $form['project']['#disabled'] = TRUE;
  $form['core_compatibility']['#value'] = '8.x';
  $form['core_compatibility']['#disabled'] = TRUE;
  $form['preferred']['#value'] = 0;
  $form['preferred']['#disabled'] = TRUE;
  $form['branch_name']['#value'] = '8.x-3.x';
  $form['branch_name']['#disabled'] = TRUE;
  $form['title']['#value'] = 'UIkit 8.x-3.x';
  $form['data']['directories']['#value'] = "$profile_path/sources/uikit-8.x-3.x";
  $form['data']['directories']['#value'] .= PHP_EOL . "$profile_path/documentation/uikit-8.x-3.x";
  $form['data']['directories']['#disabled'] = TRUE;
  $form['update_frequency']['#value'] = 604800;
  $form['update_frequency']['#disabled'] = TRUE;
  $form['submit']['#value'] = st('Save and continue');

  return $form;
}

/**
 * Form constructor to configure the UIkit project stats.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form. The arguments that
 *   drupal_get_form() was originally called with are available in the array
 *   $form_state['build_info']['args'].
 *
 * @return array
 *   Returns nested array of form elements.
 */
function _uikit_project_stats_form($form, &$form_state) {
  drupal_set_title(st('Configure UIkit Project Stats'));

  // Load api.admin.inc from the api module.
  module_load_include('inc', 'projectstats', 'projectstats.admin');

  // Construct $form from the projectstats module's projectstats_form().
  $form = drupal_get_form('projectstats_form');

  // Alter form elements to pre-populate the form values.
  $form['uikit_api'] = array(
    '#type' => 'fieldset',
    '#title' => st('Create UIkit project stats'),
    '#description' => st('<p>This will create project stats for the UIkit project. Preset values have been disabled.</p>'),
    '#weight' => -100,
  );
  $form['full_project_name']['#value'] = 'UIkit';
  $form['full_project_name']['#disabled'] = TRUE;
  $form['short_project_name']['#value'] = 'uikit';
  $form['short_project_name']['#disabled'] = TRUE;

  return $form;
}

/**
 * Batch operations to configure UIkit API.
 */
function _configure_uikit_api() {
  // Create the batch to process during installation.
  $batch = array(
    'operations' => array(
      array('uikit_api_processed', array()),
    ),
    'title' => st('Configuring UIkit API Site'),
    'error_message' => st('The UIkit API configuration has encountered an error.'),
    'file' => drupal_get_path('profile', 'uikit_api') . '/includes/install-tasks.inc',
    'finished' => 'uikit_api_finished',
  );
  return $batch;
}

/**
 * Form constructor to configure the Drupal 7.x reference branch.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form. The arguments that
 *   drupal_get_form() was originally called with are available in the array
 *   $form_state['build_info']['args'].
 *
 * @return array
 *   Returns nested array of form elements.
 */
function _drupal_7x_api_reference_branch_form($form, &$form_state) {
  drupal_set_title(st('Configure Drupal 7.x Reference Branch'));

  // Load api.admin.inc from the api module.
  module_load_include('inc', 'api', 'api.admin');

  // Construct $form from the api module's api_api_branch_edit_form().
  $form = drupal_get_form('api_api_branch_edit_form');

  // Alter form elements to pre-populate the form values.
  $form['drupal_api'] = array(
    '#type' => 'fieldset',
    '#title' => st('Create Drupal 7.x reference branch'),
    '#description' => st('<p>This will create a 7.x reference branch for the Drupal core project. Preset values have been disabled, but you are free to make changes to the rest.</p>'),
    '#weight' => -100,
  );
  $form['title']['#value'] = st('Drupal 7.x');
  $form['data']['url']['#value'] = 'https://api.drupal.org/api/drupal/full_list/7.x';
  $form['data']['url']['#disabled'] = TRUE;
  $form['data']['search_url']['#value'] = 'https://api.drupal.org/api/drupal/7.x/search/';
  $form['data']['search_url']['#disabled'] = TRUE;
  $form['data']['core_compatibility']['#value'] = '7.x';
  $form['data']['core_compatibility']['#disabled'] = TRUE;
  $form['data']['project_type']['#value'] = 'core';
  $form['data']['project_type']['#disabled'] = TRUE;
  $form['data']['page_limit']['#value'] = 2000;
  $form['data']['timeout']['#value'] = 30;
  $form['update_frequency']['#value'] = 604800;
  $form['update_frequency']['#disabled'] = TRUE;
  $form['submit']['#value'] = st('Save and continue');

  return $form;
}

/**
 * Form constructor to configure the Drupal 8.x reference branch.
 *
 * @param array $form
 *   Nested array of form elements that comprise the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form. The arguments that
 *   drupal_get_form() was originally called with are available in the array
 *   $form_state['build_info']['args'].
 *
 * @return array
 *   Returns nested array of form elements.
 */
function _drupal_8x_api_reference_branch_form($form, &$form_state) {
  drupal_set_title(st('Configure Drupal 8.2.x Reference Branch'));

  // Load api.admin.inc from the api module.
  module_load_include('inc', 'api', 'api.admin');

  // Construct $form from the api module's api_api_branch_edit_form().
  $form = drupal_get_form('api_api_branch_edit_form');

  // Alter form elements to pre-populate the form values.
  $form['drupal_api'] = array(
    '#type' => 'fieldset',
    '#title' => st('Create Drupal 8.2.x reference branch'),
    '#description' => st('<p>This will create an 8.2.x reference branch for the Drupal core project. Preset values have been disabled, but you are free to make changes to the rest.</p>'),
    '#weight' => -100,
  );
  $form['title']['#value'] = st('Drupal 8.2.x');
  $form['data']['url']['#value'] = 'https://api.drupal.org/api/drupal/full_list/8.2.x';
  $form['data']['url']['#disabled'] = TRUE;
  $form['data']['search_url']['#value'] = 'https://api.drupal.org/api/drupal/8.2.x/search/';
  $form['data']['search_url']['#disabled'] = TRUE;
  $form['data']['core_compatibility']['#value'] = '8.x';
  $form['data']['core_compatibility']['#disabled'] = TRUE;
  $form['data']['project_type']['#value'] = 'core';
  $form['data']['project_type']['#disabled'] = TRUE;
  $form['data']['page_limit']['#value'] = 2000;
  $form['data']['timeout']['#value'] = 30;
  $form['update_frequency']['#value'] = 604800;
  $form['update_frequency']['#disabled'] = TRUE;
  $form['submit']['#value'] = st('Save and continue');

  return $form;
}
