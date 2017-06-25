<?php

/**
 * @file
 * Set up variables to be placed within the template (.tpl.php) files.
 *
 * The variables set up here apply to both templates (.tpl.php) files and
 * functions (theme_HOOK). These are also used for providing
 * @link https://www.drupal.org/node/223440 template suggestions @endlink.
 *
 * @see process.inc
 */

use Drupal\uikit\UIkit;

/**
 * Implements template_preprocess_html().
 */
function uikit_preprocess_html(&$variables) {
  global $theme_key;

  // Load UIkit assets, i.e. stylesheets and scripts.
  uikit_get_cdn_assets();

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

  // Add an http-equiv tag, if set.
  if (UIkit::getThemeSetting('x_ua_compatible', $theme_key)) {
    $meta_x_ua_compatible = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => 'x-ua-compatible',
        'content' => 'IE=' . UIkit::getThemeSetting('x_ua_compatible', $theme_key),
      ),
      '#weight' => -9998,
    );

    drupal_add_html_head($meta_x_ua_compatible, 'uikit_x_ua_compatible');
  }

  // Get viewport metadata settings for mobile devices.
  $device_width_ratio = UIkit::getThemeSetting('viewport_device_width_ratio', $theme_key);
  $custom_device_width = UIkit::getThemeSetting('viewport_custom_width', $theme_key);
  $device_height_ratio = UIkit::getThemeSetting('viewport_device_height_ratio', $theme_key);
  $custom_device_height = UIkit::getThemeSetting('viewport_custom_height', $theme_key);
  $initial_scale = UIkit::getThemeSetting('viewport_initial_scale', $theme_key);
  $maximum_scale = UIkit::getThemeSetting('viewport_maximum_scale', $theme_key);
  $minimum_scale = UIkit::getThemeSetting('viewport_minimum_scale', $theme_key);
  $user_scalable = UIkit::getThemeSetting('viewport_user_scalable', $theme_key);
  $viewport_array = array();

  // Add each, if set, to the viewport array.
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
    // Add the viewport options to the viewport meta tag.
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
 * Implements template_preprocess_page().
 */
