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

use Drupal\uikit\UIkit;
use Drupal\Core\Template\Attribute;
use Drupal\block\Entity\Block;

/**
 * Implements template_preprocess_page().
 */
function uikit_preprocess_page(&$variables) {
  // Attach the UIkit framework, Font Awesome and base theme libraries to all
  // pages.
  $variables['#attached']['library'][] = UIkit::getUIkitLibrary();
  $variables['#attached']['library'][] = 'uikit/font-awesome';
  $variables['#attached']['library'][] = 'uikit/global-style';

  // Assign new header attributes.
  $variables['header_attributes'] = new Attribute();
  $variables['header_attributes']['id'] = 'page--header';
  $variables['header_attributes']['class'] = array();

  // Add classes to header attributes based on theme settings.
  $navbar_container = UIkit::getThemeSetting('navbar_container');
  if ($navbar_container) {
    $variables['header_attributes']['class'][] = 'uk-container';
  }
  $navbar_centering = UIkit::getThemeSetting('navbar_centering');
  if ($navbar_centering) {
    $variables['header_attributes']['class'][] = 'uk-container-center';
  }

  // Assign new navbar attributes.
  $variables['navbar_attributes'] = new Attribute();
  $variables['navbar_attributes']['id'] = 'page--navbar';
  $variables['navbar_attributes']['class'] = array('uk-navbar');

  // Add classes to navbar attribtues based on theme settings.
  $navbar_attached = UIkit::getThemeSetting('navbar_attached');
  if ($navbar_attached) {
    $variables['navbar_attributes']['class'][] = 'uk-navbar-attached';
  }
  $navbar_margin_top = UIkit::getThemeSetting('navbar_margin_top');
  if ($navbar_margin_top) {
    $variables['navbar_attributes']['class'][] = $navbar_margin_top;
  }
  $navbar_margin_bottom = UIkit::getThemeSetting('navbar_margin_bottom');
  if ($navbar_margin_bottom) {
    $variables['navbar_attributes']['class'][] = $navbar_margin_bottom;
  }

  // Assign new page attributes.
  $variables['page_attributes'] = new Attribute();
  $variables['page_attributes']['id'] = 'page';
  $variables['page_attributes']['class'] = array();

  // Add classes to page attribtues based on theme settings.
  $page_container = UIkit::getThemeSetting('page_container');
  if ($page_container) {
    $variables['page_attributes']['class'][] = 'uk-container';
  }
  $page_centering = UIkit::getThemeSetting('page_centering');
  if ($page_centering) {
    $variables['page_attributes']['class'][] = 'uk-container-center';
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
    $variables['sidebar_first_attributes']['class'] = array();
    foreach ($grid_classes['sidebar']['first'] as $sidebar_first_class) {
      $variables['sidebar_first_attributes']['class'][] = $sidebar_first_class;
    }
  }
  if ($right_sidebar) {
    // Add right sidebar grid classes.
    $variables['sidebar_second_attributes'] = new Attribute();
    $variables['sidebar_second_attributes']['id'] = 'page--sidebar-second';
    $variables['sidebar_second_attributes']['class'] = array();
    foreach ($grid_classes['sidebar']['second'] as $sidebar_second_class) {
      $variables['sidebar_second_attributes']['class'][] = $sidebar_second_class;
    }
  }
}

/**
 * Implements template_preprocess_block().
 */
function uikit_preprocess_block(&$variables) {
  $system_menu_block = $variables['base_plugin_id'] == 'system_menu_block';
  $block = Block::load($variables['elements']['#id']);
  $region = $block->getRegion();

  if ($system_menu_block) {
    switch ($region) {
      case 'navbar':
        // Define #theme variable for navbar menus.
        $variables['content']['#theme'] = 'menu__navbar';
        break;

      case 'offcanvas':
        // Define #theme variable for offcanvas menus.
        $variables['content']['#theme'] = 'menu__offcanvas';
        break;
    }
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
    $variables['breadcrumb'][] = array(
      'text' => $page_title,
      'active' => TRUE,
    );
  }
}

/**
 * Implements template_preprocess_details().
 */
function uikit_preprocess_details(&$variables) {
  $variables['#attached']['library'][] = UIkit::getUIkitComponent('accordion');
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
 * Implements template_preprocess_form_element().
 */
function uikit_preprocess_form_element(&$variables) {
  $element = $variables['element'];

  // Grouped form elements do not need the uk-form-row class. This adds a
  // grouped variable to use in form-element.html.twig.
  $groups = isset($element['#groups']) && is_array($element['#groups']);
  $variables['grouped'] = FALSE;
  if ($groups) {
    $variables['grouped'] = TRUE;
  }
}

/**
 * Implements template_preprocess_form_element() for form-element--advanced.html.twig.
 */
function uikit_preprocess_form_element__advanced(&$variables) {
  $variables['#attached']['library'][] = UIkit::getUIkitComponent('form-advanced');
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
      $dropbutton['link']['#options']['attributes']['class'] = array('uk-button');
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
  $variables['link'] = array(
    'title' => $link['title'],
    'url' => $link['url'],
  );
}

/**
 * Implements hook_preprocess_HOOK() for menu-local-tasks.html.twig.
 */
function uikit_preprocess_menu_local_tasks(&$variables) {
  $primary_tasks_style = UIkit::getThemeSetting('primary_tasks_style');
  $secondary_tasks_style = UIkit::getThemeSetting('secondary_tasks_style');

  // Create new primary tasks attributes.
  $variables['primary_attributes'] = new Attribute();
  $variables['primary_attributes']['class'] = array();
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
  $variables['secondary_attributes']['class'] = array('uk-subnav');
  if ($secondary_tasks_style) {
    // Add uk-subnav-* class to secondary tasks.
    $variables['secondary_attributes']['class'][] = $secondary_tasks_style;
  }
}

/**
 * Implements template_preprocess_user().
 */
function uikit_preprocess_user(&$variables) {
  // $variables['content']['member_for'] doesn't style well. Instead of
  // overriding with CSS, we reformat the markup used.
  $created = $variables['elements']['#user']->getCreatedTime();
  $created_diff = \Drupal::service('date.formatter')->formatTimeDiffSince($created);
  $member_for = '<strong>' . t('Member for') . '</strong> ' . $created_diff;
  $variables['content']['member_for']['#markup'] = $member_for;
}