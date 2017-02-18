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

/**
 * Implements template_preprocess_html().
 */
function uikit_preprocess_html(&$variables) {
  global $theme_key;
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

  if (theme_get_setting('x_ua_compatible', $theme_key)) {
    $meta_x_ua_compatible = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => 'x-ua-compatible',
        'content' => 'IE=' . theme_get_setting('x_ua_compatible', $theme_key),
      ),
      '#weight' => -9998,
    );

    drupal_add_html_head($meta_x_ua_compatible, 'uikit_x_ua_compatible');
  }

  // Get viewport metadata settings for mobile devices.
  $device_width_ratio = theme_get_setting('viewport_device_width_ratio', $theme_key);
  $custom_device_width = theme_get_setting('viewport_custom_width', $theme_key);
  $device_height_ratio = theme_get_setting('viewport_device_height_ratio', $theme_key);
  $custom_device_height = theme_get_setting('viewport_custom_height', $theme_key);
  $initial_scale = theme_get_setting('viewport_initial_scale', $theme_key);
  $maximum_scale = theme_get_setting('viewport_maximum_scale', $theme_key);
  $minimum_scale = theme_get_setting('viewport_minimum_scale', $theme_key);
  $user_scalable = theme_get_setting('viewport_user_scalable', $theme_key);
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
 * Implements template_preprocess_page().
 */