function uikit_preprocess_page(&$variables) {
  global $theme_key;

  // Get various theme settings to add the correct attributes.
  $sidebar_first = isset($variables['page']['sidebar_first']) ? $variables['page']['sidebar_first'] : '';
  $sidebar_second = isset($variables['page']['sidebar_second']) ? $variables['page']['sidebar_second'] : '';
  $standard_layout = UIkit::getThemeSetting('standard_sidebar_positions', $theme_key);
  $tablet_layout = UIkit::getThemeSetting('tablet_sidebar_positions', $theme_key);
  $mobile_layout = UIkit::getThemeSetting('mobile_sidebar_positions', $theme_key);

  // Determine the standard layout.
  $standard_grail = $standard_layout === 'holy-grail';
  $standard_left = $standard_layout === 'sidebars-left';
  $standard_right = $standard_layout === 'sidebars-right';

  // Determine the tablet layout.
  $tablet_grail = $tablet_layout === 'holy-grail';
  $tablet_left = $tablet_layout === 'sidebars-left';
  $tablet_left_stacked = $tablet_layout === 'sidebar-left-stacked';
  $tablet_right = $tablet_layout === 'sidebars-right';
  $tablet_right_stacked = $tablet_layout === 'sidebar-right-stacked';

  // Determine the mobile layout.
  $mobile_stacked = $mobile_layout === 'sidebars-stacked';
  $mobile_vertical = $mobile_layout === 'sidebars-vertical';

  // Assign page container attributes.
  $page_container_attributes['id'] = 'page';
  if (UIkit::getThemeSetting('page_container', $theme_key)) {
    $page_container_attributes['class'][] = 'uk-container';
  }
  if (UIkit::getThemeSetting('page_centering', $theme_key)) {
    $page_container_attributes['class'][] = 'uk-container-center';
  }
  if (UIkit::getThemeSetting('page_margin', $theme_key)) {
    $page_container_attributes['class'][] = UIkit::getThemeSetting('page_margin', $theme_key);
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
  if (UIkit::getThemeSetting('navbar_container', $theme_key)) {
    $variables['header_attributes_array']['class'][] = 'uk-container';
  }
  if (UIkit::getThemeSetting('navbar_centering', $theme_key)) {
    $variables['header_attributes_array']['class'][] = 'uk-container-center';
  }

  // Define navbar attributes.
  $variables['navbar_attributes_array'] = array(
    'id' => 'page-navbar',
    'class' => array('uk-navbar'),
  );

  if (UIkit::getThemeSetting('navbar_attached', $theme_key)) {
    $variables['navbar_attributes_array']['class'][] = 'uk-navbar-attached';
  }

  if (UIkit::getThemeSetting('navbar_margin_top', $theme_key)) {
    switch (UIkit::getThemeSetting('navbar_margin_top', $theme_key)) {
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

  if (UIkit::getThemeSetting('navbar_margin_bottom', $theme_key)) {
    switch (UIkit::getThemeSetting('navbar_margin_bottom', $theme_key)) {
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
  $variables['navbar_primary'] = FALSE;
  $variables['navbar_secondary'] = FALSE;
  $variables['offcanvas_primary'] = FALSE;
  $variables['offcanvas_secondary'] = FALSE;

  // Provide menu trees and theme wrappers for the navbar and offcanvas menus.
  if ($variables['main_menu']) {
    // Primary navbar menu.
    $variables['navbar_primary'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
    $variables['navbar_primary']['#theme_wrappers'] = array('menu_tree__navbar');

    foreach ($variables['navbar_primary'] as $key => $value) {
      // Define a theme wrapper for navbar menu links.
      if (is_array($value) && isset($value['#original_link'])) {
        $variables['navbar_primary'][$key]['#theme'] = 'menu_link__navbar';
      }
    }

    // Primary offcanvas menu.
    $variables['offcanvas_primary'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
    $variables['offcanvas_primary']['#theme_wrappers'] = array('menu_tree__offcanvas');

    foreach ($variables['offcanvas_primary'] as $key => $value) {
      // Define a theme wrapper for offcanvas below menu trees.
      if (is_array($value) && isset($value['#below']) && !empty($value['#below'])) {
        $variables['offcanvas_primary'][$key]['#below']['#theme_wrappers'] = array('menu_tree__offcanvas__below');
      }
      // Define a theme wrapper for offcanvas menu links.
      if (is_array($value) && isset($value['#original_link'])) {
        $variables['offcanvas_primary'][$key]['#theme'] = 'menu_link__offcanvas';
      }
    }
  }
  if ($variables['secondary_menu']) {
    // Secondary navbar menu.
    $variables['navbar_secondary'] = menu_tree(variable_get('menu_secondary_links_source', 'user-menu'));
    $variables['navbar_secondary']['#theme_wrappers'] = array('menu_tree__navbar_flip');

    foreach ($variables['navbar_secondary'] as $key => $value) {
      // Define a theme wrapper for navbar menu links.
      if (is_array($value) && isset($value['#original_link'])) {
        $variables['navbar_secondary'][$key]['#theme'] = 'menu_link__navbar';
      }
    }

    // Secondary offcanvas menu.
    $variables['offcanvas_secondary'] = menu_tree(variable_get('menu_secondary_links_source', 'user-menu'));
    $variables['offcanvas_secondary']['#theme_wrappers'] = array('menu_tree__offcanvas');

    foreach ($variables['offcanvas_secondary'] as $key => $value) {
      // Define a theme wrapper for offcanvas below menu trees.
      if (is_array($value) && isset($value['#below']) && !empty($value['#below'])) {
        $variables['offcanvas_secondary'][$key]['#below']['#theme_wrappers'] = array('menu_tree__offcanvas__below');
      }
      // Define a theme wrapper for offcanvas menu links.
      if (is_array($value) && isset($value['#original_link'])) {
        $variables['offcanvas_secondary'][$key]['#theme'] = 'menu_link__offcanvas';
      }
    }
  }

  // Create variable for breadcrumb display setting.
  $variables['display_breadcrumb'] = UIkit::getThemeSetting('display_breadcrumbs', $theme_key);
}

/**
 * Implements template_preprocess_node().
 */
function uikit_preprocess_node(&$variables) {
  $node = $variables['node'];

  // Add the uk-article-title class to all node titles.
  $variables['title_attributes_array']['class'][] = 'uk-article-title';

  // Theme the submitted meta data.
  $datetime = date('F j, Y', $node->created);
  if (variable_get('node_submitted_' . $node->type, TRUE)) {
    $variables['submitted'] = t('Written by !username on !datetime', array('!username' => $variables['name'], '!datetime' => $datetime));
  }
}

/**
 * Implements template_preprocess_region().
 */
function uikit_preprocess_region(&$variables) {
  global $theme_key;
  $region = $variables['region'];
  $wrapper_id = str_replace('_', '-', $region);

  // Add a wrapper id and class to help themers.
  $variables['wrapper_attributes_array'] = array(
    'id' => 'region-' . $wrapper_id . '-wrapper',
    'class' => array('region-wrapper'),
  );

  // Get all regions for the theme.
  $regions = system_region_list($theme_key);

  foreach ($regions as $key => $value) {
    // Get the settings for each region being used.
    if ($region == $key) {
      $style_setting = UIkit::getThemeSetting($key . '_style', $theme_key);
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
 * Implements template_preprocess_block().
 */
function uikit_preprocess_block(&$variables) {
  $region = $variables['block']->region;

  if ($region == 'sidebar_first' || $region == 'sidebar_second') {
    $variables['classes_array'][] = 'uk-margin';
  }
}

/**
 * Implements template_preprocess_HOOK().
 */
function uikit_preprocess_breadcrumb(&$variables) {
  global $theme_key;

  // Remove home link from breadcrumb if disabled in theme settings.
  if (!UIkit::getThemeSetting('breakcrumbs_home_link', $theme_key)) {
    array_shift($variables['breadcrumb']);
  }

  if (UIkit::getThemeSetting('breakcrumbs_current_page') && !drupal_is_front_page()) {
    // Display the current page title if enabled in the theme settings and set
    // it as being active.
    $page_title = UIkit::getPageTitle();
    $variables['breadcrumb'][] = '<span>' . $page_title . '</span>';
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_button().
 */
function uikit_preprocess_button(&$variables) {
  $value = $variables['element']['#value'];

  // Add the uk-button class to all buttons.
  $variables['element']['#attributes']['class'][] = 'uk-button';

  // Add uk-button-STYLE class based on the button value.
  switch ($value) {
    case 'Add':
    case 'Continue':
    case 'Create new account':
    case 'Create new set':
    case 'Create new style':
    case 'Download these updates':
    case 'Install':
    case 'Revert':
    case 'Save':
    case 'Save block':
    case 'Save blocks':
    case 'Save configuration':
    case 'Save content type':
    case 'Save permissions':
    case 'Save role':
    case 'Save settings':
    case 'Save field settings':
    case 'Upload':
    case 'Update effect':
    case 'Update preview':
    case 'Update style':
      $variables['element']['#attributes']['class'][] = 'uk-button-primary';
      break;

    case 'Override defaults':
    case 'Preview':
      $variables['element']['#attributes']['class'][] = 'uk-button-warning';
      break;

    case 'Cancel':
    case 'Delete':
    case 'Delete content type':
    case 'Delete role':
    case 'Remove':
      $variables['element']['#attributes']['class'][] = 'uk-button-danger';
      break;
  }

  // Add small right margin so button groups have proper spacing.
  $variables['element']['#attributes']['class'][] = 'uk-margin-small-right';
}

/**
 * Implements template_preprocess_comment().
 */
function uikit_preprocess_comment(&$variables) {
  global $theme_key;
  $comment = $variables['elements']['#comment'];
  $node = $variables['elements']['#node'];

  // Check if user picture in comments is enabled.
  $comment_picture = UIkit::getThemeSetting('toggle_comment_user_picture', $theme_key) ? 1 : 0;

  // Check if user pictures are enabled.
  $user_pictures = variable_get('user_pictures') ? 1 : 0;

  // Add comment classes.
  $variables['classes_array'][] = 'uk-comment';
  if ($variables['elements']['#comment']->divs > 0) {
    $variables['classes_array'][] = 'uk-comment-primary';
  }
  $variables['title_attributes_array']['class'][] = 'uk-comment-title';
  $variables['content_attributes_array']['class'][] = 'uk-comment-body';

  // Use the comment id as the permalink text in the comment title.
  $id = $variables['id'];
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
  $variables['permalink'] = l(t('#@id', array('@id' => $id)), $uri['path'], $uri['options']);

  // Use the same uri for the title permalink.
  $title['options'] = array(
    'attributes' => array(
      'class' => array(
        'uk-link-reset',
      ),
      'rel' => 'bookmark',
    ),
    'fragment' => "comment-$cid",
  );
  $variables['title'] = l(t('@subject', array('@subject' => $comment->subject)), $uri['path'], $title['options']);

  // Use separate submitted by and date variables.
  $variables['submitted_user'] = t('!username', array('!username' => $variables['author']));
  $variables['submitted_date'] = t('!datetime', array('!datetime' => $variables['created']));

  $uid = $variables['comment']->uid;
  $user = user_load($uid);
  if ($comment_picture && $user_pictures && !isset($user->picture)) {
    // Provide a default image when the user does not have a picture uploaded.
    $default = ' data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4NCjwhLS0gR2VuZXJhdG9yOiBBZG9iZSBJbGx1c3RyYXRvciAxNi4wLjQsIFNWRyBFeHBvcnQgUGx1Zy1JbiAuIFNWRyBWZXJzaW9uOiA2LjAwIEJ1aWxkIDApICAtLT4NCjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+DQo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkViZW5lXzEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4Ig0KCSB3aWR0aD0iNTBweCIgaGVpZ2h0PSI1MHB4IiB2aWV3Qm94PSIwIDAgNTAgNTAiIGVuYWJsZS1iYWNrZ3JvdW5kPSJuZXcgMCAwIDUwIDUwIiB4bWw6c3BhY2U9InByZXNlcnZlIj4NCjxyZWN0IGZpbGw9IiNGRkZGRkYiIHdpZHRoPSI1MCIgaGVpZ2h0PSI1MCIvPg0KPGc+DQoJPHBhdGggZmlsbD0iI0UwRTBFMCIgZD0iTTQ1LjQ1LDQxLjM0NWMtMC4yMDktMS4xNjYtMC40NzMtMi4yNDYtMC43OTEtMy4yNDJjLTAuMzE5LTAuOTk2LTAuNzQ3LTEuOTY3LTEuMjg2LTIuOTE0DQoJCWMtMC41MzgtMC45NDYtMS4xNTUtMS43NTMtMS44NTItMi40MmMtMC42OTktMC42NjctMS41NS0xLjItMi41NTYtMS41OThzLTIuMTE3LTAuNTk4LTMuMzMyLTAuNTk4DQoJCWMtMC4xNzksMC0wLjU5NywwLjIxNC0xLjI1NSwwLjY0MmMtMC42NTcsMC40MjktMS4zOTksMC45MDctMi4yMjYsMS40MzRjLTAuODI3LDAuNTI4LTEuOTAzLDEuMDA2LTMuMjI3LDEuNDM0DQoJCWMtMS4zMjUsMC40MjktMi42NTUsMC42NDMtMy45ODksMC42NDNjLTEuMzM0LDAtMi42NjQtMC4yMTQtMy45ODktMC42NDNjLTEuMzI1LTAuNDI4LTIuNDAxLTAuOTA2LTMuMjI3LTEuNDM0DQoJCWMtMC44MjgtMC41MjctMS41NjktMS4wMDUtMi4yMjYtMS40MzRjLTAuNjU4LTAuNDI4LTEuMDc2LTAuNjQyLTEuMjU1LTAuNjQyYy0xLjIxNiwwLTIuMzI2LDAuMTk5LTMuMzMyLDAuNTk4DQoJCWMtMS4wMDYsMC4zOTgtMS44NTgsMC45MzEtMi41NTQsMS41OThjLTAuNjk5LDAuNjY3LTEuMzE1LDEuNDc0LTEuODUzLDIuNDJjLTAuNTM4LDAuOTQ3LTAuOTY3LDEuOTE3LTEuMjg1LDIuOTE0DQoJCXMtMC41ODMsMi4wNzYtMC43OTIsMy4yNDJjLTAuMjA5LDEuMTY1LTAuMzQ5LDIuMjUxLTAuNDE4LDMuMjU2Yy0wLjA3LDEuMDA2LTAuMTA0LDIuMS0wLjEwNCwzLjE1NUMzLjkwMSw0OC41NCwzLjk4Nyw0OSw0LjE0Myw1MA0KCQloNDEuNTg5YzAuMTU2LTEsMC4yNDItMS40NiwwLjI0Mi0yLjI0M2MwLTEuMDU1LTAuMDM1LTIuMTE4LTAuMTA1LTMuMTI0QzQ1Ljc5OSw0My42MjcsNDUuNjYsNDIuNTEsNDUuNDUsNDEuMzQ1eiIvPg0KCTxwYXRoIGZpbGw9IiNFMEUwRTAiIGQ9Ik0yNC45MzgsMzIuNDg1YzMuMTY3LDAsNS44NzEtMS4xMjEsOC4xMTMtMy4zNjFjMi4yNDEtMi4yNDIsMy4zNjEtNC45NDUsMy4zNjEtOC4xMTMNCgkJcy0xLjEyMS01Ljg3Mi0zLjM2MS04LjExMmMtMi4yNDItMi4yNDEtNC45NDYtMy4zNjItOC4xMTMtMy4zNjJzLTUuODcyLDEuMTIxLTguMTEyLDMuMzYyYy0yLjI0MiwyLjI0MS0zLjM2Miw0Ljk0NS0zLjM2Miw4LjExMg0KCQlzMS4xMiw1Ljg3MSwzLjM2Miw4LjExM0MxOS4wNjUsMzEuMzY1LDIxLjc3MSwzMi40ODUsMjQuOTM4LDMyLjQ4NXoiLz4NCjwvZz4NCjwvc3ZnPg0K';
    $variables['picture'] = '<img class="uk-comment-avatar" width="50" height="50" src="' . $default . '">';
  }
  else {
    $picture = theme('image_style', array(
      'style_name' => 'thumbnail',
      'path' => $user->picture->uri,
      'attributes' => array(
        'class' => 'uk-comment-avatar'
      ),
    ));
    $options = array(
      'attributes' => array(
        'title' => t('View user profile.'),
      ),
      'html' => TRUE,
    );
    $variables['picture'] = l($picture, "user/$uid", $options);
  }
  $variables['content']['links']['#attributes']['class'][] = 'uk-float-right';
}

/**
 * Implements template_preprocess_comment_wrapper().
 */
function uikit_preprocess_comment_wrapper(&$variables) {
  // Remove margin from the comment wrapper element.
  $variables['classes_array'][] = 'uk-margin-top-remove';
}

/**
 * Implements hook_preprocess_HOOK() for theme_confirm_form().
 */
function uikit_preprocess_confirm_form(&$variables) {
  foreach ($variables['form']['actions'] as $key => $action) {
    $type = isset($action['#type']) ? $action['#type'] : 0;

    if ($type && $type == 'link') {
      // Add the uk-button class to form action links for consistent styling
      // with form action buttons.
      $variables['form']['actions'][$key]['#attributes']['class'][] = 'uk-button';
    }
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_container().
 */
function uikit_preprocess_container(&$variables) {
  // Some modules do not set the classes in attributes as an array and use a
  // string instead. Move these classes into an array to avoid string to array
  // errors.
  $attributes = $variables['element']['#attributes'];
  if (isset($attributes['class']) && !is_array($attributes['class'])) {
    $old_classes = explode(' ', $variables['element']['#attributes']['class']);
    $variables['element']['#attributes']['class'] = $old_classes;
  }

  // Add the uk-form-row class to provide proper margin between container
  // elements.
  $variables['element']['#attributes']['class'][] = 'uk-form-row';

  // Add the uk-display-inline-block and uk-margin-remove classes to inline
  // containers operation form items.
  $classes = $variables['element']['#attributes']['class'];
  if (in_array('container-inline', $classes) || in_array('form-item-operation', $classes)) {
    $variables['element']['#attributes']['class'][] = 'uk-display-inline-block';
    $variables['element']['#attributes']['class'][] = 'uk-margin-remove';
  }
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
      $classes[] = 'uk-display-inline-block';
      $classes[] = 'uk-margin';
      break;
  }

  $variables['classes_array'] = $classes;

  if ($variables['element']['#field_name'] == 'field_tags') {
    foreach ($variables['items'] as $delta => $item) {
      $variables['item_attributes_array'][$delta]['class'][] = 'field-item';
      $variables['item_attributes_array'][$delta]['class'][] = $delta % 2 ? 'odd' : 'even';
    }
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_fieldset().
 */
function uikit_preprocess_fieldset(&$variables) {
  $collapsible = isset($variables['element']['#collapsible']) && $variables['element']['#collapsible'];
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

    // Retrieve the accordion component CDN assets.
    uikit_get_cdn_asset('accordion');
  }
  elseif ($format_fieldset) {
    $variables['theme_hook_suggestions'][] = 'fieldset__format';
  }
  else {
    $variables['theme_hook_suggestions'][] = 'fieldset';
    $variables['element']['#attributes']['class'][] = 'uk-form-row';
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_form().
 */
function uikit_preprocess_form(&$variables) {
  $attributes = $variables['element']['#attributes'];

  // Make sure the class attribute is an array. If not we take the class set
  // and add it to an array. This is a special case issue caused by the
  // api_search module, and should not be a common problem.
  if (isset($attributes['class']) && !is_array($attributes['class'])) {
    $class = $attributes['class'];
    $variables['element']['#attributes']['class'] = array($class);
  }

  // Add the uk-form class to all forms.
  $variables['element']['#attributes']['class'][] = 'uk-form';
  $variables['element']['#attributes']['class'][] = 'uk-form-stacked';

  // Retrieve the advanced form component CDN assets.
  uikit_get_cdn_asset('form-advanced');
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
  $classes = isset($variables['attributes']['class']) ? $variables['attributes']['class'] : array();

  // Add uk-subnav and uk-subnav-line classes to inline links.
  $inline = in_array('inline', $classes);

  if ($inline) {
    $variables['attributes']['class'][] = 'uk-subnav';
    $variables['attributes']['class'][] = 'uk-subnav-line';
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_menu_link().
 */
function uikit_preprocess_menu_link(&$variables) {
  $depth = $variables['element']['#original_link']['depth'];
  $href = $variables['element']['#href'];
  $theme = $variables['element']['#theme'];

  // Define #hidden variable with default value of FALSE.
  $variables['element']['#hidden'] = FALSE;

  if ($theme == 'menu_link__navbar' && $href == '<uk-nav-header>' && $depth == 1) {
    // Top-level nav headers should be hidden for navbar menu links.
    $variables['element']['#hidden'] = TRUE;
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_menu_local_tasks().
 */
function uikit_preprocess_menu_local_tasks(&$variables) {
  global $theme_key;
  // Get the local task styles.
  $primary_style = UIkit::getThemeSetting('primary_tasks_style', $theme_key);
  $secondary_style = UIkit::getThemeSetting('secondary_tasks_style', $theme_key);

  // Set the default attributes.
  $variables['primary_attributes_array'] = array(
    'id' => 'primary-local-tasks',
  );
  $variables['secondary_attributes_array'] = array(
    'id' => 'secondary-local-tasks',
    'class' => array('uk-subnav'),
  );

  // Add additional styling from theme settings.
  if ($primary_style == 'uk-tab') {
    $variables['primary_attributes_array']['class'][] = $primary_style;
  }
  else {
    $variables['primary_attributes_array']['class'][] = 'uk-subnav';

    if ($primary_style != '0') {
      $variables['primary_attributes_array']['class'][] = $primary_style;
    }
  }
  if ($secondary_style) {
    $variables['secondary_attributes_array']['class'][] = $secondary_style;
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_password().
 */
function uikit_preprocess_password(&$variables) {
  // Define size attribute for password fields for consistent styling.
  $variables['element']['#attributes']['size'] = 25;
  $element = $variables['element'];

  if (isset($element['#parents']) && !empty($element['#validated']) && form_get_error($element)) {
    $variables['element']['#attributes']['class'][] = 'uk-form-danger';
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_radio().
 */
function uikit_preprocess_radio(&$variables) {
  $element = $variables['element'];

  if (isset($element['#parents']) && !empty($element['#validated']) && form_get_error($element)) {
    $variables['element']['#attributes']['class'][] = 'uk-form-danger';
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_select().
 */
function uikit_preprocess_select(&$variables) {
  $element = $variables['element'];

  if (isset($element['#parents']) && !empty($element['#validated']) && form_get_error($element)) {
    $variables['element']['#attributes']['class'][] = 'uk-form-danger';
  }
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
 * Implements hook_preprocess_HOOK() for theme_textarea().
 */
function uikit_preprocess_textarea(&$variables) {
  $element = $variables['element'];

  if (isset($element['#parents']) && !empty($element['#validated']) && form_get_error($element)) {
    $variables['element']['#attributes']['class'][] = 'uk-form-danger';
  }
}

/**
 * Implements template_preprocess_username().
 */
function uikit_preprocess_username(&$variables) {
  global $language;
  $user_language = isset($variables['attributes_array']['xml:lang']);

  if ($user_language) {
    // Provide a proper lang attribute to username elements.
    $lang = $variables['attributes_array']['xml:lang'];
    unset($variables['attributes_array']['xml:lang']);
    $variables['attributes_array']['lang'] = !empty($lang) ? $lang : $language->language;
  }
}
