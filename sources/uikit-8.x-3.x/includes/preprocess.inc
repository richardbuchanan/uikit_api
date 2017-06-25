<?php

/**
 * @file
 * Set up variables to be placed within the template (.html.twig) files.
 *
 * The variables set up here apply to both templates (.html.twig) files and
 * functions (theme_HOOK). These are also used for providing
 * @link https://www.drupal.org/node/2354645 Twig Template naming conventions @endlink.
 *
 * @see process.inc
 */

use Drupal\Component\Utility\Html;
use Drupal\Core\Template\Attribute;
use Drupal\Core\Url;
use Drupal\block\Entity\Block;
use Drupal\uikit\UIkit;

/**
 * Implements template_preprocess_page().
 */
function uikit_preprocess_page(&$variables) {
  // Assign new header attributes.
  $variables['header_attributes'] = new Attribute();
  $variables['header_attributes']['id'] = 'page--header';
  $variables['header_attributes']['class'] = [];

  // Assign new navbar attributes.
  $variables['navbar_attributes'] = new Attribute();
  $variables['navbar_attributes']->setAttribute('id', 'page--navbar');
  $variables['navbar_attributes']->addClass('uk-navbar-container');
  $variables['navbar_attributes']->setAttribute('uk-navbar', '');

  // Assign new page attributes.
  $variables['page_attributes'] = new Attribute();
  $variables['page_attributes']['id'] = 'page';
  $variables['page_attributes']['class'] = [];

  // Add classes to page attribtues based on theme settings.
  $page_container = UIkit::getThemeSetting('page_container');
  if ($page_container) {
    $variables['page_attributes']['class'][] = 'uk-container';
  }
  $page_margin = UIkit::getThemeSetting('page_margin');
  if ($page_margin) {
    $variables['page_attributes']['class'][] = $page_margin;
  }

  // Get the grid classes for the page content and sidebars.
  $left_sidebar = !empty($variables['page']['sidebar_first']);
  $right_sidebar = !empty($variables['page']['sidebar_second']);
  $grid_classes = UIkit::getGridClasses($left_sidebar, $right_sidebar);

  // Add page content grid classes.
  $variables['content_attributes']['id'] = 'page--content';
  foreach ($grid_classes['content'] as $content_class) {
    $variables['content_attributes']['class'][] = $content_class;
  }

  if ($left_sidebar) {
    // Add left sidebar grid classes.
    $variables['sidebar_first_attributes'] = new Attribute();
    $variables['sidebar_first_attributes']['id'] = 'page--sidebar-first';
    $variables['sidebar_first_attributes']['class'] = [];
    foreach ($grid_classes['sidebar']['first'] as $sidebar_first_class) {
      $variables['sidebar_first_attributes']['class'][] = $sidebar_first_class;
    }
  }
  if ($right_sidebar) {
    // Add right sidebar grid classes.
    $variables['sidebar_second_attributes'] = new Attribute();
    $variables['sidebar_second_attributes']['id'] = 'page--sidebar-second';
    $variables['sidebar_second_attributes']['class'] = [];
    foreach ($grid_classes['sidebar']['second'] as $sidebar_second_class) {
      $variables['sidebar_second_attributes']['class'][] = $sidebar_second_class;
    }
  }
}

/**
 * Implements template_preprocess_region().
 */
