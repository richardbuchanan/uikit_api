<?php
/**
 * @file
 * Enables modules and site configuration for a development site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function uikit_api_form_install_configure_form_alter(&$form, $form_state) {
  $form['site_information']['site_name']['#default_value'] = 'UIkit API';
  $form['site_information']['site_mail']['#default_value'] = 'admin@example.com';
  $form['admin_account']['account']['name']['#default_value'] = 'Administrator';
  $form['admin_account']['account']['mail']['#default_value'] = 'admin@example.com';
  $form['server_settings']['site_default_country']['#default_value'] = 'US';
  $form['update_notifications']['update_status_module']['#default_value'] = array(1, 0);
}
