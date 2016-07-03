<?php

/**
 * @file
 * Conditional logic and data processing for the UIkit theme.
 */

/**
 * Include common functions used throughout theme.
 */
include_once dirname(__FILE__) . '/includes/get.inc';

/**
 * Implements hook_libraries_info().
 */
function uikit_libraries_info() {
  $libraries = array();
  $libraries['uikit'] = array(
    'name' => 'UIkit library',
    'vendor url' => 'http://getuikit.com',
    'download url' => 'https://github.com/uikit/uikit/releases',
    'version arguments' => array(
      'file' => 'css/uikit.css',
      'pattern' => '@^/\*! UIkit ([\d\.]+)@',
      'lines' => 5,
      'cols' => 20,
    ),
    'version callback' => '_uikit_get_library_version',
    'files' => array(
      'js' => array(
        'js/uikit.js' => array(
          'type' => 'file',
          'group' => JS_THEME,
          'weight' => -10,
          'every_page' => TRUE,
        ),
      ),
      'css' => array(
        'css/uikit.css' => array(
          'type' => 'file',
          'group' => CSS_THEME,
          'weight' => -10,
          'every_page' => TRUE,
        ),
      ),
    ),
  );

  return $libraries;
}

/**
 * Implements template_preprocess_html().
 */
function uikit_preprocess_html(&$variables) {
  // Create an HTML5 doctype variable.
  $variables['doctype'] = '<!DOCTYPE html>' . "\n";

  // Create an attributes array for the html element.
  $html_attributes_array = array(
    'lang' => $variables['language']->language,
    'dir' => $variables['language']->dir,
    'class' => array('uk-height-1-1'),
  );
  $variables['html_attributes_array'] = $html_attributes_array;

  // Add the uk-height-1-1 class to extend the <html> and <body> elements to the
  // full height of the page.
  $variables['classes_array'][] = 'uk-height-1-1';

  // Serialize RDF Namespaces into an RDFa 1.1 prefix attribute.
  if ($variables['rdf_namespaces']) {
    $rdf_namespaces = array();

    foreach (explode("\n  ", ltrim($variables['rdf_namespaces'])) as $namespace) {
      // Remove xlmns: and ending quote and fix prefix formatting.
      $rdf_namespaces[] = str_replace('="', ': ', substr($namespace, 6, -1));
    }

    $variables['rdf_namespaces'] = ' prefix="' . implode('  ', $rdf_namespaces) . '"';
  }

  if (theme_get_setting('x_ua_compatible')) {
    $meta_x_ua_compatible = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => 'x-ua-compatible',
        'content' => 'IE=' . theme_get_setting('x_ua_compatible'),
      ),
      '#weight' => -9998,
    );

    drupal_add_html_head($meta_x_ua_compatible, 'uikit_x_ua_compatible');
  }

  // Get viewport metadata settings for mobile devices.
  $device_width_ratio = theme_get_setting('viewport_device_width_ratio');
  $custom_device_width = theme_get_setting('viewport_custom_width');
  $device_height_ratio = theme_get_setting('viewport_device_height_ratio');
  $custom_device_height = theme_get_setting('viewport_custom_height');
  $initial_scale = theme_get_setting('viewport_initial_scale');
  $maximum_scale = theme_get_setting('viewport_maximum_scale');
  $minimum_scale = theme_get_setting('viewport_minimum_scale');
  $user_scalable = theme_get_setting('viewport_user_scalable');
  $viewport_array = array();

  if ($device_width_ratio == 'device-width') {
    $viewport_array['width'] = 'width=device-width';
  }
  elseif ($device_width_ratio) {
    $viewport_array['width'] = 'width=' . $custom_device_width;
  }
  if ($device_height_ratio == 1) {
    $viewport_array['height'] = 'height=' . $custom_device_height;
  }
  if ($initial_scale) {
    $viewport_array['initial-scale'] = 'initial-scale=' . $initial_scale;
  }
  if ($maximum_scale) {
    $viewport_array['maximum-scale'] = 'maximum-scale=' . $maximum_scale;
  }
  if ($minimum_scale) {
    $viewport_array['minimum-scale'] = 'minimum-scale=' . $minimum_scale;
  }
  if ($viewport_array && !$user_scalable) {
    $viewport_array['user-scalable'] = 'user-scalable=no';
  }

  if ($viewport_array) {
    $viewport_content = implode(', ', $viewport_array);

    $meta_viewport = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'viewport',
        'content' => $viewport_content,
      ),
      '#weight' => -9997,
    );

    drupal_add_html_head($meta_viewport, 'uikit_viewport');
  }
}

/**
 * Implements template_process_html().
 */
function uikit_process_html(&$variables) {
  // Convert attribute arrays to an attribute string.
  $variables['html_attributes'] = drupal_attributes($variables['html_attributes_array']);
}

