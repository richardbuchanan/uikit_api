<?php

/**
 * @file
 * Common get functions.
 */

use \Drupal\uikit\UIkit;

/**
 * Retrieves UIkit, jQuery, jQuery Migrate and Font Awesome CDN assets.
 */
function uikit_get_cdn_assets() {
  // Add the UIkit stylesheet.
  drupal_add_css('//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . '/css/uikit.min.css', array(
    'type' => 'external',
    'group' => CSS_THEME,
    'every_page' => TRUE,
    'weight' => -100,
    'version' => UIkit::UIKIT_LIBRARY_VERSION,
  ));

  // Add the jQuery script.
  drupal_add_js('//cdnjs.cloudflare.com/ajax/libs/jquery/' . UIkit::UIKIT_JQUERY_VERSION . '/jquery.min.js', array(
    'type' => 'external',
    'group' => JS_THEME,
    'every_page' => TRUE,
    'weight' => -20,
    'version' => UIkit::UIKIT_JQUERY_VERSION,
  ));

  // Add the jQuery Migrate script so we can use multiple jQuery versions
  // simultaneously.
  drupal_add_js('//cdnjs.cloudflare.com/ajax/libs/jquery-migrate/' . UIkit::UIKIT_JQUERY_MIGRATE_VERSION . '/jquery-migrate.min.js', array(
    'type' => 'external',
    'group' => JS_THEME,
    'every_page' => TRUE,
    'weight' => -20,
    'version' => UIkit::UIKIT_JQUERY_MIGRATE_VERSION,
  ));

  // Add the UIkit script.
  drupal_add_js('//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . '/js/uikit.min.js', array(
    'type' => 'external',
    'group' => JS_THEME,
    'every_page' => TRUE,
    'weight' => -20,
    'version' => UIkit::UIKIT_LIBRARY_VERSION,
  ));

  // Add the UIkit icons script.
  drupal_add_js('//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . '/js/uikit-icons.min.js', array(
    'type' => 'external',
    'group' => JS_THEME,
    'every_page' => TRUE,
    'weight' => -20,
    'version' => UIkit::UIKIT_LIBRARY_VERSION,
  ));
}

/**
 * Checks whether the given path is the current path.
 *
 * @param string $path
 *   The path to check against the current path.
 *
 * @return bool
 *   Returns true if the given path is the current path, false if otherwise.
 */
function uikit_get_active_path($path) {
  $active_path = FALSE;

  // Checks if the path is the current page.
  $current_page = $path == $_GET['q'];

  // Checks if the path and current page are the front page.
  $front_page = $path == '<front>' && drupal_is_front_page();

  // Checks if the path and current page are both a user page.
  $exploded_path = explode('/', $_GET['q']);
  $user_page = is_array($exploded_path) && $exploded_path[0] == 'user' && $exploded_path[0] == $path;

  // Change $active_path to true if the given path is the current path.
  if ($current_page || $front_page || $user_page) {
    $active_path = TRUE;
  }

  return $active_path;
}
