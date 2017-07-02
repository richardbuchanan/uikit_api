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
use Drupal\Core\StringTranslation\TranslatableMarkup;
use Drupal\Core\Template\Attribute;
use Drupal\block\Entity\Block;
use Drupal\uikit\UIkit;

/**
 * Implements template_preprocess_page().
 */
function uikit_preprocess_page(&$variables) {
  // Attach the UIkit framework and base theme libraries to all pages.
  $variables['#attached']['library'][] = UIkit::getUIkitLibrary();
  $variables['#attached']['library'][] = 'uikit/global-style';

  // Assign new header attributes.
  $variables['header_attributes'] = new Attribute();
  $variables['header_attributes']['id'] = 'page--header';
  $variables['header_attributes']['class'] = [];

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
  $variables['navbar_attributes']['class'] = ['uk-navbar'];

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
  $variables['page_attributes']['class'] = [];

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
      // Get navbar alignment from block settings.
      $variables['navbar_flip'] = $navbar_alignment = $block->getThirdPartySetting('uikit_components', 'uikit_navbar_alignment') ? 1 : 0;

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

  $link = $variables['permalink']->getGeneratedLink();
  preg_match_all('/<a[^>]+href=([\'"])(.+?)\1[^>]*>/i', $link, $permalink);
  $variables['comment_url'] = $permalink[2][0];


  $generated_title_link = $variables['title']->getGeneratedLink();
  preg_match('/<a(.*?)>(.*?)<\/a>/s', $generated_title_link, $matches);
  $link_text = $matches[2] . ' <i class="uk-icon-link"></i>';
  $set_title_link = str_replace($matches[2], $link_text, $generated_title_link);
  $variables['title']->setGeneratedLink($set_title_link);
}

/**
 * Implements template_preprocess_details().
 */
function uikit_preprocess_details(&$variables) {
  // Set the accordion attributes.
  $attributes = $variables['attributes'];
  $accordion_attributes = new Attribute;

  foreach ($attributes as $attribute => $value) {
    if ($attribute != 'class' && $attribute != 'open') {
      $accordion_attributes->setAttribute($attribute, $value);
    }
    elseif ($attribute == 'class') {
      foreach ($value as $class) {
        $accordion_attributes->addClass($class);
      }
    }
  }
  $accordion_attributes->addClass('uk-form-row');
  $accordion_attributes->addClass('uk-accordion');

  // Set the data-uk-accordion attribute based on the #open value.
  $open = isset($variables['element']['#open']) ? $variables['element']['#open'] : FALSE;
  if ($open) {
    $accordion_attributes->setAttribute('data-uk-accordion', '{showfirst: true}');
  }
  else {
    $accordion_attributes->setAttribute('data-uk-accordion', '{showfirst: false}');
  }

  $variables['accordion_attributes'] = $accordion_attributes;

  // Set the accordion title attributes.
  $accordion_title_attributes = new Attribute;
  $accordion_title_attributes->addClass('uk-accordion-title');
  $variables['accordion_title_attributes'] = $accordion_title_attributes;

  // Set the accordion content attributes.
  $accordion_content_attributes = new Attribute;
  $accordion_content_attributes->addClass('uk-accordion-content');
  $variables['accordion_content_attributes'] = $accordion_content_attributes;

  // Set the error classes.
  $error_classes = new Attribute;
  $error_classes->addClass('uk-alert');
  $error_classes->addClass('uk-alert-danger');
  $variables['error_classes'] = $error_classes;

  // Set the description attributes.
  $description_attributes = new Attribute;
  $description_attributes->addClass('uk-form-help-block');
  $description_attributes->addClass('uk-margin-small-bottom');
  $variables['description_attributes'] = $description_attributes;
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
 * Implements template_preprocess_form_element() for form-element--advanced.html.twig.
 */
function uikit_preprocess_form_element__advanced(&$variables) {
  $variables['#attached']['library'][] = UIkit::getUIkitComponent('form-advanced');

  if (is_object($variables['label']['#title'])) {
    $label = $variables['label']['#title']->getUntranslatedString();
  }
  else {
    $label = $variables['label']['#title'];
  }
  $variables['label_text'] = t('@label', ['@label' => $label]);
}

/**
 * Implements template_preprocess_HOOK() for input.html.twig.
 */
function uikit_preprocess_input(&$variables) {
  $element = $variables['element'];
  $errors = FALSE;

  if (isset($element['#parents']) && isset($element['#errors']) && !empty($element['#validated'])) {
    $errors = TRUE;
  }

  $variables['errors'] = $errors;

  if ($variables['element']['#type'] == 'file') {
    $variables['#attached']['library'][] = UIkit::getUIkitComponent('form-file');
    $title = $variables['element']['#title']->getUntranslatedString();
    $variables['title'] = t('@title', ['@title' => $title]);
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

  foreach ($items as $key => $item) {
    $variables['items'][$key]['has_url'] = TRUE;
    $route = $item['url']->getRouteName();

    if ($route == '<none>') {
      $variables['items'][$key]['has_url'] = FALSE;
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

/**
 * Implements template_preprocess_username().
 */
function uikit_preprocess_username(&$variables) {
  $name = $variables['account']->getUsername() ? : \Drupal::config('user.settings')->get('anonymous');
  $title_attribute = new TranslatableMarkup("View @user's profile.", ['@user' => $name]);
  $variables['attributes']['title'] = $title_attribute;
}