/**
 * Implements template_preprocess_page().
 */
function uikit_preprocess_page(&$variables) {
  // Checks if the uikit library can be loaded.
  if (_uikit_library_load()) {
    libraries_load('uikit');
  }

  $sidebar_first = $variables['page']['sidebar_first'];
  $sidebar_second = $variables['page']['sidebar_second'];
  $standard_layout = theme_get_setting('standard_sidebar_positions');
  $tablet_layout = theme_get_setting('tablet_sidebar_positions');
  $mobile_layout = theme_get_setting('mobile_sidebar_positions');

  $standard_grail = $standard_layout === 'holy-grail';
  $standard_left = $standard_layout === 'sidebars-left';
  $standard_right = $standard_layout === 'sidebars-right';

  $tablet_grail = $tablet_layout === 'holy-grail';
  $tablet_left = $tablet_layout === 'sidebars-left';
  $tablet_left_stacked = $tablet_layout === 'sidebar-left-stacked';
  $tablet_right = $tablet_layout === 'sidebars-right';
  $tablet_right_stacked = $tablet_layout === 'sidebar-right-stacked';

  $mobile_stacked = $mobile_layout === 'sidebars-stacked';
  $mobile_vertical = $mobile_layout === 'sidebars-vertical';

  // Assign page container attributes.
  $page_container_attributes['id'] = 'page';
  if (theme_get_setting('page_container')) {
    $page_container_attributes['class'][] = 'uk-container';
  }
  if (theme_get_setting('page_centering')) {
    $page_container_attributes['class'][] = 'uk-container-center';
  }
  if (theme_get_setting('page_margin')) {
    $page_container_attributes['class'][] = theme_get_setting('page_margin');
  }
  $variables['page_container_attributes_array'] = $page_container_attributes;

  // Assign content attributes.
  $variables['content_attributes_array']['id'] = 'page-content';

  // Assign sidebar_first attributes.
  $variables['sidebar_first_attributes_array'] = array(
    'id' => 'sidebar-first',
    'class' => array('uk-width-large-1-4'),
  );

  // Assign sidebar_second attributes.
  $variables['sidebar_second_attributes_array'] = array(
    'id' => 'sidebar-second',
    'class' => array('uk-width-large-1-4'),
  );

  // Assign additional content attributes if either sidebar is not empty.
  if (!empty($sidebar_first) && !empty($sidebar_second)) {
    $variables['content_attributes_array']['class'][] = 'uk-width-large-1-2';
    $variables['sidebar_first_attributes_array']['class'][] = 'uk-width-large-1-4';
    $variables['sidebar_second_attributes_array']['class'][] = 'uk-width-large-1-4';

    if ($standard_grail) {
      $variables['content_attributes_array']['class'][] = 'uk-push-large-1-4';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-pull-large-1-2';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-push-pull-large';
    }
    elseif ($standard_left) {
      $variables['content_attributes_array']['class'][] = 'uk-push-large-1-2';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-pull-large-1-2';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-pull-large-1-2';
    }
    elseif ($standard_right) {
      $variables['content_attributes_array']['class'][] = 'uk-push-pull-large';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-push-pull-large';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-push-pull-large';
    }

    if ($tablet_grail || $tablet_left || $tablet_right) {
      $variables['content_attributes_array']['class'][] = 'uk-width-medium-1-2';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-width-medium-1-4';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-width-medium-1-4';
    }
    elseif ($tablet_left_stacked || $tablet_right_stacked) {
      $variables['content_attributes_array']['class'][] = 'uk-width-medium-3-4';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-width-medium-1-4';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-width-medium-1-1';
    }

    if ($tablet_grail) {
      $variables['content_attributes_array']['class'][] = 'uk-push-medium-1-4';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-pull-medium-1-2';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-push-pull-medium';
    }
    elseif ($tablet_left) {
      $variables['content_attributes_array']['class'][] = 'uk-push-medium-1-2';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-pull-medium-1-2';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-pull-medium-1-2';
    }
    elseif ($tablet_right) {
      $variables['content_attributes_array']['class'][] = 'uk-push-pull-medium';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-push-pull-medium';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-push-pull-medium';
    }
    elseif ($tablet_left_stacked) {
      $variables['content_attributes_array']['class'][] = 'uk-push-medium-1-4';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-pull-medium-3-4';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-push-pull-medium';
    }
    elseif ($tablet_right_stacked) {
      $variables['content_attributes_array']['class'][] = 'uk-push-pull-medium';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-push-pull-medium';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-push-pull-medium';
    }

    if ($mobile_stacked || $mobile_vertical) {
      $variables['content_attributes_array']['class'][] = 'uk-width-small-1-1';
      $variables['content_attributes_array']['class'][] = 'uk-width-1-1';
      $variables['content_attributes_array']['class'][] = 'uk-push-pull-small';
    }

    if ($mobile_stacked) {
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-width-small-1-1';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-width-1-1';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-push-pull-small';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-width-small-1-1';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-width-1-1';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-push-pull-small';
    }
    elseif ($mobile_vertical) {
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-width-small-1-2';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-width-1-2';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-push-pull-small';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-width-small-1-2';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-width-1-2';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-push-pull-small';
    }
  }
  elseif (!empty($sidebar_first)) {
    $variables['content_attributes_array']['class'][] = 'uk-width-large-3-4';
    $variables['sidebar_first_attributes_array']['class'][] = 'uk-width-large-1-4';

    if ($standard_grail || $standard_left) {
      $variables['content_attributes_array']['class'][] = 'uk-push-large-1-4';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-pull-large-3-4';
    }
    elseif ($standard_right) {
      $variables['content_attributes_array']['class'][] = 'uk-push-pull-large';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-push-pull-large';
    }

    if ($tablet_layout) {
      $variables['content_attributes_array']['class'][] = 'uk-width-medium-3-4';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-width-medium-1-4';
    }

    if ($tablet_grail || $tablet_left || $tablet_left_stacked) {
      $variables['content_attributes_array']['class'][] = 'uk-push-medium-1-4';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-pull-medium-3-4';
    }
    elseif ($tablet_right || $tablet_right_stacked) {
      $variables['content_attributes_array']['class'][] = 'uk-push-pull-medium';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-push-pull-medium';
    }
  }
  elseif (!empty($sidebar_second)) {
    $variables['content_attributes_array']['class'][] = 'uk-width-large-3-4';
    $variables['sidebar_second_attributes_array']['class'][] = 'uk-width-large-1-4';

    if ($standard_grail || $standard_right) {
      $variables['content_attributes_array']['class'][] = 'uk-push-pull-large';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-push-pull-large';
    }
    elseif ($standard_left) {
      $variables['content_attributes_array']['class'][] = 'uk-push-large-1-4';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-pull-large-3-4';
    }

    if ($tablet_grail || $tablet_right || $tablet_left) {
      $variables['content_attributes_array']['class'][] = 'uk-width-medium-3-4';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-width-medium-1-4';
    }
    elseif ($tablet_left_stacked || $tablet_right_stacked) {
      $variables['content_attributes_array']['class'][] = 'uk-width-medium-1-1';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-width-medium-1-1';
    }

    if ($tablet_grail || $tablet_right) {
      $variables['content_attributes_array']['class'][] = 'uk-push-pull-medium';
      $variables['sidebar_first_attributes_array']['class'][] = 'uk-push-pull-medium';
    }
    elseif ($tablet_left) {
      $variables['content_attributes_array']['class'][] = 'uk-push-medium-1-4';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-pull-medium-3-4';
    }
    elseif ($tablet_left_stacked || $tablet_right_stacked) {
      $variables['content_attributes_array']['class'][] = 'uk-push-pull-medium';
      $variables['sidebar_second_attributes_array']['class'][] = 'uk-push-pull-medium';
    }
  }
  elseif (empty($sidebar_first) && empty($sidebar_second)) {
    $variables['content_attributes_array']['class'][] = 'uk-width-1-1';
  }

  // Define header attributes.
  $variables['header_attributes_array'] = array(
    'id' => 'page-header',
  );
  if (theme_get_setting('navbar_container')) {
    $variables['header_attributes_array']['class'][] = 'uk-container';
  }
  if (theme_get_setting('navbar_centering')) {
    $variables['header_attributes_array']['class'][] = 'uk-container-center';
  }

  // Define navbar attributes.
  $variables['navbar_attributes_array'] = array(
    'id' => 'page-navbar',
    'class' => array('uk-navbar'),
  );

  if (theme_get_setting('navbar_attached')) {
    $variables['navbar_attributes_array']['class'][] = 'uk-navbar-attached';
  }

  if (theme_get_setting('navbar_margin_top')) {
    switch (theme_get_setting('navbar_margin_top')) {
      case 1:
        $variables['navbar_attributes_array']['class'][] = 'uk-margin-top';
        break;

      case 2:
        $variables['navbar_attributes_array']['class'][] = 'uk-margin-large-top';
        break;

      case 3:
        $variables['navbar_attributes_array']['class'][] = 'uk-margin-small-top';
        break;
    }
  }

  if (theme_get_setting('navbar_margin_bottom')) {
    switch (theme_get_setting('navbar_margin_bottom')) {
      case 1:
        $variables['navbar_attributes_array']['class'][] = 'uk-margin-bottom';
        break;

      case 2:
        $variables['navbar_attributes_array']['class'][] = 'uk-margin-large-bottom';
        break;

      case 3:
        $variables['navbar_attributes_array']['class'][] = 'uk-margin-small-bottom';
        break;
    }
  }

  // Move the main and secondary menus into variables to set the attributes
  // accordingly.
  $navbar_main = '';
  $navbar_secondary = '';
  $navbar_menus = '';
  $offcanvas_main = '';
  $offcanvas_secondary = '';

  if ($variables['main_menu']) {
    if (theme_get_setting('main_menu_alignment')) {
      $navbar_main .= '<div id="navbar-flip--main-menu" class="uk-navbar-flip">';
    }
    $navbar_main .= theme('links__system_main_menu', array(
      'links' => $variables['main_menu'],
      'attributes' => array(
        'id' => 'main-menu',
        'class' => array('uk-navbar-nav', 'uk-hidden-small'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => 'uk-hidden',
      ),
    ));
    if (theme_get_setting('main_menu_alignment')) {
      $navbar_main .= '</div>';
    }

    $offcanvas_main = theme('links__system_main_menu__offcanvas', array(
      'links' => $variables['main_menu'],
      'attributes' => array(
        'id' => 'main-menu--offcanvas',
        'class' => array('uk-nav', 'uk-nav-offcanvas'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => 'uk-hidden',
      ),
    ));
  }

  if ($variables['secondary_menu']) {
    if (theme_get_setting('secondary_menu_alignment')) {
      $navbar_secondary .= '<div id="navbar-flip--secondary-menu" class="uk-navbar-flip">';
    }
    $navbar_secondary .= theme('links__system_secondary_menu', array(
      'links' => $variables['secondary_menu'],
      'attributes' => array(
        'id' => 'secondary-menu',
        'class' => array('uk-navbar-nav', 'uk-hidden-small'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => 'uk-hidden',
      ),
    ));
    if (theme_get_setting('secondary_menu_alignment')) {
      $navbar_secondary .= '</div>';
    }
    $offcanvas_secondary = theme('links__system_secondary_menu__offcanvas', array(
      'links' => $variables['secondary_menu'],
      'attributes' => array(
        'id' => 'secondary-menu--offcanvas',
        'class' => array('uk-nav', 'uk-nav-offcanvas'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => 'uk-hidden',
      ),
    ));
  }

  // Place additional menus in the navbar from the theme settings.
  $menus = menu_get_menus();
  foreach ($menus as $menu_name => $menu_title) {
    $menu_links = str_replace('-', '_', $menu_name);

    if (theme_get_setting($menu_name . '_in_navbar')) {
      $navbar_menu = menu_navigation_links($menu_name);

      if (theme_get_setting($menu_links . '_additional_alignment')) {
        $navbar_menus .= "<div id=\"navbar-flip--$menu_name\" class=\"uk-navbar-flip\">";
      }
      $navbar_menus .= theme('links__' . $menu_links, array(
        'links' => $navbar_menu,
        'attributes' => array(
          'id' => $menu_name,
          'class' => array('uk-navbar-nav', 'uk-hidden-small'),
        ),
        'heading' => array(
          'text' => t('@title', array('@title' => $menu_title)),
          'level' => 'h2',
          'class' => 'uk-hidden',
        ),
      ));
      if (theme_get_setting($menu_links . '_alignment')) {
        $navbar_menus .= '</div>';
      }
    }
  }

  $variables['navbar_main'] = $navbar_main;
  $variables['navbar_secondary'] = $navbar_secondary;
  $variables['navbar_menus'] = $navbar_menus;
  $variables['offcanvas_main'] = $offcanvas_main;
  $variables['offcanvas_secondary'] = $offcanvas_secondary;

  // Create variable for breadcrumb display setting.
  $variables['display_breadcrumb'] = theme_get_setting('display_breadcrumbs');

  // Get theme specific jQuery version.
  $jquery_version = theme_get_setting('jquery_update_jquery_version');

  // Get site wide jQuery version if theme specific one is not set.
  if (!$jquery_version && module_exists('jquery_update')) {
    $jquery_version = variable_get('jquery_update_jquery_version', '1.10');
  }

  // Check if the jquery_update module is both installed and enabled.
  if (!module_exists('jquery_update')) {
    $message = t('jQuery Update is not enabled. UIkit requires a minimum jQuery version of 1.10 or higher. Please enable the <a href="@jquery_update_project_url">jQuery Update</a> module and <a href="@jquery_update_configure">configure</a> the default jQuery version.', array(
      '@jquery_update_project_url' => 'https://www.drupal.org/project/jquery_update',
      '@jquery_update_configure' => url('admin/config/development/jquery_update'),
    ));
    drupal_set_message($message, 'error', FALSE);
  }

  // Check if the minimum jQuery version is met.
  if (module_exists('jquery_update') && !version_compare($jquery_version, '1.10', '>=')) {
    $message = t('UIkit requires a minimum jQuery version of 1.10 or higher. Please <a href="@jquery_update_configure">configure</a> the default jQuery version.', array(
      '@jquery_update_configure' => url('admin/config/development/jquery_update'),
    ));
    drupal_set_message($message, 'error', FALSE);
  }

  // Check if the libraries module is both installed and enabled.
  if (!module_exists('libraries')) {
    $message = t('UIkit requires the Libraries module. Please enable the <a href="@libraries_project_url">Libraries</a> module and follow <a href="@uikit_get_started">these instructions</a> to install the UIkit asset files.', array(
      '@libraries_project_url' => 'https://www.drupal.org/project/libraries',
      '@uikit_get_started' => check_url('admin/appearance/settings/uikit#edit-get-started'),
    ));
    drupal_set_message($message, 'error', FALSE);
  }

}

/**
 * Implements template_process_page().
 */
function uikit_process_page(&$variables) {
  // Convert attribute arrays to an attribute string.
  $variables['page_container_attributes'] = drupal_attributes($variables['page_container_attributes_array']);
  $variables['sidebar_first_attributes'] = drupal_attributes($variables['sidebar_first_attributes_array']);
  $variables['sidebar_second_attributes'] = drupal_attributes($variables['sidebar_second_attributes_array']);
  $variables['header_attributes'] = drupal_attributes($variables['header_attributes_array']);
  $variables['navbar_attributes'] = drupal_attributes($variables['navbar_attributes_array']);
}

/**
 * Implements template_preprocess_node().
 */
function uikit_preprocess_node(&$variables) {
  // Add the uk-article-title class to all node titles.
  $variables['title_attributes_array']['class'][] = 'uk-article-title';

  // Add the uk-flex-right class to node links to align them.
  $variables['content']['links']['#attributes']['class'][] = 'uk-flex-right';
}

/**
 * Implements template_preprocess_region().
 */
function uikit_preprocess_region(&$variables) {
  global $theme_key;
  $region = $variables['region'];
  $wrapper_id = str_replace('_', '-', $region);

  $variables['wrapper_attributes_array'] = array(
    'id' => 'region-' . $wrapper_id . '-wrapper',
    'class' => array('region-wrapper'),
  );

  // Get all regions for the theme.
  $regions = system_region_list($theme_key);

  foreach ($regions as $key => $value) {
    // Get the settings for each region being used.
    if ($region == $key) {
      $style_setting = theme_get_setting($key . '_style');
      $region_style = $style_setting ? $style_setting : 0;

      if ($region_style) {
        switch ($region_style) {
          case 'panel':
            $variables['wrapper_attributes_array']['class'][] = 'uk-panel';
            $variables['wrapper_attributes_array']['class'][] = 'uk-panel-box';
            break;

          case 'block':
            $variables['wrapper_attributes_array']['class'][] = 'uk-block';
            break;
        }
      }
    }
  }
}

/**
 * Implements hook_process_HOOK() for region.tpl.php.
 */
function uikit_process_region(&$variables) {
  $attributes = $variables['wrapper_attributes_array'];
  $variables['wrapper_attributes'] = drupal_attributes($attributes);
}

/**
 * Implements template_preprocess_block().
 */
function uikit_preprocess_block(&$variables) {
  $variables['content_attributes_array']['class'][] = 'uk-margin';
}

/**
 * Implements hook_preprocess_HOOK() for theme_button().
 */
function uikit_preprocess_button(&$variables) {
  // Add the uk-button class to all buttons.
  $variables['element']['#attributes']['class'][] = 'uk-button';
  $variables['element']['#attributes']['class'][] = 'uk-margin-small-right';
}

/**
 * Implements template_preprocess_comment().
 */
function uikit_preprocess_comment(&$variables) {
  $comment = $variables['elements']['#comment'];
  $node = $variables['elements']['#node'];

  // Add comment classes.
  $variables['classes_array'][] = 'uk-comment';
  $variables['classes_array'][] = 'uk-clearfix';
  $variables['classes_array'][] = 'uk-margin-top';
  $variables['title_attributes_array']['class'][] = 'uk-comment-title';
  $variables['content_attributes_array']['class'][] = 'uk-comment-body';

  // Use the comment cid as the permalink text in the comment title.
  $cid = $comment->cid;
  $uri = entity_uri('node', $node);
  $uri['options'] += array(
    'attributes' => array(
      'class' => array(
        'permalink',
      ),
      'rel' => 'bookmark',
    ),
    'fragment' => "comment-$cid",
  );
  $variables['permalink'] = l(t('#@cid', array('@cid' => $cid)), $uri['path'], $uri['options']);

  // Use the same uri for the title permalink.
  $variables['title'] = l(t('@subject', array('@subject' => $comment->subject)), $uri['path'], $uri['options']);

  // Use separate submitted by and date variables.
  $variables['submitted_user'] = t('!username', array('!username' => $variables['author']));
  $variables['submitted_date'] = t('!datetime', array('!datetime' => $variables['created']));
}

/**
 * Implements template_preprocess_comment_wrapper().
 */
function uikit_preprocess_comment_wrapper(&$variables) {
  $variables['classes_array'][] = 'uk-margin-top-remove';
}

/**
 * Implements hook_preprocess_HOOK() for theme_confirm_form().
 */
function uikit_preprocess_confirm_form(&$variables) {
  foreach ($variables['form']['actions'] as $key => $action) {
    $type = isset($action['#type']) ? $action['#type'] : 0;
    if ($type && $type == 'link') {
      $variables['form']['actions'][$key]['#attributes']['class'][] = 'uk-button';
    }
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_container().
 */
function uikit_preprocess_container(&$variables) {
  $variables['element']['#attributes']['class'][] = 'uk-form-row';
}

/**
 * Implements template_preprocess_field().
 */
function uikit_preprocess_field(&$variables) {
  $type = $variables['element']['#field_type'];
  $classes = $variables['classes_array'];

  // Add utility classes based on field type.
  switch ($type) {
    case 'image':
      $classes[] = 'uk-float-left';
      $classes[] = 'uk-margin-right';
      $classes[] = 'uk-margin-bottom';
      break;

    case 'text':
    case 'text_with_summary':
      $classes[] = 'uk-clearfix';
      break;
  }

  $variables['classes_array'] = $classes;
}

/**
 * Implements hook_preprocess_HOOK() for theme_fieldset().
 */
function uikit_preprocess_fieldset(&$variables) {
  $collapsible = $variables['element']['#collapsible'];
  $group_fieldset = isset($variables['element']['#group_fieldset']) && $variables['element']['#group_fieldset'];
  $format_fieldset = isset($variables['element']['format']);

  // Collapsible, non-grouped fieldsets will use UIkit's accordion components.
  if ($group_fieldset) {
    $variables['theme_hook_suggestions'][] = 'fieldset__grouped';
  }
  elseif ($collapsible) {
    $variables['theme_hook_suggestions'][] = 'fieldset__collapsible';
    $variables['element']['#attributes']['class'][] = 'uk-form-row';
    $variables['element']['#attributes']['class'][] = 'uk-accordion';
    $variables['element']['#attributes']['data-uk-accordion'] = '';

    foreach ($variables['element']['#attributes']['class'] as $key => $class) {
      if ($class == 'collapsible' || $class == 'collapsed') {
        unset($variables['element']['#attributes']['class'][$key]);
        array_values($variables['element']['#attributes']['class']);
      }
      if ($class == 'collapsed') {
        $variables['element']['#attributes']['data-uk-accordion'] .= '{showfirst: false}';
      }
    }
  }
  elseif ($format_fieldset) {
    $variables['theme_hook_suggestions'][] = 'fieldset__format';
  }
  else {
    $variables['theme_hook_suggestions'][] = 'fieldset';
    $variables['element']['#attributes']['class'][] = 'uk-form-row';
  }

  if (_uikit_library_load()) {
    // Load accordion component stylesheet and script.
    $library_path = _uikit_get_library_path();
    drupal_add_css($library_path . '/css/components/accordion.gradient.min.css', array(
      'group' => CSS_THEME,
    ));
    drupal_add_js($library_path . '/js/components/accordion.min.js', array(
      'group' => JS_THEME,
    ));
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_form().
 */
function uikit_preprocess_form(&$variables) {
  $element = $variables['element'];
  $children = $element['#children'];

  $form_build_id = isset($element['form_build_id']['#children']) ? $element['form_build_id']['#children'] : '';
  $form_token = isset($element['form_token']['#children']) ? $element['form_token']['#children'] : '';
  $form_id = isset($element['form_id']['#children']) ? $element['form_id']['#children'] : '';

  // Add the uk-form class to all forms.
  $variables['element']['#attributes']['class'] = array('uk-form');
  $variables['element']['#attributes']['class'][] = 'uk-form-stacked';

  if (_uikit_library_load()) {
    // Load advanced form component stylesheets.
    $library_path = _uikit_get_library_path();
    drupal_add_css($library_path . '/css/components/form-advanced.min.css', array(
      'group' => CSS_THEME,
      'weight' => -10,
      'every_page' => TRUE,
    ));
  }

  if ($form_build_id) {
    $children = str_replace($form_build_id, '', $children);
  }
  if ($form_token) {
    $children = str_replace($form_token, '', $children);
  }
  if ($form_id) {
    $children = str_replace($form_id, '', $children);
  }

  $children .= $form_build_id . $form_token . $form_id;
  $variables['element']['#children'] = $children;
}

/**
 * Implements hook_preprocess_HOOK() for theme_item_list().
 */
function uikit_preprocess_item_list(&$variables) {
  // Add the uk-list class to all item lists.
  $variables['attributes']['class'][] = 'uk-list';
}

/**
 * Implements hook_preprocess_HOOK() for theme_links().
 */
function uikit_preprocess_links(&$variables) {
  $theme_hook_original = isset($variables['theme_hook_original']) ? $variables['theme_hook_original'] : '';
  $classes = isset($variables['attributes']['class']) ? $variables['attributes']['class'] : array();

  // Add uk-subnav and uk-subnav-line classes to inline links.
  $inline = in_array('inline', $classes);

  if ($inline) {
    $variables['attributes']['class'][] = 'uk-subnav';
    $variables['attributes']['class'][] = 'uk-subnav-line';
  }

  // Add uk-nav class to contextual links.
  if ($theme_hook_original == 'links__contextual') {
    $variables['attributes']['class'] = array('uk-nav');
  }
}

/**
 * Implements template_preprocess_HOOK() for theme_menu_link().
 */
function uikit_preprocess_menu_link(&$variables) {
  global $user;
  $classes = isset($variables['element']['#attributes']['class']) ? $variables['element']['#attributes']['class'] : array();
  $leaf = array_keys($classes, 'leaf');
  $active_trail = array_keys($classes, 'active-trail');

  // Remove leaf classes.
  foreach ($leaf as $leaf_key) {
    unset($variables['element']['#attributes']['class'][$leaf_key]);
  }

  // Add uk-active class to active links.
  $href = $variables['element']['#href'];
  $user_profile = $href === 'user' && $_GET['q'] === "user/$user->uid";
  if ($href == $_GET['q'] || ($href == '<front>' && drupal_is_front_page()) || !empty($active_trail) || $user_profile) {
    $variables['element']['#attributes']['class'][] = 'uk-active';
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_menu_local_tasks().
 */
function uikit_preprocess_menu_local_tasks(&$variables) {
  // Get the local task styles.
  $primary_style = theme_get_setting('primary_tasks_style');
  $secondary_style = theme_get_setting('secondary_tasks_style');

  // Set the default attributes.
  $variables['primary_attributes_array'] = array(
    'id' => 'primary-local-tasks',
    'class' => array('uk-subnav'),
  );
  $variables['secondary_attributes_array'] = array(
    'id' => 'secondary-local-tasks',
    'class' => array('uk-subnav'),
  );

  // Add additional styling from theme settings.
  if ($primary_style) {
    $variables['primary_attributes_array']['class'][] = $primary_style;
  }
  if ($secondary_style) {
    $variables['secondary_attributes_array']['class'][] = $secondary_style;
  }
}

/**
 * Implements hook_process_HOOK() for theme_menu_local_tasks().
 */
function uikit_process_menu_local_tasks(&$variables) {
  $variables['primary_attributes'] = drupal_attributes($variables['primary_attributes_array']);
  $variables['secondary_attributes'] = drupal_attributes($variables['secondary_attributes_array']);
}

/**
 * Implements hook_preprocess_HOOK() for theme_table().
 */
function uikit_preprocess_table(&$variables) {
  $variables['attributes']['class'][] = 'uk-table';

  // Add some additional classes to the table for text format filter tips.
  $filter_tips = current_path() === 'filter/tips';
  if ($filter_tips) {
    $variables['attributes']['class'][] = 'uk-table-striped';
    $variables['attributes']['class'][] = 'table-filter-tips';
  }
}

/**
 * Implements template_preprocess_username().
 */
function uikit_preprocess_username(&$variables) {
  global $language;
  $user_language = isset($variables['attributes_array']['xml:lang']);

  if ($user_language) {
    $lang = $variables['attributes_array']['xml:lang'];
    unset($variables['attributes_array']['xml:lang']);
    $variables['attributes_array']['lang'] = !empty($lang) ? $lang : $language->language;
  }
}

/**
 * Implements hook_css_alter().
 */
function uikit_css_alter(&$css) {
  $theme = drupal_get_path('theme', 'uikit');
  $style = theme_get_setting('base_style') ? '.' . theme_get_setting('base_style') : '';
  $library_path = _uikit_get_library_path();

  // Stop Drupal core stylesheets from being loaded.
  unset($css[drupal_get_path('module', 'system') . '/system.messages.css']);
  unset($css[drupal_get_path('module', 'system') . '/system.theme.css']);
  unset($css[drupal_get_path('module', 'system') . '/system.menus.css']);

  // Use the UIkit theme style selected in the theme settings.
  $css[$library_path . '/css/uikit.css']['data'] = $library_path . '/css/uikit' . $style . '.css';

  // Replace the book module's book.css with a custom version.
  $book_css = drupal_get_path('module', 'book') . '/book.css';
  if (isset($css[$book_css])) {
    $css[$book_css]['data'] = $theme . '/css/book.css';
  }

  // Replace the user module's user.css with a custom version.
  $user_css = drupal_get_path('module', 'user') . '/user.css';
  if (isset($css[$user_css])) {
    $css[$user_css]['data'] = $theme . '/css/user.css';
  }

  // Replace the field module's field.css with a custom version.
  $field_css = drupal_get_path('module', 'field') . '/theme/field.css';
  if (isset($css[$field_css])) {
    $css[$field_css]['data'] = $theme . '/css/field.css';
  }
}

/**
 * Implements hook_element_info_alter().
 */
function uikit_element_info_alter(&$type) {
  // Remove prefix and suffix from contextual links.
  $contextual_links = isset($type['contextual_links']);
  if ($contextual_links) {
    $type['contextual_links']['#prefix'] = '<div class="contextual-links-wrapper">';
  }
}

/**
 * Implements hook_html_head_alter().
 */
function uikit_html_head_alter(&$head_elements) {
  if (isset($head_elements['system_meta_content_type'])) {
    $head_elements['system_meta_content_type']['#attributes'] = array(
      'charset' => theme_get_setting('meta_charset'),
    );
    $head_elements['system_meta_content_type']['#weight'] = -9999;
  }

  // Some modules, such as the Adminimal Admin menu, add a viewport meta tag.
  // Remove this so the theme can define the tag.
  if (isset($head_elements['viewport'])) {
    unset($head_elements['viewport']);
  }
}

/**
 * Implements hook_js_alter().
 */
function uikit_js_alter(&$javascript) {
  $theme = drupal_get_path('theme', 'uikit');

  // Replace the contextual module's contextual.js with a custom version.
  $contextual_js = drupal_get_path('module', 'contextual') . '/contextual.js';
  if (isset($javascript[$contextual_js])) {
    $javascript[$contextual_js]['data'] = $theme . '/js/contextual.js';
  }

  // Replace tabledrag.js and tableheader.js with custom versions.
  $tabledrag_js = 'misc/tabledrag.js';
  $tableheader_js = 'misc/tableheader.js';
  if (isset($javascript[$tabledrag_js])) {
    $javascript[$tabledrag_js]['data'] = $theme . '/js/tabledrag.js';
  }
  if (isset($javascript[$tableheader_js])) {
    $javascript[$tableheader_js]['data'] = $theme . '/js/tableheader.js';
  }

  // Replace the user module's user.js with a custom version.
  $user_js = drupal_get_path('module', 'user') . '/user.js';
  if (isset($javascript[$user_js])) {
    $javascript[$user_js]['data'] = $theme . '/js/user.js';
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function uikit_form_user_login_block_alter(&$form, &$form_state, $form_id) {
  // Add utility classes to the login block links.
  $form['links']['#prefix'] = '<div class="uk-form-row form-item-list">';
  $form['links']['#suffix'] = '</div>';
}

/**
 * Implements hook_menu_local_tasks_alter().
 */
function uikit_menu_local_tasks_alter(&$data, $router_item, $root_path) {
  // Define various icons.
  $plus = '<i class="uk-icon-plus"></i> ';

  foreach ($data['actions']['output'] as $key => $action) {
    // Add icon based on link path.
    if (isset($action['#link']['path'])) {
      switch ($action['#link']['path']) {
        case 'node/add':
        case 'admin/structure/block/add':
        case 'admin/structure/types/add':
        case 'admin/structure/menu/add':
        case 'admin/structure/taxonomy/add':
        case 'admin/structure/taxonomy/%/add':
        case 'admin/appearance/install':
        case 'admin/people/create':
        case 'admin/modules/install':
        case 'admin/config/content/formats/add':
        case 'admin/config/media/image-styles/add':
        case 'admin/config/search/path/add':
        case 'admin/config/regional/date-time/types/add':
        case 'admin/config/user-interface/shortcut/add-set':
          $title = $plus . $data['actions']['output'][$key]['#link']['title'];
          $data['actions']['output'][$key]['#link']['title'] = $title;
          $data['actions']['output'][$key]['#link']['localized_options']['html'] = TRUE;
          break;
      }
    }
    // Some actions use the href key instead of the path key.
    elseif (isset($action['#link']['href'])) {
      switch ($action['#link']['href']) {
        case 'node/add/blog':
          $title = $plus . $data['actions']['output'][$key]['#link']['title'];
          $data['actions']['output'][$key]['#link']['title'] = $title;
          $data['actions']['output'][$key]['#link']['localized_options']['html'] = TRUE;
          break;
      }
    }
  }
}
