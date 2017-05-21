<?php

/**
 * @file
 * Provides theme settings for UIkit themes.
 */

include_once 'src/UIkit.php';

use \Drupal\uikit\UIkit;

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function uikit_form_system_theme_settings_alter(&$form, &$form_state, $form_id = NULL) {
  global $theme_key;

  // General "alters" use a form id. Settings should not be set here. The only
  // thing useful about this is if you need to alter the form for the running
  // theme and *not* the theme setting.
  // @see http://drupal.org/node/943212
  if (isset($form_id)) {
    return;
  }

  // Get the active theme name.
  $theme_key = $form_state['build_info']['args'][0] === $theme_key ? $form_state['build_info']['args'][0] : $theme_key;

  // Include theme-settings.php when the form is being rebuilt during file
  // Customizer CSS uploads.
  $form_state['build_info']['files']['uikit'] = drupal_get_path('theme', 'uikit') . '/theme-settings.php';

  // Get Customizer CSS theme setting for later use.
  $customizer_css = UIkit::getThemeSetting('customizer_css', $theme_key);

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

  // Set the charset options.
  $charsets = array(
    'utf-8' => 'UTF-8: All languages (Recommended)',
    'ISO-8859-1' => 'ISO 8859-1: Latin 1',
    'ISO-8859-2' => 'ISO 8859-2: Central & East European',
    'ISO-8859-3' => 'ISO 8859-3: South European, Maltese & Esperanto',
    'ISO-8859-4' => 'ISO 8859-4: North European',
    'ISO-8859-5' => 'ISO 8859-5: Cyrillic',
    'ISO-8859-6' => 'ISO 8859-6: Arabic',
    'ISO-8859-7' => 'ISO 8859-7: Modern Greek',
    'ISO-8859-8' => 'ISO 8859-8: Hebrew & Yiddish',
    'ISO-8859-9' => 'ISO 8859-9: Turkish',
    'ISO-8859-10' => 'ISO 8859-10: Nordic (Lappish, Inuit, Icelandic)',
    'ISO-8859-11' => 'ISO 8859-11: Thai',
    'ISO-8859-13' => 'ISO 8859-13: Baltic Rim',
    'ISO-8859-14' => 'ISO 8859-14: Celtic',
    'ISO-8859-16' => 'ISO 8859-16: South-Eastern Europe',
  );

  // Set the x-ua-compatible options.
  $x_ua_compatible_ie_options = array(
    0 => 'None (Recommended)',
    'edge' => 'Highest supported document mode',
    '5' => 'Quirks Mode',
    '7' => 'IE7 mode',
    '8' => 'IE8 mode',
    '9' => 'IE9 mode',
    '10' => 'IE10 mode',
    '11' => 'IE11 mode',
  );

  // Set the navbar margin options.
  $navbar_margin_top_options = array(
    'No top margin',
    'Normal top margin',
    'Smaller top margin',
    'Larger top margin',
  );
  $navbar_margin_bottom_options = array(
    'No bottom margin',
    'Normal bottom margin',
    'Smaller bottom margin',
    'Larger bottom margin',
  );

  // Build the markup for the local task demos.
  $demo_local_tasks = '<ul>';
  $demo_local_tasks .= '<li class="uk-active"><a href="#">Item</a></li>';
  $demo_local_tasks .= '<li><a href="#">Item</a></li>';
  $demo_local_tasks .= '<li><a href="#">Item</a></li>';
  $demo_local_tasks .= '<li class="uk-disabled"><a href="#">Disabled</a></li>';
  $demo_local_tasks .= '</ul>';

  // Set the subnav options for primary and secondary tasks.
  $primary_subnav_options = array(
    0 => 'Basic subnav',
    'uk-subnav-line' => 'Subnav line',
    'uk-subnav-pill' => 'Subnav pill',
    'uk-tab' => 'Tabbed',
  );
  $secondary_subnav_options = array(
    0 => 'Basic subnav',
    'uk-subnav-line' => 'Subnav line',
    'uk-subnav-pill' => 'Subnav pill',
  );

  // Set the region style options.
  $region_style_options = array(
    0 => 'No style',
    'panel' => 'Panel',
    'block' => 'Block',
  );

  // Set the viewport scale options.
  $viewport_scale = array(
    -1 => t('-- Select --'),
    '0' => '0',
    '1' => '1',
    '2' => '2',
    '3' => '3',
    '4' => '4',
    '5' => '5',
    '6' => '6',
    '7' => '7',
    '8' => '8',
    '9' => '9',
    '10' => '10',
  );

  // Fetch a list of regions for the current theme.
  $all_regions = system_region_list($theme_key);

  // Create markup for UIkit theme information.
  $uikit_theme_info = drupal_parse_info_file(drupal_get_path('theme', 'uikit') . '/uikit.info');
  $uikit_version = isset($uikit_theme_info['version']) ? $uikit_theme_info['version'] : UIkit::UIKIT_PROJECT_BRANCH;
  $uikit_info = '<div class="uk-container uk-container-center uk-margin-top">';
  $uikit_info .= '<div class="uk-grid">';
  $uikit_info .= '<div class="uk-width-1-1">';
  $uikit_info .= '<div class="uk-text-center"><img src="/' . drupal_get_path('theme', 'uikit') . '/images/uikit-small.png" /></div>';
  $uikit_info .= '<blockquote class="uk-text-small">';
  $uikit_info .= '<p><i class="uk-icon-quote-left uk-icon-large uk-align-left"></i> ' . $uikit_theme_info['description'] . '</p>';
  $uikit_info .= '</blockquote>';
  $uikit_info .= '</div>';
  $uikit_info .= '<div class="uk-width-1-1 uk-margin">';
  $uikit_info .= '<div class="uk-grid">';
  $uikit_info .= '<ul class="uk-list uk-width-1-1 uk-text-center">';
  $uikit_info .= '<li class="uk-width-small-1-1 uk-width-medium-1-3 uk-float-left"><a href="' . UIkit::UIKIT_LIBRARY . '" target="_blank">UIkit homepage</a></li>';
  $uikit_info .= '<li class="uk-width-small-1-1 uk-width-medium-1-3 uk-float-left"><a href="' . UIkit::UIKIT_PROJECT . '" target="_blank">Drupal.org project page</a></li>';
  $uikit_info .= '<li class="uk-width-small-1-1 uk-width-medium-1-3 uk-float-left"><a href="' . UIkit::UIKIT_PROJECT_API . '" target="_blank">UIkit API site</a></li>';
  $uikit_info .= '<li class="uk-width-small-1-1 uk-width-medium-1-3 uk-float-left"><strong>UIkit library version</strong>: v' . UIkit::UIKIT_LIBRARY_VERSION . '</li>';
  $uikit_info .= '<li class="uk-width-small-1-1 uk-width-medium-1-3 uk-float-left"><strong>UIkit Drupal version</strong>: ' . $uikit_version . '</li>';
  $uikit_info .= '<li class="uk-width-small-1-1 uk-width-medium-1-3 uk-float-left"><strong>Ported to Drupal by</strong>: <a href="http://richardbuchanan.com" target="_blank">Richard Buchanan</a></li>';
  $uikit_info .= '<li class="uk-width-small-1-1 uk-float-left uk-margin-top">UIkit <i class="uk-icon-copyright"></i> <a href="http://www.yootheme.com/" target="_blank">YOOtheme</a>, with love and caffeine, under the <a href="http://opensource.org/licenses/MIT" target="_blank">MIT license</a>.</li>';
  $uikit_info .= '<li class="uk-width-small-1-1 uk-float-left">UIkit for Drupal <i class="uk-icon-copyright"></i> <a href="http://richardbuchanan.com" target="_blank">Richard Buchanan</a></li>';
  $uikit_info .= '</ul>';
  $uikit_info .= '</div></div></div></div>';

  // Create vertical tabs for all UIkit related settings.
  $form['uikit'] = array(
    '#type' => 'vertical_tabs',
    '#attached' => array(
      'css' => array(
        drupal_get_path('theme', 'uikit') . '/css/uikit.admin.css' => array(
          'group' => CSS_DEFAULT,
        ),
      ),
      'js' => array(
        drupal_get_path('theme', 'uikit') . '/js/uikit.admin.js' => array(
          'group' => JS_DEFAULT,
        ),
      ),
    ),
    '#prefix' => '<h3>' . t('UIkit Settings') . '</h3>',
    '#weight' => -10,
  );

  // UIkit theme styles.
  $form['theme'] = array(
    '#type' => 'fieldset',
    '#title' => t('Theme styles'),
    '#description' => t('UIkit comes with a basic theme and two neat themes to get you started. Here you can select which base style to start with.'),
    '#group' => 'uikit',
    '#attributes' => array(
      'class' => array(
        'uikit-theme-settings-form',
      ),
    ),
  );
  $form['theme']['base_style'] = array(
    '#type' => 'select',
    '#title' => t('Base style'),
    '#options' => array(
      0 => t('UIkit default'),
      'almost-flat' => t('UIkit almost flat'),
      'gradient' => t('UIkit gradient'),
      'customizer-css' => t('Customizer CSS'),
    ),
    '#description' => t('Select which base style to use.<ol><li><strong>UIkit default:</strong> No border radius or gradients</li><li><strong>UIkit almost flat:</strong> Small border and border radius</li><li><strong>UIkit gradient:</strong> Almost flat style with gradient backgrounds.</li><li><strong>Customizer CSS:</strong> Use stylesheet uploaded from <a href="@customizer" target="_blank">Customizer</a>.</li></ol>', array('@customizer' => 'https://getuikit.com/v2/docs/customizer.html')),
    '#default_value' => UIkit::getThemeSetting('base_style', $theme_key),
  );
  $form['theme']['theme_customizer'] = array(
    '#type' => 'fieldset',
    '#title' => t('UIkit Customizer'),
    '#description' => t('UIkit comes with a customizer that enables you to make adjustments to the theme you are using with just a few clicks and no need for any CSS knowledge. You can then download your new CSS and upload it here to override the default styles provided by UIkit. Visit <a href="@customizer" target="_blank">How to customize</a> to learn how to use Customizer.', array('@customizer' => 'https://getuikit.com/v2/docs/documentation_how-to-customize.html')),
    '#states' => array(
      'visible' => array(
        ':input[name="base_style"]' => array('value' => 'customizer-css'),
      ),
    ),
  );
  $form['theme']['theme_customizer']['customizer_css'] = array(
    '#title' => t('Customizer CSS'),
    '#type' => 'managed_file',
    '#description' => t('Upload the CSS file you downloaded from Customizer. This stylesheet will be added to all pages that use your theme.'),
    '#default_value' => isset($customizer_css['fid']) ? $customizer_css['fid'] : 0,
    '#element_validate' => array('_uikit_customizer_css_file_validate'),
    '#upload_location' => 'public://customizer_css/',
    "#upload_validators"  => array('file_validate_extensions' => array('css')),
  );

  // Mobile settings.
  $form['mobile_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mobile settings'),
    '#description' => t("Adjust the mobile layout settings to enhance your users' experience on smaller devices."),
    '#group' => 'uikit',
    '#attributes' => array(
      'class' => array(
        'uikit-mobile-settings-form',
      ),
    ),
  );
  $form['mobile_settings']['mobile_advanced'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show advanced mobile settings'),
    '#description' => t('Advanced mobile settings give you fine-grain control over additional metadata settings.'),
    '#default_value' => UIkit::getThemeSetting('mobile_advanced', $theme_key),
  );
  $form['mobile_settings']['mobile_metadata'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mobile metadata'),
    '#description' => t('HTML5 has attributes that can be defined in meta elements. Here you can control some of these attributes.'),
  );
  $form['mobile_settings']['mobile_metadata']['meta_charset'] = array(
    '#type' => 'select',
    '#title' => t('<code>charset</code>'),
    '#options' => $charsets,
    '#description' => t('Specify the character encoding for the HTML document.'),
    '#default_option' => UIkit::getThemeSetting('meta_charset', $theme_key),
  );
  $form['mobile_settings']['mobile_metadata']['x_ua_compatible'] = array(
    '#type' => 'select',
    '#title' => t('<code>x_ua_compatible</code> IE Mode'),
    '#options' => $x_ua_compatible_ie_options,
    '#default_value' => UIkit::getThemeSetting('x_ua_compatible', $theme_key),
    '#description' => t('In some cases, it might be necessary to restrict a webpage to a document mode supported by an older version of Windows Internet Explorer. Here we look at the x-ua-compatible header, which allows a webpage to be displayed as if it were viewed by an earlier version of the browser. @see !legacy', array(
      '!legacy' => '<a href="https://msdn.microsoft.com/en-us/library/jj676915(v=vs.85).aspx" target="_blank">' . t('Specifying legacy document modes') . '</a>',
    )),
    '#states' => array(
      'visible' => array(
        ':input[name="mobile_advanced"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['mobile_settings']['mobile_metadata']['meta_viewport'] = array(
    '#type' => 'fieldset',
    '#title' => t('Viewport metadata'),
    '#description' => t('Gives hints about the size of the initial size of the viewport. This pragma is used by several mobile devices only.'),
    '#states' => array(
      'visible' => array(
        ':input[name="mobile_advanced"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['mobile_settings']['mobile_metadata']['meta_viewport']['device_width'] = array(
    '#type' => 'fieldset',
    '#title' => t('Width'),
    '#collapsible' => TRUE,
  );
  $form['mobile_settings']['mobile_metadata']['meta_viewport']['device_width']['viewport_device_width_ratio'] = array(
    '#type' => 'select',
    '#title' => t('Device width ratio'),
    '#description' => t('Defines the ratio between the device width (device-width in portrait mode or device-height in landscape mode) and the viewport size. Literal device width is defined as <code>device-width</code> and is the recommended value. You can also specify a pixel width by selecting <b>Other</b>, such as <code>300</code>.'),
    '#default_value' => UIkit::getThemeSetting('viewport_device_width_ratio', $theme_key),
    '#options' => array(
      0 => t('-- Select --'),
      'device-width' => t('Literal device width (Recommended)'),
      '1' => t('Other'),
    ),
  );
  $form['mobile_settings']['mobile_metadata']['meta_viewport']['device_width']['viewport_custom_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom device width'),
    '#description' => t('Defines the width, in pixels, of the viewport. Do not add <b>px</b>, the value must be a non-decimal integer number.'),
    '#default_value' => UIkit::getThemeSetting('viewport_custom_width', $theme_key),
    '#attributes' => array(
      'size' => 15,
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="viewport_device_width_ratio"]' => array('value' => '1'),
      ),
      'required' => array(
        ':input[name="viewport_device_width_ratio"]' => array('value' => '1'),
      ),
    ),
    '#element_validate' => array('_uikit_viewport_custom_width_validate'),
  );
  $form['mobile_settings']['mobile_metadata']['meta_viewport']['device_height'] = array(
    '#type' => 'fieldset',
    '#title' => t('Height'),
    '#collapsible' => TRUE,
  );
  $form['mobile_settings']['mobile_metadata']['meta_viewport']['device_height']['viewport_device_height_ratio'] = array(
    '#type' => 'select',
    '#title' => t('Device height ratio'),
    '#description' => t('Defines the ratio between the device height (device-height in portrait mode or device-width in landscape mode) and the viewport size. Literal device height is defined as <code>device-height</code> and is the recommended value. You can also specify a pixel height by selecting <b>Other</b>, such as <code>300</code>.'),
    '#default_value' => UIkit::getThemeSetting('viewport_device_height_ratio', $theme_key),
    '#options' => array(
      0 => t('-- Select --'),
      'device-height' => t('Literal device height (Recommended)'),
      '1' => t('Other'),
    ),
  );
  $form['mobile_settings']['mobile_metadata']['meta_viewport']['device_height']['viewport_custom_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom device height'),
    '#description' => t('Defines the height, in pixels, of the viewport. Do not add <b>px</b>, the value must be a non-decimal integer number.'),
    '#default_value' => UIkit::getThemeSetting('viewport_custom_height', $theme_key),
    '#attributes' => array(
      'size' => 15,
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="viewport_device_height_ratio"]' => array('value' => '1'),
      ),
      'required' => array(
        ':input[name="viewport_device_height_ratio"]' => array('value' => '1'),
      ),
    ),
    '#element_validate' => array('_uikit_viewport_custom_height_validate'),
  );
  $form['mobile_settings']['mobile_metadata']['meta_viewport']['viewport_initial_scale'] = array(
    '#type' => 'select',
    '#title' => t('initial-scale'),
    '#description' => t('Defines the ratio between the device width (device-width in portrait mode or device-height in landscape mode) and the viewport size.'),
    '#default_value' => UIkit::getThemeSetting('viewport_initial_scale', $theme_key),
    '#options' => $viewport_scale,
  );
  $form['mobile_settings']['mobile_metadata']['meta_viewport']['viewport_maximum_scale'] = array(
    '#type' => 'select',
    '#title' => t('maximum-scale'),
    '#description' => t('Defines the maximum value of the zoom; it must be greater or equal to the minimum-scale or the behavior is indeterminate.'),
    '#default_value' => UIkit::getThemeSetting('viewport_maximum_scale', $theme_key),
    '#options' => $viewport_scale,
  );
  $form['mobile_settings']['mobile_metadata']['meta_viewport']['viewport_minimum_scale'] = array(
    '#type' => 'select',
    '#title' => t('minimum-scale'),
    '#description' => t('Defines the minimum value of the zoom; it must be smaller or equal to the maximum-scale or the behavior is indeterminate.'),
    '#default_value' => UIkit::getThemeSetting('viewport_minimum_scale', $theme_key),
    '#options' => $viewport_scale,
  );
  $form['mobile_settings']['mobile_metadata']['meta_viewport']['viewport_user_scalable'] = array(
    '#type' => 'select',
    '#title' => t('user-scalable'),
    '#description' => t('If set to no, the user is not able to zoom in the webpage. Default value is <b>Yes</b>.'),
    '#default_value' => UIkit::getThemeSetting('viewport_user_scalable', $theme_key),
    '#options' => array(
      1 => t('Yes'),
      0 => t('No'),
    ),
  );

  // Layout settings.
  $form['layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layout'),
    '#description' => t('Apply our fully responsive fluid grid system and panels, common layout parts like blog articles and comments and useful utility classes.'),
    '#group' => 'uikit',
    '#attributes' => array(
      'class' => array(
        'uikit-layout-settings-form',
      ),
    ),
  );
  $form['layout']['layout_advanced'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show advanced layout settings'),
    '#default_value' => UIkit::getThemeSetting('layout_advanced', $theme_key),
  );
  $form['layout']['page_layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Page Layout'),
    '#description' => t('Change page layout settings.'),
  );
  $form['layout']['page_layout']['standard_layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Standard Layout'),
    '#description' => t('Change layout settings for desktops and large screens.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['layout']['page_layout']['standard_layout']['standard_layout_demo'] = array(
    '#type' => 'container',
  );
  $form['layout']['page_layout']['standard_layout']['standard_layout_demo']['#attributes']['class'][] = 'uk-admin-demo';
  $form['layout']['page_layout']['standard_layout']['standard_layout_demo']['#attributes']['class'][] = 'uk-layout-' . $standard_sidebar_pos;
  $form['layout']['page_layout']['standard_layout']['standard_layout_demo']['standard_demo'] = array(
    '#markup' => '<div id="standard-layout-demo">' . $demo_layout . '</div>',
  );
  $form['layout']['page_layout']['standard_layout']['standard_sidebar_positions'] = array(
    '#type' => 'radios',
    '#title' => t('Sidebar positions'),
    '#description' => t('Position the sidebars in the standard layout.'),
    '#default_value' => UIkit::getThemeSetting('standard_sidebar_positions', $theme_key),
    '#options' => array(
      'holy-grail' => t('Holy grail'),
      'sidebars-left' => t('Both sidebars left'),
      'sidebars-right' => t('Both sidebars right'),
    ),
  );
  $form['layout']['page_layout']['tablet_layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tablet Layout'),
    '#description' => t('Change layout settings for tablets and medium screens.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['layout']['page_layout']['tablet_layout']['tablet_layout_demo'] = array(
    '#type' => 'container',
  );
  $form['layout']['page_layout']['tablet_layout']['tablet_layout_demo']['#attributes']['class'][] = 'uk-admin-demo';
  $form['layout']['page_layout']['tablet_layout']['tablet_layout_demo']['#attributes']['class'][] = 'uk-layout-' . $tablet_sidebar_pos;
  $form['layout']['page_layout']['tablet_layout']['tablet_layout_demo']['tablet_demo'] = array(
    '#markup' => '<div id="tablet-layout-demo">' . $demo_layout . '</div>',
  );
  $form['layout']['page_layout']['tablet_layout']['tablet_sidebar_positions'] = array(
    '#type' => 'radios',
    '#title' => t('Sidebar positions'),
    '#description' => t('Position the sidebars in the tablet layout.'),
    '#default_value' => UIkit::getThemeSetting('tablet_sidebar_positions', $theme_key),
    '#options' => array(
      'holy-grail' => t('Holy grail'),
      'sidebars-left' => t('Both sidebars left'),
      'sidebar-left-stacked' => t('Left sidebar stacked'),
      'sidebars-right' => t('Both sidebars right'),
      'sidebar-right-stacked' => t('Right sidebar stacked'),
    ),
  );
  $form['layout']['page_layout']['mobile_layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mobile Layout'),
    '#description' => t('Change layout settings for mobile devices and small screens.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['layout']['page_layout']['mobile_layout']['mobile_layout_demo'] = array(
    '#type' => 'container',
  );
  $form['layout']['page_layout']['mobile_layout']['mobile_layout_demo']['#attributes']['class'][] = 'uk-admin-demo';
  $form['layout']['page_layout']['mobile_layout']['mobile_layout_demo']['#attributes']['class'][] = 'uk-layout-' . $mobile_sidebar_pos;
  $form['layout']['page_layout']['mobile_layout']['mobile_layout_demo']['mobile_demo'] = array(
    '#markup' => '<div id="mobile-layout-demo">' . $demo_layout . '</div>',
  );
  $form['layout']['page_layout']['mobile_layout']['mobile_sidebar_positions'] = array(
    '#type' => 'radios',
    '#title' => t('Sidebar positions'),
    '#description' => t('Position the sidebars in the mobile layout.'),
    '#default_value' => UIkit::getThemeSetting('mobile_sidebar_positions', $theme_key),
    '#options' => array(
      'sidebars-stacked' => t('Sidebars stacked'),
      'sidebars-vertical' => t('Sidebars vertical'),
    ),
  );
  $form['layout']['page_layout']['page_container'] = array(
    '#type' => 'checkbox',
    '#title' => t('Page Container'),
    '#description' => t('Add the .uk-container class to the page container to give it a max-width and wrap the main content of your website. For large screens it applies a different max-width.'),
    '#default_value' => UIkit::getThemeSetting('page_container', $theme_key),
    '#states' => array(
      'visible' => array(
        ':input[name="layout_advanced"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['layout']['page_layout']['page_centering'] = array(
    '#type' => 'checkbox',
    '#title' => t('Page Centering'),
    '#description' => t('To center the page container, use the .uk-container-center class.'),
    '#default_value' => UIkit::getThemeSetting('page_centering', $theme_key),
    '#states' => array(
      'visible' => array(
        ':input[name="layout_advanced"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['layout']['page_layout']['page_margin'] = array(
    '#type' => 'select',
    '#title' => t('Page margin'),
    '#description' => t('Select the margin to add to the top and bottom of the page container. This is useful, for example, when using the gradient style with a centered page container and a navbar.'),
    '#default_value' => UIkit::getThemeSetting('page_margin', $theme_key),
    '#options' => array(
      0 => t('No margin'),
      'uk-margin-top' => t('Top margin'),
      'uk-margin-bottom' => t('Bottom margin'),
      'uk-margin' => t('Top and bottom margin'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="layout_advanced"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['layout']['region_layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Region Layout'),
    '#description' => t('Change region layout settings.<br><br>Use the following links to see an example of each component style.<ul class="links"><li><a href="http://getuikit.com/docs/panel.html" target="_blank">Panel</a></li><li><a href="http://getuikit.com/docs/block.html" target="_blank">Block</a></li></ul>'),
    '#states' => array(
      'visible' => array(
        ':input[name="layout_advanced"]' => array('checked' => TRUE),
      ),
    ),
  );

  // Load all regions to assign separate settings for each region.
  foreach ($all_regions as $region_key => $region) {
    $form['layout']['region_layout'][$region_key] = array(
      '#type' => 'fieldset',
      '#title' => t('@region region', array('@region' => $region)),
      '#description' => t('Change the @region region settings.', array('@region' => $region)),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['layout']['region_layout'][$region_key][$region_key . '_style'] = array(
      '#type' => 'select',
      '#title' => t('@title style', array('@title' => $region)),
      '#description' => t('Set the style for the @region region. The theme will automatically style the region accordingly.', array('@region' => $region)),
      '#default_value' => UIkit::getThemeSetting($region_key . '_style', $theme_key),
      '#options' => $region_style_options,
    );
  }

  // Navigational settings.
  $form['navigations'] = array(
    '#type' => 'fieldset',
    '#title' => t('Navigations'),
    '#description' => t('UIkit offers different types of navigations, like navigation bars and side navigations. Use breadcrumbs or a pagination to steer through articles.'),
    '#group' => 'uikit',
  );
  $form['navigations']['main_navbar'] = array(
    '#type' => 'fieldset',
    '#title' => t('Navigation bar'),
    '#description' => t('Configure settings for the navigation bar.'),
  );
  $form['navigations']['main_navbar']['navbar_container_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Navbar container'),
    '#description' => t('Configure settings for the navigation bar container.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['navigations']['main_navbar']['navbar_container_settings']['navbar_container'] = array(
    '#type' => 'checkbox',
    '#title' => t('Container'),
    '#description' => t('Add the .uk-container class to the navbar container to give it a max-width and wrap the navbar of your website. For large screens it applies a different max-width.'),
    '#default_value' => UIkit::getThemeSetting('navbar_container', $theme_key),
  );
  $form['navigations']['main_navbar']['navbar_container_settings']['navbar_centering'] = array(
    '#type' => 'checkbox',
    '#title' => t('Centering'),
    '#description' => t('To center the navbar container, use the .uk-container-center class.'),
    '#default_value' => UIkit::getThemeSetting('navbar_centering', $theme_key),
  );
  $form['navigations']['main_navbar']['navbar_container_settings']['navbar_attached'] = array(
    '#type' => 'checkbox',
    '#title' => t('Navbar attached'),
    '#description' => t("Adds the <code>.uk-navbar-attached</code> class to optimize the navbar's styling to be attached to the top of the viewport. For example, rounded corners will be removed."),
    '#default_value' => UIkit::getThemeSetting('navbar_attached', $theme_key),
  );
  $form['navigations']['main_navbar']['navbar_margin'] = array(
    '#type' => 'fieldset',
    '#title' => t('Navbar margin'),
    '#description' => t('Configure the top and bottom margin to apply to the navbar.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['navigations']['main_navbar']['navbar_margin']['navbar_margin_top'] = array(
    '#type' => 'select',
    '#title' => t('Navbar top margin'),
    '#description' => t('Select the amount of top margin to apply to the navbar.'),
    '#default_value' => UIkit::getThemeSetting('navbar_margin_top', $theme_key),
    '#options' => $navbar_margin_top_options,
  );
  $form['navigations']['main_navbar']['navbar_margin']['navbar_margin_bottom'] = array(
    '#type' => 'select',
    '#title' => t('Navbar bottom margin'),
    '#description' => t('Select the amount of bottom margin to apply to the navbar.'),
    '#default_value' => UIkit::getThemeSetting('navbar_margin_bottom', $theme_key),
    '#options' => $navbar_margin_bottom_options,
  );
  $form['navigations']['local_tasks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Local tasks'),
    '#description' => t('Configure settings for the local tasks menus.'),
  );
  $form['navigations']['local_tasks']['primary_tasks'] = array(
    '#type' => 'container',
  );
  $form['navigations']['local_tasks']['primary_tasks']['primary_tasks_demo'] = array(
    '#markup' => '<div id="primary-tasks-demo" class="uk-admin-demo">' . $demo_local_tasks . '</div>',
  );
  $form['navigations']['local_tasks']['primary_tasks']['primary_tasks_style'] = array(
    '#type' => 'select',
    '#title' => t('Primary tasks style'),
    '#description' => t('Select the style to apply to the primary local tasks.'),
    '#default_value' => UIkit::getThemeSetting('primary_tasks_style', $theme_key),
    '#options' => $primary_subnav_options,
  );
  $form['navigations']['local_tasks']['secondary_tasks'] = array(
    '#type' => 'container',
  );
  $form['navigations']['local_tasks']['secondary_tasks']['secondary_tasks_demo'] = array(
    '#markup' => '<div id="secondary-tasks-demo" class="uk-admin-demo">' . $demo_local_tasks . '</div>',
  );
  $form['navigations']['local_tasks']['secondary_tasks']['secondary_tasks_style'] = array(
    '#type' => 'select',
    '#title' => t('Secondary tasks style'),
    '#description' => t('Select the style to apply to the secondary local tasks.'),
    '#default_value' => UIkit::getThemeSetting('secondary_tasks_style', $theme_key),
    '#options' => $secondary_subnav_options,
  );
  $form['navigations']['breadcrumb'] = array(
    '#type' => 'fieldset',
    '#title' => t('Breadcrumbs'),
    '#description' => t('Configure settings for breadcrumb navigation.'),
  );
  $form['navigations']['breadcrumb']['display_breadcrumbs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display breadcrumbs'),
    '#description' => t('Check this box to display the breadcrumb.'),
    '#default_value' => UIkit::getThemeSetting('display_breadcrumbs', $theme_key),
  );
  $form['navigations']['breadcrumb']['breakcrumbs_home_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display home link in breadcrumbs'),
    '#description' => t('Check this box to display the home link in breadcrumb trail.'),
    '#default_value' => UIkit::getThemeSetting('breakcrumbs_home_link', $theme_key),
  );
  $form['navigations']['breadcrumb']['breakcrumbs_current_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display current page title in breadcrumbs'),
    '#description' => t('Check this box to display the current page title in breadcrumb trail.'),
    '#default_value' => UIkit::getThemeSetting('breakcrumbs_current_page', $theme_key),
    '#states' => array(
      'disabled' => array(
        ':input[name="display_breadcrumbs"]' => array('checked' => FALSE),
      ),
    ),
  );

  // UIkit theme information.
  $form['uikit_details'] = array(
    '#type' => 'fieldset',
    '#title' => t('About UIkit'),
    '#group' => 'uikit',
  );
  $form['uikit_details']['info'] = array(
    '#markup' => $uikit_info,
  );

  // Create vertical tabs to place Drupal's default theme settings in.
  $form['basic_settings'] = array(
    '#type' => 'vertical_tabs',
    '#prefix' => '<h3>' . t('Basic Settings') . '</h3>',
    '#weight' => 0,
  );

  // Group Drupal's default theme settings in the basic settings.
  $form['theme_settings']['#group'] = 'basic_settings';
  $form['logo']['#group'] = 'basic_settings';
  $form['logo']['#attributes']['class'] = array('form-wrapper', 'vertical-tabs-pane');
  $form['favicon']['#group'] = 'basic_settings';

  // Set validation callback to call when saving theme settings.
  $form['#validate'][] = 'uikit_theme_settings_validate';
}

/**
 * Callback function to validate the Customizer CSS field.
 *
 * When using the Customizer option as a base style, this function validates the
 * file being uploaded. This provides the user with useful information and
 * instructions to be sure the file is uploaded and saved as a managed file.
 * This allows the base theme to load the stylesheet as a managed file from the
 * database.
 */
function _uikit_customizer_css_file_validate($element, &$form_state) {
  $theme_key = $form_state['build_info']['args'][0];

  // If referencing an existing file, only allow if there are existing
  // references. This prevents unmanaged files from being deleted if this
  // item were to be deleted.
  $clicked_button = end($form_state['triggering_element']['#parents']);

  if ($clicked_button == 'upload_button') {
    if ($file = !file_load($element['fid']['#value'])) {
      form_error($element, t('The file referenced by the !name field does not exist.', array('!name' => $element['#title'])));
    }
    else {
      $fid = $element['fid']['#value'];
      $file = file_load($fid);

      if (is_object($file)) {

        // Check to make sure that the file is set to be permanent.
        if ($file->status == 0) {
          // Update the status.
          $file->status = FILE_STATUS_PERMANENT;

          // Save the update.
          file_save($file);

          // Add a reference to prevent warnings.
          file_usage_add($file, $theme_key, 'theme', 1);

          // Alert the user to save the form to update the theme settings.
          drupal_set_message(t('@filename successfully uploaded. All changes are stored temporarily. Click Save configuration to make your changes permanent.', array('@filename' => $file->filename)), 'warning');
        }
      }
    }
  }
  elseif ($clicked_button == 'remove_button') {
    // Delete the file and file usage from the database and file system.
    $file = file_load($element['fid']['#value']);
    file_usage_delete($file, $theme_key, 'theme', 1);
    file_delete($file);

    // Alert the user to save the form to update the theme settings.
    drupal_set_message(t('@filename successfully removed. All changes are stored temporarily. Click Save configuration to make your changes permanent.', array('@filename' => $file->filename)), 'warning');
  }
}

/**
 * Callback function to validate the viewport width.
 *
 * The default value for the initial scale is turned off, but it is recommended
 * to use the literal device width. If the user chooses to define a pixel width,
 * the value for the initial scale needs to be validated to ensure only an
 * integer is entered.
 */
function _uikit_viewport_custom_width_validate($element, &$form_state) {
  $device_width_ratio = $form_state['values']['viewport_device_width_ratio'] == 1;

  if ($device_width_ratio && empty($element['#value'])) {
    form_set_error($element['#name'], t('<b>Other</b> was selected for <b>Device width ratio</b>, but no value was given for <b>Custom device width</b>. Please enter an integer value in <b>Custom device width</b> under <b>Mobile settings</b> and save the configuration.'));
  }
  elseif ($device_width_ratio && !empty($element['#value']) && !ctype_digit($element['#value'])) {
    form_set_error($element['#name'], t('<b>Custom device width</b> can only contain an integer number, without a decimal point. Please check the value for <b>Custom device width</b> under <b>Mobile settings</b> and save the configuration.'));
  }
}

/**
 * Callback function to validate the viewport height.
 *
 * The default value for the initial scale is turned off, but it is recommended
 * to use the literal device width. If the user chooses to define a pixel width,
 * the value for the initial scale needs to be validated to ensure only an
 * integer is entered.
 */
function _uikit_viewport_custom_height_validate($element, &$form_state) {
  $device_height_ratio = $form_state['values']['viewport_device_height_ratio'] == 1;

  if ($device_height_ratio && empty($element['#value'])) {
    form_set_error($element['#name'], t('<b>Other</b> was selected for <b>Device height ratio</b>, but no value was given for <b>Custom device height</b>. Please enter an integer value in <b>Custom device height</b> under <b>Mobile settings</b> and save the configuration.'));
  }
  elseif ($device_height_ratio && !empty($element['#value']) && !ctype_digit($element['#value'])) {
    form_set_error($element['#name'], t('<b>Custom device height</b> can only contain an integer number, without a decimal point. Please check the value for <b>Custom device height</b> under <b>Mobile settings</b> and save the configuration.'));
  }
}

/**
 * Callback function to validate the system theme settings form.
 *
 * When the Customizer option is used as a base style, this function validates
 * a stylesheet was in fact uploaded. This ensures the base theme will still
 * load a UIkit-supplied style until the user fixes the error and uploads a
 * stylesheet.
 */
function uikit_theme_settings_validate($form, &$form_state) {
  $base_style = $form_state['values']['base_style'];
  $customizer_css = $form_state['values']['customizer_css']['fid'];

  if ($base_style == 'customizer-css' && !$customizer_css) {
    form_set_error('customizer_css', t('Customizer CSS is selected as your base style but you have not uploaded a stylesheet.'));
  }
}
