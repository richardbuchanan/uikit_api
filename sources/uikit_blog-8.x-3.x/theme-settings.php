<?php

/**
 * @file
 * Provides theme settings for uikit_blog.
 */

use Drupal\Component\Utility\String;
use Drupal\Core\Datetime\Entity\DateFormat;
use Drupal\uikit\UIkit;

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function uikit_blog_form_system_theme_settings_alter(&$form, \Drupal\Core\Form\FormStateInterface $form_state, $form_id = NULL) {
  // General "alters" use a form id. Settings should not be set here. The only
  // thing useful about this is if you need to alter the form for the running
  // theme and *not* the theme setting.
  // @see http://drupal.org/node/943212
  if (isset($form_id)) {
    return;
  }

  // Get settings from core.
  $theme = Drupal::config('system.theme')->get('default');

  // Get all date formats and add to to an array to put into the node date
  // format settings.
  $date_types = DateFormat::loadMultiple();
  $date_formatter = \Drupal::service('date.formatter');
  $date_formats = [];
  foreach ($date_types as $machine_name => $format) {
    $date_formats[$machine_name] = $date_formatter->format(\Drupal::time()->getRequestTime(), $machine_name);
  }
  $date_formats['custom'] = t('Custom');
  $default_date_format = UIKit::getThemeSetting('node_date_format', $theme) ? UIKit::getThemeSetting('node_date_format', $theme) : 'medium';

  // Translatable string arguments.
  $args = [
    '@date' => 'http://php.net/manual/function.date.php',
    '@animation' => 'https://getuikit.com/docs/animation#usage',
    '@icon' => 'https://getuikit.com/docs/icon#library',
    '@tooltip' => 'https://getuikit.com/docs/tooltip',
  ];

  // Create vertical tabs for all UIkit Blog related settings.
  $form['uikit_blog'] = [
    '#type' => 'vertical_tabs',
    '#prefix' => '<h3>' . t('UIkit Blog Settings') . '</h3>',
    '#weight' => -9,
  ];

  // UIkit Blog content settings.
  $form['uikit_blog_content'] = [
    '#type' => 'details',
    '#title' => t('Content'),
    '#group' => 'uikit_blog',
    '#attributes' => [
      'class' => [
        'uikit-blog-content-settings-form',
      ],
    ],
  ];
  $form['uikit_blog_content']['node_date_format'] = [
    '#type' => 'select',
    '#title' => t('Node date format'),
    '#options' => $date_formats,
    '#description' => t('Select the date format to use when displaying nodes. <em class="placeholder">Custom</em> is a user-defined date format. See the <a href="@date" target="_blank">PHP manual</a> for available options.', $args),
    '#default_value' => $default_date_format,
  ];
  $form['uikit_blog_content']['node_date_format__custom'] = [
    '#type' => 'textfield',
    '#title' => t('Custom date format'),
    '#description' => t(''),
    '#default_value' => UIKit::getThemeSetting('node_date_format__custom', $theme),
    '#states' => [
      'visible' => [
        ':input[name="node_date_format"]' => ['value' => 'custom'],
      ],
    ],
  ];

  // UIkit Blog users settings.
  $form['uikit_blog_users'] = [
    '#type' => 'details',
    '#title' => t('Users'),
    '#group' => 'uikit_blog',
    '#attributes' => [
      'class' => [
        'uikit-blog-users-settings-form',
      ],
    ],
  ];
  $form['uikit_blog_users']['default_user_picture'] = [
    '#type' => 'select',
    '#title' => t('Default user picture'),
    '#options' => [
      'default' => t('Default user icon'),
      'icon' => t('Custom UIkit icon'),
      'custom' => t('Custom picture'),
    ],
    '#description' => t('Select whether to use the default user picture (using the UIkit user icon), a different UIkit icon or a custom picture you can upload.'),
    '#default_value' => UIKit::getThemeSetting('default_user_picture', $theme),
  ];
  $form['uikit_blog_users']['custom_user_picture'] = [
    '#type' => 'container',
    '#title' => t('Custom user picture'),
  ];
  $form['uikit_blog_users']['custom_user_picture']['custom_user_picture_icon'] = [
    '#type' => 'textfield',
    '#title' => t('Font Awesome icon'),
    '#description' => t('Enter the Font Awesome icon class provided by UIkit. A list of available classes can be found <a href="@icon" target="_blank">here</a>.', $args),
    '#default_value' => UIkit::getThemeSetting('custom_user_picture_icon', $theme),
    '#states' => [
      'visible' => [
        ':input[name="default_user_picture"]' => ['value' => 'icon'],
      ],
    ],
  ];
  $form['uikit_blog_users']['custom_user_picture']['upload_wrapper'] = [
    '#type' => 'container',
    '#states' => [
      'visible' => [
        ':input[name="default_user_picture"]' => ['value' => 'custom'],
      ],
    ],
  ];
  $form['uikit_blog_users']['custom_user_picture']['upload_wrapper']['custom_user_picture_upload'] = [
    '#type' => 'managed_file',
    '#title' => t('Upload custom picture'),
    '#upload_location' => 'public://uikit_blog',
    '#description' => t('Upload the custom picture to use as the default user picture. The allowed file extensions are: <em class="placeholder">gif,png, jpg and jpeg</em>.'),
    '#default_value' => UIKit::getThemeSetting('custom_user_picture_upload', $theme),
    '#upload_validators'  => [
      'file_validate_extensions' => ['gif png jpg jpeg'],
    ],
  ];

  // UIkit Blog additional component settings.
  $form['uikit_blog_additional_components'] = [
    '#type' => 'details',
    '#title' => t('Additional components'),
    '#group' => 'uikit_blog',
    '#attributes' => [
      'class' => [
        'uikit-blog-additional-components-settings-form',
      ],
    ],
  ];
  $form['uikit_blog_additional_components']['tooltip'] = [
    '#type' => 'details',
    '#title' => t('Tooltip component'),
    '#description' => t('Easily create nicely looking <a href="@tooltip" target="_blank">tooltips</a>.', $args),
    '#open' => UIkit::getThemeSetting('uikit_tooltips', $theme) ? TRUE : FALSE,
  ];
  $form['uikit_blog_additional_components']['tooltip']['uikit_tooltips'] = [
    '#type' => 'checkbox',
    '#title' => t('UIkit Tooltips'),
    '#description' => t('Use the tooltip component for all elements containing the <em class="placeholder">title</em> attribute.'),
    '#default_value' => UIkit::getThemeSetting('uikit_tooltips', $theme),
  ];
  $form['uikit_blog_additional_components']['tooltip']['tooltip_position'] = [
    '#type' => 'select',
    '#title' => t('Tooltip position'),
    '#description' => t('Tooltip position. Default: top'),
    '#default_value' => UIkit::getThemeSetting('tooltip_position', $theme),
    '#options' => [
      'top' => t('Top'),
      'top-left' => t('Top left'),
      'top-right' => t('Top right'),
      'bottom' => t('Bottom'),
      'bottom-left' => t('Bottom left'),
      'bottom-right' => t('Bottom right'),
      'left' => t('Left'),
      'right' => t('Right'),
    ],
    '#states' => [
      'visible' => [
        ':input[name="uikit_tooltips"]' => ['checked' => TRUE],
      ],
    ],
  ];
  $form['uikit_blog_additional_components']['tooltip']['tooltip_offset'] = [
    '#type' => 'number',
    '#title' => t('Tooltip offset'),
    '#description' => t('The offset of the Tooltip. Default: 0'),
    '#default_value' => UIkit::getThemeSetting('tooltip_offset', $theme),
    '#states' => [
      'visible' => [
        ':input[name="uikit_tooltips"]' => ['checked' => TRUE],
      ],
    ],
  ];
  $form['uikit_blog_additional_components']['tooltip']['tooltip_animation'] = [
    '#type' => 'textfield',
    '#title' => t('Tooltip animation'),
    '#description' => t('The space separated names of animations to use. Comma separate for animation out. A list of available values can be found <a href="@animation">here</a>. Default: uk-animation-scale-up', $args),
    '#default_value' => UIkit::getThemeSetting('tooltip_animation', $theme),
    '#states' => [
      'visible' => [
        ':input[name="uikit_tooltips"]' => ['checked' => TRUE],
      ],
    ],
  ];
  $form['uikit_blog_additional_components']['tooltip']['tooltip_duration'] = [
    '#type' => 'number',
    '#title' => t('Tooltip duration'),
    '#description' => t('The animation duration in ms. Default: 100'),
    '#default_value' => UIkit::getThemeSetting('tooltip_duration', $theme),
    '#states' => [
      'visible' => [
        ':input[name="uikit_tooltips"]' => ['checked' => TRUE],
      ],
    ],
  ];
  $form['uikit_blog_additional_components']['tooltip']['tooltip_delay'] = [
    '#type' => 'number',
    '#title' => t('Tooltip delay'),
    '#description' => t('The show delay in ms. Default: 0'),
    '#default_value' => UIkit::getThemeSetting('tooltip_delay', $theme),
    '#states' => [
      'visible' => [
        ':input[name="uikit_tooltips"]' => ['checked' => TRUE],
      ],
    ],
  ];
  $form['uikit_blog_additional_components']['tooltip']['tooltip_active_class'] = [
    '#type' => 'textfield',
    '#title' => t('Tooltip active class'),
    '#description' => t('The active class. Default: uk-active'),
    '#default_value' => UIkit::getThemeSetting('tooltip_active_class', $theme),
    '#states' => [
      'visible' => [
        ':input[name="uikit_tooltips"]' => ['checked' => TRUE],
      ],
    ],
  ];
}