function uikit_preprocess_page(&$variables) {
  global $theme_key;

  $sidebar_first = isset($variables['page']['sidebar_first']) ? $variables['page']['sidebar_first'] : '';
  $sidebar_second = isset($variables['page']['sidebar_second']) ? $variables['page']['sidebar_second'] : '';
  $standard_layout = theme_get_setting('standard_sidebar_positions', $theme_key);
  $tablet_layout = theme_get_setting('tablet_sidebar_positions', $theme_key);
  $mobile_layout = theme_get_setting('mobile_sidebar_positions', $theme_key);

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
  if (theme_get_setting('page_container', $theme_key)) {
    $page_container_attributes['class'][] = 'uk-container';
  }
  if (theme_get_setting('page_centering', $theme_key)) {
    $page_container_attributes['class'][] = 'uk-container-center';
  }
  if (theme_get_setting('page_margin', $theme_key)) {
    $page_container_attributes['class'][] = theme_get_setting('page_margin', $theme_key);
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
  if (theme_get_setting('navbar_container', $theme_key)) {
    $variables['header_attributes_array']['class'][] = 'uk-container';
  }
  if (theme_get_setting('navbar_centering', $theme_key)) {
    $variables['header_attributes_array']['class'][] = 'uk-container-center';
  }

  // Define navbar attributes.
  $variables['navbar_attributes_array'] = array(
    'id' => 'page-navbar',
    'class' => array('uk-navbar'),
  );

  if (theme_get_setting('navbar_attached', $theme_key)) {
    $variables['navbar_attributes_array']['class'][] = 'uk-navbar-attached';
  }

  if (theme_get_setting('navbar_margin_top', $theme_key)) {
    switch (theme_get_setting('navbar_margin_top', $theme_key)) {
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

  if (theme_get_setting('navbar_margin_bottom', $theme_key)) {
    switch (theme_get_setting('navbar_margin_bottom', $theme_key)) {
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
    $main_menu_name = variable_get('menu_main_links_source', 'main-menu');
    $main_menu_tree = menu_tree($main_menu_name);
    $main_menu_tree['#theme_wrappers'] = array('menu_tree__main_menu');
    $main_menu_tree__offcanvas = $main_menu_tree;
    $main_menu_tree__offcanvas['#theme_wrappers'] = array('menu_tree__main_menu__offcanvas');

    foreach ($main_menu_tree as $key => $value) {
      $below = is_array($value) && (isset($value['#below']) && !empty($value['#below'])) ? $value['#below'] : 0;

      if ($below) {
        $main_menu_tree[$key]['#below']['#theme_wrappers'] = array('menu_tree__main_menu__dropdown');
      }
    }

    foreach ($main_menu_tree__offcanvas as $key => $value) {
      $theme_menu_link = is_array($value) && isset($value['#theme']) ? $value['#theme'] : 0;
      $below = is_array($value) && (isset($value['#below']) && !empty($value['#below'])) ? $value['#below'] : 0;

      if ($theme_menu_link) {
        $main_menu_tree__offcanvas[$key]['#theme'] = 'menu_link__offcanvas';
      }

      if ($below) {
        $main_menu_tree__offcanvas[$key]['#below']['#theme_wrappers'] = array('menu_tree__main_menu__offcanvas__dropdown');
      }
    }

    if (theme_get_setting('main_menu_alignment', $theme_key)) {
      $navbar_main .= '<div id="navbar-flip--main-menu" class="uk-navbar-flip">';
    }

    $navbar_main .= drupal_render($main_menu_tree);

    if (theme_get_setting('main_menu_alignment', $theme_key)) {
      $navbar_main .= '</div>';
    }

    $offcanvas_main = drupal_render($main_menu_tree__offcanvas);
  }

  if ($variables['secondary_menu']) {
    $secondary_menu_name = variable_get('menu_secondary_links_source', 'user-menu');
    $secondary_menu_tree = menu_tree($secondary_menu_name);
    $secondary_menu_tree['#theme_wrappers'] = array('menu_tree__secondary_menu');
    $secondary_menu_tree__offcanvas = $secondary_menu_tree;
    $secondary_menu_tree__offcanvas['#theme_wrappers'] = array('menu_tree__secondary_menu__offcanvas');

    foreach ($secondary_menu_tree as $key => $value) {
      $below = is_array($value) && (isset($value['#below']) && !empty($value['#below'])) ? $value['#below'] : 0;

      if ($below) {
        $secondary_menu_tree[$key]['#below']['#theme_wrappers'] = array('menu_tree__secondary_menu__dropdown');
      }
    }

    foreach ($secondary_menu_tree__offcanvas as $key => $value) {
      $theme_menu_link = is_array($value) && isset($value['#theme']) ? $value['#theme'] : 0;
      $below = is_array($value) && (isset($value['#below']) && !empty($value['#below'])) ? $value['#below'] : 0;

      if ($theme_menu_link) {
        $main_menu_tree__offcanvas[$key]['#theme'] = 'menu_link__offcanvas';
      }

      if ($below) {
        $main_menu_tree__offcanvas[$key]['#below']['#theme_wrappers'] = array('menu_tree__secondary_menu__offcanvas__dropdown');
      }
    }

    if (theme_get_setting('secondary_menu_alignment', $theme_key)) {
      $navbar_secondary .= '<div id="navbar-flip--secondary-menu" class="uk-navbar-flip">';
    }

    $navbar_secondary .= drupal_render($secondary_menu_tree);

    if (theme_get_setting('secondary_menu_alignment', $theme_key)) {
      $navbar_secondary .= '</div>';
    }

    $offcanvas_secondary = drupal_render($secondary_menu_tree__offcanvas);
  }

  // Place additional menus in the navbar from the theme settings.
  $menus = menu_get_menus();
  foreach ($menus as $menu_name => $menu_title) {
    $menu_links = str_replace('-', '_', $menu_name);

    if (theme_get_setting($menu_name . '_in_navbar', $theme_key)) {
      $navbar_menu = menu_navigation_links($menu_name);

      if (theme_get_setting($menu_links . '_additional_alignment', $theme_key)) {
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
      if (theme_get_setting($menu_links . '_alignment', $theme_key)) {
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
  $variables['display_breadcrumb'] = theme_get_setting('display_breadcrumbs', $theme_key);
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

  $variables['wrapper_attributes_array'] = array(
    'id' => 'region-' . $wrapper_id . '-wrapper',
    'class' => array('region-wrapper'),
  );

  // Get all regions for the theme.
  $regions = system_region_list($theme_key);

  foreach ($regions as $key => $value) {
    // Get the settings for each region being used.
    if ($region == $key) {
      $style_setting = theme_get_setting($key . '_style', $theme_key);
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
  $variables['content_attributes_array']['class'][] = 'uk-margin';
}

/**
 * Implements template_preprocess_HOOK().
 */
function uikit_preprocess_breadcrumb(&$variables) {
  global $theme_key;

  // Remove home link from breadcrumb if disabled in theme settings.
  if (!theme_get_setting('breakcrumbs_home_link', $theme_key)) {
    array_shift($variables['breadcrumb']);
  }
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
  global $theme_key;
  $comment = $variables['elements']['#comment'];
  $node = $variables['elements']['#node'];

  // Check if user picture in comments is enabled.
  $comment_picture = theme_get_setting('toggle_comment_user_picture', $theme_key) ? 1 : 0;

  // Check if user pictures are enabled.
  $user_pictures = variable_get('user_pictures') ? 1 : 0;

  // Chech if a default picture has been set.
  $user_picture_default = !empty(variable_get('user_picture_default')) ? 1 : 0;

  // Add comment classes.
  $variables['classes_array'][] = 'uk-comment';
  if ($variables['elements']['#comment']->divs > 0) {
    $variables['classes_array'][] = 'uk-comment-primary';
  }
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

  if ($comment_picture && $user_pictures && $user_picture_default && empty($variables['picture'])) {
    // Provide a default image when the user does not have a picture uploaded.
    if (empty($variables['picture'])) {
      $default = ' data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4NCjwhLS0gR2VuZXJhdG9yOiBBZG9iZSBJbGx1c3RyYXRvciAxNi4wLjQsIFNWRyBFeHBvcnQgUGx1Zy1JbiAuIFNWRyBWZXJzaW9uOiA2LjAwIEJ1aWxkIDApICAtLT4NCjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+DQo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkViZW5lXzEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4Ig0KCSB3aWR0aD0iNTBweCIgaGVpZ2h0PSI1MHB4IiB2aWV3Qm94PSIwIDAgNTAgNTAiIGVuYWJsZS1iYWNrZ3JvdW5kPSJuZXcgMCAwIDUwIDUwIiB4bWw6c3BhY2U9InByZXNlcnZlIj4NCjxyZWN0IGZpbGw9IiNGRkZGRkYiIHdpZHRoPSI1MCIgaGVpZ2h0PSI1MCIvPg0KPGc+DQoJPHBhdGggZmlsbD0iI0UwRTBFMCIgZD0iTTQ1LjQ1LDQxLjM0NWMtMC4yMDktMS4xNjYtMC40NzMtMi4yNDYtMC43OTEtMy4yNDJjLTAuMzE5LTAuOTk2LTAuNzQ3LTEuOTY3LTEuMjg2LTIuOTE0DQoJCWMtMC41MzgtMC45NDYtMS4xNTUtMS43NTMtMS44NTItMi40MmMtMC42OTktMC42NjctMS41NS0xLjItMi41NTYtMS41OThzLTIuMTE3LTAuNTk4LTMuMzMyLTAuNTk4DQoJCWMtMC4xNzksMC0wLjU5NywwLjIxNC0xLjI1NSwwLjY0MmMtMC42NTcsMC40MjktMS4zOTksMC45MDctMi4yMjYsMS40MzRjLTAuODI3LDAuNTI4LTEuOTAzLDEuMDA2LTMuMjI3LDEuNDM0DQoJCWMtMS4zMjUsMC40MjktMi42NTUsMC42NDMtMy45ODksMC42NDNjLTEuMzM0LDAtMi42NjQtMC4yMTQtMy45ODktMC42NDNjLTEuMzI1LTAuNDI4LTIuNDAxLTAuOTA2LTMuMjI3LTEuNDM0DQoJCWMtMC44MjgtMC41MjctMS41NjktMS4wMDUtMi4yMjYtMS40MzRjLTAuNjU4LTAuNDI4LTEuMDc2LTAuNjQyLTEuMjU1LTAuNjQyYy0xLjIxNiwwLTIuMzI2LDAuMTk5LTMuMzMyLDAuNTk4DQoJCWMtMS4wMDYsMC4zOTgtMS44NTgsMC45MzEtMi41NTQsMS41OThjLTAuNjk5LDAuNjY3LTEuMzE1LDEuNDc0LTEuODUzLDIuNDJjLTAuNTM4LDAuOTQ3LTAuOTY3LDEuOTE3LTEuMjg1LDIuOTE0DQoJCXMtMC41ODMsMi4wNzYtMC43OTIsMy4yNDJjLTAuMjA5LDEuMTY1LTAuMzQ5LDIuMjUxLTAuNDE4LDMuMjU2Yy0wLjA3LDEuMDA2LTAuMTA0LDIuMS0wLjEwNCwzLjE1NUMzLjkwMSw0OC41NCwzLjk4Nyw0OSw0LjE0Myw1MA0KCQloNDEuNTg5YzAuMTU2LTEsMC4yNDItMS40NiwwLjI0Mi0yLjI0M2MwLTEuMDU1LTAuMDM1LTIuMTE4LTAuMTA1LTMuMTI0QzQ1Ljc5OSw0My42MjcsNDUuNjYsNDIuNTEsNDUuNDUsNDEuMzQ1eiIvPg0KCTxwYXRoIGZpbGw9IiNFMEUwRTAiIGQ9Ik0yNC45MzgsMzIuNDg1YzMuMTY3LDAsNS44NzEtMS4xMjEsOC4xMTMtMy4zNjFjMi4yNDEtMi4yNDIsMy4zNjEtNC45NDUsMy4zNjEtOC4xMTMNCgkJcy0xLjEyMS01Ljg3Mi0zLjM2MS04LjExMmMtMi4yNDItMi4yNDEtNC45NDYtMy4zNjItOC4xMTMtMy4zNjJzLTUuODcyLDEuMTIxLTguMTEyLDMuMzYyYy0yLjI0MiwyLjI0MS0zLjM2Miw0Ljk0NS0zLjM2Miw4LjExMg0KCQlzMS4xMiw1Ljg3MSwzLjM2Miw4LjExM0MxOS4wNjUsMzEuMzY1LDIxLjc3MSwzMi40ODUsMjQuOTM4LDMyLjQ4NXoiLz4NCjwvZz4NCjwvc3ZnPg0K';
      $variables['picture'] = '<img class="uk-comment-avatar" width="50" height="50" src="' . $default . '">';
    }
  }
  $variables['content']['links']['#attributes']['class'][] = 'uk-float-right';
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
      $classes[] = 'uk-display-inline-block';
      $classes[] = 'uk-margin';
      break;
  }

  $variables['classes_array'] = $classes;
}

/**
 * Implements hook_preprocess_HOOK() for theme_fieldset().
 */
function uikit_preprocess_fieldset(&$variables) {
  global $theme_key;
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
    $uikit_style = theme_get_setting('base_style', $theme_key);
    $accordion_css = 'accordion.min.css';

    switch ($uikit_style) {
      case 'almost-flat':
        $accordion_css = 'accordion.almost-flat.min.css';
        break;

      case 'gradient':
        $accordion_css = 'accordion.gradient.min.css';
        break;
    }

    drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/uikit/2.26.4/css/components/$accordion_css", array(
      'type' => 'external',
      'group' => CSS_THEME,
      'every_page' => TRUE,
      'weight' => -10,
      'version' => '2.26.4',
    ));

    drupal_add_js('//cdnjs.cloudflare.com/ajax/libs/uikit/2.26.4/js/components/accordion.min.js', array(
      'type' => 'external',
      'group' => JS_THEME,
      'every_page' => TRUE,
      'weight' => -10,
      'version' => '2.26.4',
    ));
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
  global $theme_key;

  // Add the uk-form class to all forms.
  $variables['element']['#attributes']['class'][] = 'uk-form';
  $variables['element']['#attributes']['class'][] = 'uk-form-stacked';

  // Retrieve the advanced form component CDN assets.
  $uikit_style = theme_get_setting('base_style', $theme_key);
  $form_advanced_css = 'form-advanced.min.css';

  switch ($uikit_style) {
    case 'almost-flat':
      $form_advanced_css = 'form-advanced.almost-flat.min.css';
      break;

    case 'gradient':
      $form_advanced_css = 'form-advanced.gradient.min.css';
      break;
  }

  drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/uikit/2.26.4/css/components/$form_advanced_css", array(
    'type' => 'external',
    'group' => CSS_THEME,
    'every_page' => TRUE,
    'weight' => -10,
    'version' => '2.26.4',
  ));
}

/**
 * Implements hook_preprocess_HOOK() for theme_item_list().
 */
function uikit_preprocess_item_list(&$variables) {
  // Add the uk-list class to all item lists.
  $variables['attributes']['class'][] = 'uk-list';
}

/**
 * Implements hook_preprocess_HOOK().
 */
function uikit_preprocess_link(&$variables) {
  $path = isset($variables['path']) ? $variables['path'] : 0;
  $path_alias = $path ? drupal_get_path_alias($path) : 0;

  // Remove the path and add some options to <empty> paths for dropdown menu
  // support.
  if ($path && $path_alias == '<empty>') {
    $variables['path'] = '';
    $variables['options']['fragment'] = ' ';
    $variables['options']['external'] = TRUE;
  }
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
 * Implements template_preprocess_HOOK() for theme_menu_link().
 */
function uikit_preprocess_menu_link(&$variables) {
  global $user;

  $classes = isset($variables['element']['#attributes']['class']) ? $variables['element']['#attributes']['class'] : array();
  $expanded = array_keys($classes, 'expanded');
  $leaf = array_keys($classes, 'leaf');
  $active_trail = array_keys($classes, 'active-trail');
  $theme_hook = isset($variables['theme_hook_suggestion']) ? $variables['theme_hook_suggestion'] : 0;

  if ($theme_hook) {
    unset($variables['theme_hook_suggestion']);
    $variables['theme_hook_suggestions'] = array(
      'menu_link',
      $theme_hook,
    );
  }

  // Remove expanded classes.
  foreach ($expanded as $expanded_key) {
    unset($variables['element']['#attributes']['class'][$expanded_key]);
    $variables['element']['#attributes']['class'][] = 'uk-parent';

    if ($theme_hook == 'menu_link__main_menu') {
      $variables['element']['#attributes']['data-uk-dropdown'] = '';
    }

    if ($theme_hook == 'menu_link__offcanvas') {
      $variables['element']['#attributes']['aria-expanded'] = 'false';
    }
  }

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
  global $theme_key;
  // Get the local task styles.
  $primary_style = theme_get_setting('primary_tasks_style', $theme_key);
  $secondary_style = theme_get_setting('secondary_tasks_style', $theme_key);

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
 * Implements tempalte_preprocess_menu_tree().
 */
function uikit_preprocess_menu_tree(&$variables) {
  $theme_hook = isset($variables['theme_hook_suggestion']) ? $variables['theme_hook_suggestion'] : 0;
  $variables['theme_hook_suggestions'] = array('menu_tree');

  if ($theme_hook) {
    unset($variables['theme_hook_suggestion']);
    $variables['theme_hook_suggestions'][] = $theme_hook;
  }
}

/**
 * Preprocess function for theme_uikit_navbar().
 */
function uikit_preprocess_uikit_navbar(&$variables) {
  $items = $variables['items'];

  foreach ($items as $id => $item) {
    foreach ($item as $key => $value) {
      $path = drupal_get_path_alias($variables['items'][$id][$key]['href']);
      $has_attributes = isset($variables['items'][$id][$key]['attributes']);
      $attributes = $has_attributes ? $variables['items'][$id][$key]['attributes'] : array();

      // Append active class.
      if (uikit_get_active_path($path)) {
        $attributes['class'][] = 'uk-active';
      }

      if ($path == '<parent>') {
        $attributes['class'][] = 'uk-parent';
      }

      $variables['items'][$id][$key]['attributes'] = $attributes;
    }
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_password().
 */
function uikit_preprocess_password(&$variables) {
  $variables['element']['#attributes']['size'] = 25;
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
