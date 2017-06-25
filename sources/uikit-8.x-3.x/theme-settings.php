<?php

/**
 * @file
 * Provides theme settings for UIkit themes.
 */

use Drupal\Core\Extension\InfoParser;
use Drupal\uikit\UIkit;

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function uikit_form_system_theme_settings_alter(&$form, \Drupal\Core\Form\FormStateInterface $form_state, $form_id = NULL) {
  // General "alters" use a form id. Settings should not be set here. The only
  // thing useful about this is if you need to alter the form for the running
  // theme and *not* the theme setting.
  // @see http://drupal.org/node/943212
  if (isset($form_id)) {
    return;
  }

  // Attach the uikit.admin library from the base theme.
  $form['#attached']['library'][] = 'uikit/uikit';
  $form['#attached']['library'][] = 'uikit/uikit.admin';

  // Get the active theme name.
  $build_info = $form_state->getBuildInfo();
  $active_theme = \Drupal::theme()->getActiveTheme();
  $theme = $active_theme->getName();
  $theme_key = $build_info['args'][0] === $theme ? $build_info['args'][0] : $theme;

  // Build the markup for the layout demos.
  $demo_layout = '<div class="uk-layout-wrapper">';
  $demo_layout .= '<div class="uk-layout-container">';
  $demo_layout .= '<div class="uk-layout-content"></div>';
  $demo_layout .= '<div class="uk-layout-sidebar uk-layout-sidebar-left"></div>';
  $demo_layout .= '<div class="uk-layout-sidebar uk-layout-sidebar-right"></div>';
  $demo_layout .= '</div></div>';

  // Get the sidebar positions for each layout.
  $standard_sidebar_pos = UIkit::getThemeSetting('standard_sidebar_positions', $theme_key);
  $tablet_sidebar_pos = UIkit::getThemeSetting('tablet_sidebar_positions', $theme_key);
  $mobile_sidebar_pos = UIkit::getThemeSetting('mobile_sidebar_positions', $theme_key);

  // Build the markup for the local task demos.
  $demo_local_tasks = '<ul>';
  $demo_local_tasks .= '<li class="uk-active"><a href="#">Item</a></li>';
  $demo_local_tasks .= '<li><a href="#">Item</a></li>';
  $demo_local_tasks .= '<li><a href="#">Item</a></li>';
  $demo_local_tasks .= '<li class="uk-disabled"><a href="#">Disabled</a></li>';
  $demo_local_tasks .= '</ul>';

  // Set the subnav options for primary and secondary tasks.
  $primary_subnav_options = [
    0 => 'Basic subnav',
    'uk-subnav-divider' => 'Subnav divider',
    'uk-subnav-pill' => 'Subnav pill',
    'uk-tab' => 'Tabbed',
  ];
  $secondary_subnav_options = [
    0 => 'Basic subnav',
    'uk-subnav-divider' => 'Subnav divider',
    'uk-subnav-pill' => 'Subnav pill',
  ];

  // Set the region style options.
  $region_style_options = [
    0 => 'No style',
    'panel' => 'Panel',
    'block' => 'Block',
  ];

  // Fetch a list of regions for the current theme.
  $all_regions = system_region_list($theme, $show = REGIONS_VISIBLE);

  // Create markup for UIkit theme information.
  $info_parser = new InfoParser();
  $uikit_theme_info = $info_parser->parse(drupal_get_path('theme', 'uikit') . '/uikit.info.yml');
  $uikit_version = isset($uikit_theme_info['version']) ? $uikit_theme_info['version'] : UIkit::UIKIT_PROJECT_BRANCH;
  $uikit_info = '<div class="uk-container uk-margin-top">';
  $uikit_info .= '<div class="uk-grid">';
  $uikit_info .= '<div class="uk-width-1-1">';
  $uikit_info .= '<div class="uk-text-center"><img src="/' . drupal_get_path('theme', 'uikit') . '/images/uikit-small.png" /></div>';
  $uikit_info .= '<blockquote class="uk-text-small">';
  $uikit_info .= '<p class="uk-text-center">';
  $uikit_info .= '<span class="uk-margin-small-right" uk-icon="quote-right"></span> ' . $uikit_theme_info['description'];
  $uikit_info .= '</p>';
  $uikit_info .= '</blockquote>';
  $uikit_info .= '</div>';
  $uikit_info .= '<div class="uk-width-1-1 uk-margin">';
  $uikit_info .= '<ul class="uk-list uk-width-1-1 uk-text-center" uk-grid>';
  $uikit_info .= '<li class="uk-width-1-1@s uk-width-1-3@m"><a href="' . UIkit::UIKIT_LIBRARY . '" target="_blank">UIkit homepage</a></li>';
  $uikit_info .= '<li class="uk-width-1-1@s uk-width-1-3@m"><a href="' . UIkit::UIKIT_PROJECT . '" target="_blank">Drupal.org project page</a></li>';
  $uikit_info .= '<li class="uk-width-1-1@s uk-width-1-3@m"><a href="' . UIkit::UIKIT_PROJECT_API . '" target="_blank">UIkit API site</a></li>';
  $uikit_info .= '<li class="uk-width-1-1@s uk-width-1-3@m"><strong>UIkit library version</strong>: v' . UIkit::UIKIT_LIBRARY_VERSION . '</li>';
  $uikit_info .= '<li class="uk-width-1-1@s uk-width-1-3@m"><strong>UIkit Drupal version</strong>: ' . $uikit_version . '</li>';
  $uikit_info .= '<li class="uk-width-1-1@s uk-width-1-3@m"><strong>Ported to Drupal by</strong>: <a href="http://richardbuchanan.com" target="_blank">Richard Buchanan</a></li>';
  $uikit_info .= '<li class="uk-width-1-1@s uk-margin-top">UIkit <span class="uk-admin-text-medium">&copy;</span> <a href="http://www.yootheme.com/" target="_blank">YOOtheme</a>, with love and caffeine, under the <a href="http://opensource.org/licenses/MIT" target="_blank">MIT license</a>.</li>';
  $uikit_info .= '<li class="uk-width-1-1@s">UIkit for Drupal <span class="uk-admin-text-medium">&copy;</span> <a href="http://richardbuchanan.com" target="_blank">Richard Buchanan</a></li>';
  $uikit_info .= '</ul>';
  $uikit_info .= '</div></div></div>';

  // Create vertical tabs for all UIkit related settings.
  $form['uikit'] = [
    '#type' => 'vertical_tabs',
    '#prefix' => '<h3>' . t('UIkit Settings') . '</h3>',
    '#weight' => -10,
  ];

  // Layout settings.
  $form['layout'] = [
    '#type' => 'details',
    '#title' => t('Layout'),
    '#description' => t('Apply our fully responsive fluid grid system and panels, common layout parts like blog articles and comments and useful utility classes.'),
    '#group' => 'uikit',
    '#attributes' => [
      'class' => [
        'uikit-layout-settings-form',
      ],
    ],
  ];
  $form['layout']['layout_advanced'] = [
    '#type' => 'checkbox',
    '#title' => t('Show advanced layout settings'),
    '#default_value' => UIkit::getThemeSetting('layout_advanced', $theme_key),
  ];
  $form['layout']['page_layout'] = [
    '#type' => 'details',
    '#title' => t('Page Layout'),
    '#description' => t('Change page layout settings.'),
    '#attributes' => [
      'open' => 'open',
    ],
  ];
  $form['layout']['page_layout']['standard_layout'] = [
    '#type' => 'details',
    '#title' => t('Standard Layout'),
    '#description' => t('Change layout settings for desktops and large screens.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  ];
  $form['layout']['page_layout']['standard_layout']['standard_layout_demo'] = [
    '#type' => 'container',
  ];
  $form['layout']['page_layout']['standard_layout']['standard_layout_demo']['#attributes']['class'][] = 'uk-admin-demo';
  $form['layout']['page_layout']['standard_layout']['standard_layout_demo']['#attributes']['class'][] = 'uk-layout-' . $standard_sidebar_pos;
  $form['layout']['page_layout']['standard_layout']['standard_layout_demo']['standard_demo'] = [
    '#markup' => '<div id="standard-layout-demo">' . $demo_layout . '</div>',
  ];
  $form['layout']['page_layout']['standard_layout']['standard_sidebar_positions'] = [
    '#type' => 'radios',
    '#title' => t('Sidebar positions'),
    '#description' => t('Position the sidebars in the standard layout.'),
    '#default_value' => UIkit::getThemeSetting('standard_sidebar_positions', $theme_key),
    '#options' => [
      'holy-grail' => t('Holy grail'),
      'sidebars-left' => t('Both sidebars left'),
      'sidebars-right' => t('Both sidebars right'),
    ],
  ];
  $form['layout']['page_layout']['tablet_layout'] = [
    '#type' => 'details',
    '#title' => t('Tablet Layout'),
    '#description' => t('Change layout settings for tablets and medium screens.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  ];
  $form['layout']['page_layout']['tablet_layout']['tablet_layout_demo'] = [
    '#type' => 'container',
  ];
  $form['layout']['page_layout']['tablet_layout']['tablet_layout_demo']['#attributes']['class'][] = 'uk-admin-demo';
  $form['layout']['page_layout']['tablet_layout']['tablet_layout_demo']['#attributes']['class'][] = 'uk-layout-' . $tablet_sidebar_pos;
  $form['layout']['page_layout']['tablet_layout']['tablet_layout_demo']['tablet_demo'] = [
    '#markup' => '<div id="tablet-layout-demo">' . $demo_layout . '</div>',
  ];
  $form['layout']['page_layout']['tablet_layout']['tablet_sidebar_positions'] = [
    '#type' => 'radios',
    '#title' => t('Sidebar positions'),
    '#description' => t('Position the sidebars in the tablet layout.'),
    '#default_value' => UIkit::getThemeSetting('tablet_sidebar_positions', $theme_key),
    '#options' => [
      'holy-grail' => t('Holy grail'),
      'sidebars-left' => t('Both sidebars left'),
      'sidebar-left-stacked' => t('Left sidebar stacked'),
      'sidebars-right' => t('Both sidebars right'),
      'sidebar-right-stacked' => t('Right sidebar stacked'),
    ],
  ];
  $form['layout']['page_layout']['mobile_layout'] = [
    '#type' => 'details',
    '#title' => t('Mobile Layout'),
    '#description' => t('Change layout settings for mobile devices and small screens.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  ];
  $form['layout']['page_layout']['mobile_layout']['mobile_layout_demo'] = [
    '#type' => 'container',
  ];
  $form['layout']['page_layout']['mobile_layout']['mobile_layout_demo']['#attributes']['class'][] = 'uk-admin-demo';
  $form['layout']['page_layout']['mobile_layout']['mobile_layout_demo']['#attributes']['class'][] = 'uk-layout-' . $mobile_sidebar_pos;
  $form['layout']['page_layout']['mobile_layout']['mobile_layout_demo']['mobile_demo'] = [
    '#markup' => '<div id="mobile-layout-demo">' . $demo_layout . '</div>',
  ];
  $form['layout']['page_layout']['mobile_layout']['mobile_sidebar_positions'] = [
    '#type' => 'radios',
    '#title' => t('Sidebar positions'),
    '#description' => t('Position the sidebars in the mobile layout.'),
    '#default_value' => UIkit::getThemeSetting('mobile_sidebar_positions', $theme_key),
    '#options' => [
      'sidebars-stacked' => t('Sidebars stacked'),
      'sidebars-vertical' => t('Sidebars vertical'),
    ],
  ];
  $form['layout']['page_layout']['page_container'] = [
    '#type' => 'checkbox',
    '#title' => t('Page Container'),
    '#description' => t('Add the .uk-container class to the page container to give it a max-width and wrap the main content of your website. For large screens it applies a different max-width.'),
    '#default_value' => UIkit::getThemeSetting('page_container', $theme_key),
    '#states' => [
      'visible' => [
        ':input[name="layout_advanced"]' => ['checked' => TRUE],
      ],
    ],
  ];
  $form['layout']['page_layout']['page_margin'] = [
    '#type' => 'select',
    '#title' => t('Page margin'),
    '#description' => t('Select the margin to add to the top and bottom of the page container. This is useful, for example, when using the gradient style with a centered page container and a navbar.'),
    '#default_value' => UIkit::getThemeSetting('page_margin', $theme_key),
    '#options' => [
      0 => t('No margin'),
      'uk-margin-top' => t('Top margin'),
      'uk-margin-bottom' => t('Bottom margin'),
      'uk-margin' => t('Top and bottom margin'),
    ],
    '#states' => [
      'visible' => [
        ':input[name="layout_advanced"]' => ['checked' => TRUE],
      ],
    ],
  ];
  $form['layout']['region_layout'] = [
    '#type' => 'details',
    '#title' => t('Region Layout'),
    '#description' => t('Change region layout settings.<br><br>Use the following links to see an example of each component style.<ul class="links"><li><a href="http://getuikit.com/docs/panel.html" target="_blank">Panel</a></li><li><a href="http://getuikit.com/docs/block.html" target="_blank">Block</a></li></ul>'),
    '#states' => [
      'visible' => [
        ':input[name="layout_advanced"]' => ['checked' => TRUE],
      ],
    ],
  ];

  // Load all regions to assign separate settings for each region.
  foreach ($all_regions as $region_key => $region) {
    if ($region_key != 'navbar' && $region_key != 'offcanvas') {
      $form['layout']['region_layout'][$region_key] = [
        '#type' => 'details',
        '#title' => t('@region region', ['@region' => $region]),
        '#description' => t('Change the @region region settings.', ['@region' => $region]),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      ];
      $form['layout']['region_layout'][$region_key][$region_key . '_style'] = [
        '#type' => 'select',
        '#title' => t('@title style', ['@title' => $region]),
        '#description' => t('Set the style for the @region region. The theme will automatically style the region accordingly.', ['@region' => $region]),
        '#default_value' => UIkit::getThemeSetting($region_key . '_style', $theme_key),
        '#options' => $region_style_options,
      ];
    }
  }

  // Navigational settings.
  $form['navigations'] = [
    '#type' => 'details',
    '#title' => t('Navigations'),
    '#description' => t('UIkit offers different types of navigations, like navigation bars and side navigations. Use breadcrumbs or a pagination to steer through articles.'),
    '#group' => 'uikit',
  ];
  $form['navigations']['local_tasks'] = [
    '#type' => 'details',
    '#title' => t('Local tasks'),
    '#description' => t('Configure settings for the local tasks menus.'),
    '#attributes' => [
      'open' => 'open',
    ],
  ];
  $form['navigations']['local_tasks']['primary_tasks'] = [
    '#type' => 'container',
  ];
  $form['navigations']['local_tasks']['primary_tasks']['primary_tasks_demo'] = [
    '#markup' => '<div id="primary-tasks-demo" class="uk-admin-demo">' . $demo_local_tasks . '</div>',
  ];
  $form['navigations']['local_tasks']['primary_tasks']['primary_tasks_style'] = [
    '#type' => 'select',
    '#title' => t('Primary tasks style'),
    '#description' => t('Select the style to apply to the primary local tasks.'),
    '#default_value' => UIkit::getThemeSetting('primary_tasks_style', $theme_key),
    '#options' => $primary_subnav_options,
  ];
  $form['navigations']['local_tasks']['secondary_tasks'] = [
    '#type' => 'container',
  ];
  $form['navigations']['local_tasks']['secondary_tasks']['secondary_tasks_demo'] = [
    '#markup' => '<div id="secondary-tasks-demo" class="uk-admin-demo">' . $demo_local_tasks . '</div>',
  ];
  $form['navigations']['local_tasks']['secondary_tasks']['secondary_tasks_style'] = [
    '#type' => 'select',
    '#title' => t('Secondary tasks style'),
    '#description' => t('Select the style to apply to the secondary local tasks.'),
    '#default_value' => UIkit::getThemeSetting('secondary_tasks_style', $theme_key),
    '#options' => $secondary_subnav_options,
  ];
  $form['navigations']['breadcrumb'] = [
    '#type' => 'details',
    '#title' => t('Breadcrumbs'),
    '#description' => t('Configure settings for breadcrumb navigation.'),
    '#attributes' => [
      'open' => 'open',
    ],
  ];
  $form['navigations']['breadcrumb']['display_breadcrumbs'] = [
    '#type' => 'checkbox',
    '#title' => t('Display breadcrumbs'),
    '#description' => t('Check this box to display the breadcrumb.'),
    '#default_value' => UIkit::getThemeSetting('display_breadcrumbs', $theme_key),
  ];
  $form['navigations']['breadcrumb']['breakcrumbs_home_link'] = [
    '#type' => 'checkbox',
    '#title' => t('Display home link in breadcrumbs'),
    '#description' => t('Check this box to display the home link in breadcrumb trail.'),
    '#default_value' => UIkit::getThemeSetting('breakcrumbs_home_link', $theme_key),
    '#states' => [
      'disabled' => [
        ':input[name="display_breadcrumbs"]' => ['checked' => FALSE],
      ],
    ],
  ];
  $form['navigations']['breadcrumb']['breakcrumbs_current_page'] = [
    '#type' => 'checkbox',
    '#title' => t('Display current page title in breadcrumbs'),
    '#description' => t('Check this box to display the current page title in breadcrumb trail.'),
    '#default_value' => UIkit::getThemeSetting('breakcrumbs_current_page', $theme_key),
    '#states' => [
      'disabled' => [
        ':input[name="display_breadcrumbs"]' => ['checked' => FALSE],
      ],
    ],
  ];

  // UIkit theme information.
  $form['uikit_details'] = [
    '#type' => 'details',
    '#title' => t('About UIkit'),
    '#group' => 'uikit',
  ];
  $form['uikit_details']['info'] = [
    '#markup' => $uikit_info,
  ];

  // Get logo from theme settings to show a preview.
  $logo = UIkit::getThemeSetting('logo');
  $render_logo = [
    '#theme' => 'image',
    '#uri' => $logo['url'],
    '#prefix' => '<div id="logo-preview">',
    '#suffix' => '</div>',
  ];
  $form['logo']['logo_preview'] = [
    '#type' => 'item',
    '#title' => t('Logo preview'),
    '#markup' => render($render_logo),
    '#description' => t('Preview of image to display as the site logo. The preview will be updated when the configuration is saved.'),
  ];

  // Get favicon from theme settings to show a preview.
  $favicon = UIkit::getThemeSetting('favicon');
  $render_favicon = [
    '#theme' => 'image',
    '#uri' => $favicon['url'],
    '#prefix' => '<div id="favicon-preview">',
    '#suffix' => '</div>',
  ];
  $form['favicon']['favicon_preview'] = [
    '#type' => 'item',
    '#title' => t('Favicon preview'),
    '#markup' => render($render_favicon),
    '#description' => t('Preview of favicon displayed in the address bar and bookmarks of most browsers. The preview will be updated when the configuration is saved.'),
  ];

  // Close the logo and favicon details elements by default.
  $form['logo']['#open'] = FALSE;
  $form['favicon']['#open'] = FALSE;
}
