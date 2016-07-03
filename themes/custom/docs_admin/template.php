<?php

/**
 * @file
 * Process theme data for the Docs Admin theme.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_admin_preprocess_maintenance_page(&$variables) {
  $variables['head_title_array']['name'] = t('UIkit API');
}

/**
 * Implements hook_process_HOOK().
 */
function docs_admin_process_maintenance_page(&$variables) {
  $variables['head_title'] = implode(' | ', $variables['head_title_array']);
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_admin_preprocess_button(&$variables) {
  $variables['element']['#attributes']['class'] = array('uk-button');
  $value = $variables['element']['#value'];
  $primary = array(
    'Save and continue',
  );

  if (in_array($value, $primary)) {
    $variables['element']['#attributes']['class'][] = 'uk-button-primary';
  }
}

/**
 * Implements hook_css_alter().
 */
function docs_admin_css_alter(&$css) {
  $docs_admin = drupal_get_path('theme', 'docs_admin');
  $system = drupal_get_path('module', 'system');

  if (isset($css[$system . '/system.theme.css'])) {
    unset($css[$system . '/system.theme.css']);
  }
}

/**
 * Implements hook_js_alter().
 */
function docs_admin_js_alter(&$javascript) {
  $docs_admin = drupal_get_path('theme', 'docs_admin');
  $user = drupal_get_path('module', 'user');

  if (isset($javascript['misc/progress.js'])) {
    $javascript['misc/progress.js']['data'] = $docs_admin . '/js/progress.js';
  }

  if (isset($javascript[$user . '/user.js'])) {
    $javascript[$user . '/user.js']['data'] = $docs_admin . '/js/user.js';
  }
}
