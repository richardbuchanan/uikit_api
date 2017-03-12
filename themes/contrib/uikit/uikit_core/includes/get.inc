<?php

/**
 * @file
 * Common get functions.
 */

/**
 * Retrieves UIkit CDN assets.
 *
 * @param string $font_awesome_version
 *   The version of Font-Awesome to retrieve.
 * @param string $jquery_version
 *   The version of jQuery to retrieve.
 * @param string $uikit_version
 *   The version of UIkit to retrieve.
 */
function uikit_get_cdn_assets($font_awesome_version = '4.7.0', $jquery_version = '2.1.4', $uikit_version = '2.26.4') {
  global $theme_key;
  $uikit_style = theme_get_setting('base_style', $theme_key);
  $uikit_css = 'uikit.min.css';

  if ($uikit_style == 'customizer-css') {
    $customizer_css = theme_get_setting('customizer_css', $theme_key);
    $file = file_load($customizer_css['fid']);

    drupal_add_css($file->uri, array(
      'group' => CSS_THEME,
      'every_page' => TRUE,
      'weight' => -100,
      'version' => $uikit_version,
    ));
  }
  else {
    switch ($uikit_style) {
      case 'almost-flat':
        $uikit_css = 'uikit.almost-flat.min.css';
        break;

      case 'gradient':
        $uikit_css = 'uikit.gradient.min.css';
        break;
    }

    drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/uikit/$uikit_version/css/$uikit_css", array(
      'type' => 'external',
      'group' => CSS_THEME,
      'every_page' => TRUE,
      'weight' => -100,
      'version' => $uikit_version,
    ));
  }

  drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/font-awesome/$font_awesome_version/css/font-awesome.css", array(
    'type' => 'external',
    'group' => CSS_THEME,
    'every_page' => TRUE,
    'weight' => 0,
    'version' => $font_awesome_version,
  ));

  drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/jquery/$jquery_version/jquery.min.js", array(
    'type' => 'external',
    'group' => JS_THEME,
    'every_page' => TRUE,
    'weight' => -20,
    'version' => $jquery_version,
  ));

  drupal_add_js('//cdnjs.cloudflare.com/ajax/libs/jquery-migrate/1.4.1/jquery-migrate.min.js', array(
    'type' => 'external',
    'group' => JS_THEME,
    'every_page' => TRUE,
    'weight' => -20,
    'version' => '3.0.0',
  ));

  drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/uikit/$uikit_version/js/uikit.min.js", array(
    'type' => 'external',
    'group' => JS_THEME,
    'every_page' => TRUE,
    'weight' => -20,
    'version' => $uikit_version,
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