function uikit_preprocess_region(&$variables) {
  // Provide an id attribute to help themers.
  $region = $variables['region'];
  $variables['attributes']['id'] = "region--$region";

  if ($variables['region'] == 'navbar') {
    $variables['content_left'] = [];
    $variables['content_center'] = [];
    $variables['content_right'] = [];

    foreach ($variables['elements'] as $id => $element) {
      if (is_array($element) && isset($element['#id'])) {
        $block = Block::load($element['#id']);
        $block_navbar_alignment = $block->getThirdPartySetting('uikit_components', 'uikit_navbar_alignment');
        $navbar_alignment = $block_navbar_alignment ? $block_navbar_alignment : 'left';

        switch ($navbar_alignment) {
          case 'left':
            $variables['content_left'][$id] = [
              '#markup' => render($element),
            ];
            break;

          case 'center':
            $variables['content_center'][$id] = [
              '#markup' => render($element),
            ];
            break;

          case 'right':
            $variables['content_right'][$id] = [
              '#markup' => render($element),
            ];
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
  // Provide an id attribute to help themers.
  $id = $variables['elements']['#id'];
  $id = Html::cleanCssIdentifier($id);
  $variables['attributes']['id'] = $id;

  $base_plugin_id = $variables['base_plugin_id'];
  $system_menu_block = $base_plugin_id == 'system_menu_block';
  $block = Block::load($variables['elements']['#id']);
  $region = $block->getRegion();

  switch ($region) {
    case 'navbar':
      if ($system_menu_block) {
        // Define #theme variable for navbar menus.
        $variables['content']['#theme'] = 'menu__navbar';
      }
      break;

    case 'offcanvas':
      if ($system_menu_block) {
        // Define #theme variable for offcanvas menus.
        $variables['content']['#theme'] = 'menu__offcanvas';
      }
      break;
  }
}

/**
 * Implements template_preprocess_breadcrumb().
 */
function uikit_preprocess_breadcrumb(&$variables) {
  // Add bool variable for breadcrumb display.
  $variables['display_breadcrumbs'] = UIkit::getThemeSetting('display_breadcrumbs');

  // Remove "Home" breadcrumb if disabled in the theme settings.
  $breadcrumb_home_link = UIkit::getThemeSetting('breakcrumbs_home_link');
  if (!$breadcrumb_home_link) {
    array_shift($variables['breadcrumb']);
  }

  if (UIkit::getThemeSetting('breakcrumbs_current_page')) {
    foreach ($variables['breadcrumb'] as $key => $breadcrumb) {
      // Set all other items as not being active.
      $variables['breadcrumb'][$key]['active'] = FALSE;
    }

    // Display the current page title if enabled in the theme settings and set
    // it as being active.
    $page_title = UIkit::getPageTitle();
    $variables['breadcrumb'][] = [
      'text' => $page_title,
      'active' => TRUE,
    ];
  }
}

/**
 * Implements template_preprocess_comment().
 */
function uikit_preprocess_comment(&$variables) {
  $indented = $variables['elements']['#comment_indent'];
  $variables['indented'] = FALSE;

  if ($indented) {
    $variables['indented'] = TRUE;
  }
}

/**
 * Implements hook_preprocess_HOOK() for feed-icon.html.twig.
 *
 * Feed icon on the front page is missing the site name, as reported in
 * @link https://www.drupal.org/node/2082657 Feed icon on the front page misses site title @endlink.
 * We are following this issue so we can make the appropriate changes when the
 * issue is fixed.
 */
function uikit_preprocess_feed_icon(&$variables) {
  $config = \Drupal::config('system.site');
  $variables['site_name'] = $config->get('name');
}

/**
 * Implements template_preprocess_field() for field--comment.html.twig.
 */
function uikit_preprocess_field__comment(&$variables) {
  $comments = $variables['comments'];
  $comment_count = 0;

  foreach ($comments as $comment) {
    if (isset($comment['#comment'])) {
      $comment_count++;
    }
  }

  $variables['comment_count'] = $comment_count;
}

/**
 * Implements template_preprocess_form_element().
 */
function uikit_preprocess_form_element(&$variables) {
  $element = $variables['element'];
  $type = $element['#type'];

  // Grouped form elements do not need the uk-margin class. This adds a
  // grouped variable to use in form-element.html.twig.
  $groups = isset($element['#groups']) && is_array($element['#groups']);
  $variables['grouped'] = FALSE;
  if ($groups) {
    $variables['grouped'] = TRUE;
  }

  // Perform various changes to the variables for advanced form elements.
  $form_advanced = $type == 'checkbox' || $type == 'radio';
  $variables['label_text'] = '';
  if ($form_advanced) {
    if (is_object($variables['label']['#title'])) {
      $label = $variables['label']['#title']->getUntranslatedString();
    }
    else {
      $label = $variables['label']['#title'];
    }
    $variables['label_text'] = t('@label', ['@label' => $label]);
  }
}

/**
 * Implements hook_preprocess_HOOK() for input.html.twig.
 */
function uikit_preprocess_input(&$variables) {
  $element = $variables['element'];
  $errors = FALSE;

  if (isset($element['#parents']) && isset($element['#errors']) && !empty($element['#validated'])) {
    $errors = TRUE;
  }

  $variables['errors'] = $errors;
}

/**
 * Implements template_preprocess_links() for links--comment.html.twig.
 */
function uikit_preprocess_links__comment(&$variables) {
  foreach ($variables['links'] as $key => $link) {
    if (isset($link['link'])) {
      $url = $link['link']['#url']->toString();
      $title = $link['text']->getUntranslatedString();
      $variables['links'][$key]['link'] = [
        'title' => t('@title', ['@title' => $title]),
      ];
      $variables['links'][$key]['link']['attributes'] = new Attribute();
      $variables['links'][$key]['link']['attributes']->setAttribute('href', $url);
      $variables['links'][$key]['link']['attributes']->addClass('uk-link-muted');
    }
  }
}

/**
 * Implements template_preprocess_links() for links--dropbutton.html.twig.
 */
function uikit_preprocess_links__dropbutton(&$variables) {
  $links = $variables['links'];
  $multiple = count($links) > 1 ? TRUE : FALSE;
  $variables['multiple'] = $multiple;

  if ($multiple) {
    // Shift the first link off the array to use it as the dropbutton link.
    $dropbutton = array_shift($links);

    if (isset($dropbutton['link'])) {
      // Add the uk-button class to the dropbutton link.
      $dropbutton['link']['#options']['attributes']['class'] = ['uk-button'];
    }

    $variables['dropbutton'] = $dropbutton;
  }
  else {
    foreach ($links as $key => $item) {
      if (isset($item['link'])) {
        // Links not in the dropbutton group need the uk-button class added.
        $links[$key]['link']['#options']['attributes']['class'][] = 'uk-button';
      }
    }
  }

  // Assign new links with the first link shifted off the array to provide the
  // dropdown menu links.
  $variables['links'] = $links;
}

/**
 * Implements template_preprocess_menu_local_action().
 */
function uikit_preprocess_menu_local_action(&$variables) {
  $link = $variables['element']['#link'];

  // Set the link variable for menu-local-action.html.twig.
  $variables['link'] = [
    'title' => $link['title'],
    'url' => $link['url'],
  ];
}

/**
 * Implements hook_preprocess_HOOK() for menu-local-tasks.html.twig.
 */
function uikit_preprocess_menu_local_tasks(&$variables) {
  $primary_tasks_style = UIkit::getThemeSetting('primary_tasks_style');
  $secondary_tasks_style = UIkit::getThemeSetting('secondary_tasks_style');

  // Create new primary tasks attributes.
  $variables['primary_attributes'] = new Attribute();
  $variables['primary_attributes']['class'] = [];
  if ($primary_tasks_style == 'uk-tab') {
    // Add uk-tab class to primary tasks.
    $variables['primary_attributes']['class'][] = 'uk-tab';
  }
  else {
    // Add uk-subnav class to primary tasks.
    $variables['primary_attributes']['class'][] = 'uk-subnav';
    if ($primary_tasks_style) {
      // Add uk-subnav-* class to primary tasks.
      $variables['primary_attributes']['class'][] = $primary_tasks_style;
    }
  }

  // Create new secondary tasks attributes.
  $variables['secondary_attributes'] = new Attribute();
  $variables['secondary_attributes']['class'] = ['uk-subnav'];
  if ($secondary_tasks_style) {
    // Add uk-subnav-* class to secondary tasks.
    $variables['secondary_attributes']['class'][] = $secondary_tasks_style;
  }
}

/**
 * Implements hook_preprocess_HOOK() for menu--navbar.html.twig
 */
function uikit_preprocess_menu__navbar(&$variables) {
  $items = $variables['items'];
  $current_url = Url::fromRoute('<current>');
  $current_path = $current_url->toString();

  foreach ($items as $key => $item) {
    $variables['items'][$key]['has_url'] = TRUE;
    $route = $item['url']->getRouteName();
    $is_active = FALSE;

    if ($route == '<none>') {
      // <none> routes do not have a URL.
      $variables['items'][$key]['has_url'] = FALSE;
    }

    if ($item['url']->toString() == '/user') {
      $uid = \Drupal::currentUser()->id();

      if ($uid && $current_path == "/user/$uid") {
        $is_active = TRUE;
      }
    }

    if ($is_active && !$item['attributes']->hasClass('uk-active')) {
      $item['attributes']->addClass('uk-active');
    }

    if ($item['below']) {
      foreach ($item['below'] as $below_key => $below_item) {
        // Set is_divider and is_header variables to FALSE.
        $variables['items'][$key]['below'][$below_key]['is_divider'] = FALSE;
        $variables['items'][$key]['below'][$below_key]['is_header'] = FALSE;

        // Get the menu item options and menu_item_type, if set. menu_item_type
        // is set by the UIkit Components module.
        $options = $below_item['url']->getOptions();
        $menu_item_type = isset($options['menu_item_type']) ? $options['menu_item_type'] : 0;

        if ($menu_item_type) {
          switch ($menu_item_type) {
            case 'nav_divider':
              // Add uk-nav-divider class and set is_divider to TRUE for
              // menu--navbar.html.twig.
              $variables['items'][$key]['below'][$below_key]['attributes']->addClass('uk-nav-divider');
              $variables['items'][$key]['below'][$below_key]['is_divider'] = TRUE;
              break;

            case 'nav_header':
              // Add uk-nav-header class and set is_header to TRUE for
              // menu--navbar.html.twig.
              $variables['items'][$key]['below'][$below_key]['attributes']->addClass('uk-nav-header');
              $variables['items'][$key]['below'][$below_key]['is_header'] = TRUE;
              break;
          }
        }
      }
    }
  }
}

/**
 * Implements hook_preprocess_HOOK() for menu--offcanvas.html.twig
 */
function uikit_preprocess_menu__offcanvas(&$variables) {
  $items = $variables['items'];

  foreach ($items as $key => $item) {
    $variables['items'][$key]['display_item'] = TRUE;
    $variables['items'][$key]['has_url'] = TRUE;
    $route = $item['url']->getRouteName();

    if ($route == '<none>') {
      $variables['items'][$key]['has_url'] = FALSE;
    }

    if ($item['below']) {
      $variables['items'][$key]['has_url'] = FALSE;

      foreach ($item['below'] as $below_key => $below_item) {
        // Set is_divider and is_header variables to FALSE.
        $variables['items'][$key]['below'][$below_key]['display_item'] = TRUE;
        $variables['items'][$key]['below'][$below_key]['has_url'] = TRUE;

        // Get the menu item options and menu_item_type, if set. menu_item_type
        // is set by the UIkit Components module.
        $options = $below_item['url']->getOptions();
        $menu_item_type = isset($options['menu_item_type']) ? $options['menu_item_type'] : 0;

        if ($menu_item_type) {
          switch ($menu_item_type) {
            case 'nav_divider':
            case 'nav_header':
            $variables['items'][$key]['below'][$below_key]['display_item'] = FALSE;
              break;
          }
        }
      }
    }
  }
}
