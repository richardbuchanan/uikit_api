<?php

/**
 * @file
 * Common get functions.
 */

use \Drupal\uikit\UIkit;

/**
 * Retrieves UIkit, jQuery and jQuery Migrate CDN assets.
 */
function uikit_get_cdn_assets() {
  global $theme_key;

  // Get the UIkit base style theme setting.
  $uikit_style = UIkit::getThemeSetting('base_style', $theme_key);

  // Default base style.
  $uikit_css = 'uikit.min.css';

  if ($uikit_style == 'customizer-css') {
    // If Customizer is used, locate and add the stylehseet.
    $customizer_css = UIkit::getThemeSetting('customizer_css', $theme_key);
    $file = file_load($customizer_css['fid']);

    drupal_add_css($file->uri, array(
      'group' => CSS_THEME,
      'every_page' => TRUE,
      'weight' => -20,
      'version' => UIkit::UIKIT_LIBRARY_VERSION,
    ));
  }
  else {
    // If not using the default base style, get the correct style.
    switch ($uikit_style) {
      case 'almost-flat':
        $uikit_css = 'uikit.almost-flat.min.css';
        break;

      case 'gradient':
        $uikit_css = 'uikit.gradient.min.css';
        break;
    }

    // Add the selected UIkit stylesheet.
    drupal_add_css('//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/$uikit_css", array(
      'type' => 'external',
      'group' => CSS_THEME,
      'every_page' => TRUE,
      'weight' => -20,
      'version' => UIkit::UIKIT_LIBRARY_VERSION,
    ));
  }

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
}

/**
 * Retrieves individual UIkit CDN asset.
 *
 * Retrieves an individual UIkit asset from cdnjs.cloudflare.com by a given
 * component name.
 *
 * @param string $component
 *   The component to retrieve CDN assets for.
 */
function uikit_get_cdn_asset($component = NULL) {
  global $theme_key;

  // Get the base style theme setting.
  $uikit_style = UIkit::getThemeSetting('base_style', $theme_key);

  switch ($uikit_style) {
    // Get the component style based on the base style.
    case 'almost-flat':
      $css = "$component.almost-flat.min.css";
      break;

    case 'gradient':
      $css = "$component.gradient.min.css";
      break;

    default:
      $css = "$component.min.css";
  }

  // Put all valid components and their assets into an array so we can load the
  // the correct assets.
  $components = array(
    'accordion' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'autocomplete' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'datepicker' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'dotnav' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => NULL,
    ),
    'form-advanced' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => NULL,
    ),
    'form-file' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => NULL,
    ),
    'form-password' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'form-select' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'grid-parallax' => array(
      'css' => NULL,
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'grid' => array(
      'css' => NULL,
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'htmleditor' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'lightbox' => array(
      'css' => NULL,
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'nestable' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'notify' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'pagination' => array(
      'css' => NULL,
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'parallax' => array(
      'css' => NULL,
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'placeholder' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => NULL,
    ),
    'progress' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => NULL,
    ),
    'search' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'slidenav' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => NULL,
    ),
    'slider' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'slideset' => array(
      'css' => NULL,
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'slideshow-fx' => array(
      'css' => NULL,
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'slideshow' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'sortable' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'sticky' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'timepicker' => array(
      'css' => NULL,
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'tooltip' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
    'upload' => array(
      'css' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/css/components/$css",
      'js' => '//cdnjs.cloudflare.com/ajax/libs/uikit/' . UIkit::UIKIT_LIBRARY_VERSION . "/js/components/$component.min.js",
    ),
  );

  if (isset($components[$component])) {
    // Get the css and js assets for the component.
    $component_css = $components[$component]['css'];
    $component_js = $components[$component]['js'];

    if (!empty($component_css)) {
      // Load component's stylesheet if it has one.
      drupal_add_css($component_css, array(
        'type' => 'external',
        'group' => CSS_THEME,
        'every_page' => TRUE,
        'weight' => -10,
        'version' => UIkit::UIKIT_LIBRARY_VERSION,
      ));
    }

    if (!empty($component_js)) {
      // Load component's script if it has one.
      drupal_add_js($component_js, array(
        'type' => 'external',
        'group' => JS_THEME,
        'every_page' => TRUE,
        'weight' => -10,
        'version' => UIkit::UIKIT_LIBRARY_VERSION,
      ));
    }
  }
  else {
    // Warn the user of an invald component.
    $message = t('The component @component does not exist in uikit_get_cdn_asset().', array('@component' => $component));
    drupal_set_message($message, 'warning');
    watchdog('uikit', $message, array(), WATCHDOG_WARNING);
  }
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
