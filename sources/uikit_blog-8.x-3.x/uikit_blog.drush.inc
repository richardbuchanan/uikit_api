<?php

/**
 * @file
 * Drush integration of UIkit.
 */

/**
 * Implements hook_drush_command().
 */
function uikit_blog_drush_command() {
  $commands = [];

  $commands['uikit-blog-starterkit'] = [
    'description' => 'Create a UIkit Blog sub-theme.',
    'arguments' => [
      'machine_name' => '[optional] A machine-readable name for your theme.',
      'name' => 'A human-readable name for your theme.',
    ],
    'aliases' => ['uikit-blog-sk'],
    'options' => [
      'name' => 'A human-readable name for your theme.',
      'machine-name' => '[a-z, 0-9, _] A machine-readable name for your theme.',
      'path' => 'The path where your theme will be created. Defaults to: themes',
      'description' => 'A description of your theme.',
    ],
    'examples' => [
      'drush uikit-blog-sk "Amazing name"' => 'Create a sub-theme, using the default options.',
      'drush uikit-blog-sk zomg_amazing "Amazing name"' => 'Create a sub-theme with a specific machine name.',
      'drush uikit-blog-sk "Amazing name" --path=sites/default/themes --description="So amazing."' => 'Create a sub-theme in the specified directory with a custom description.',
    ],
  ];

  return $commands;
}

/**
 * Create a UIkit Blog sub-theme using the starter kit.
 */
function drush_uikit_blog_starterkit($machine_name = NULL, $name = NULL) {
  // Determine the theme name and machine name.
  if (!isset($name)) {
    // If only given one argument, it is the $name.
    if (isset($machine_name)) {
      $name = $machine_name;
      unset($machine_name);
    }
    else {
      $name = drush_get_option('name');
    }

    if (!isset($machine_name)) {
      $machine_name = drush_get_option('machine-name');
    }
  }

  if (!$name) {
    if ($machine_name) {
      $name = $machine_name;
    }
    else {
      if (FALSE) {
        // Allow localize.drupal.org to pick up the string to translate.
        t('The name of the theme was not specified.');
      }
      return drush_set_error('UIKIT_BLOG_SUBTHEME_NAME_NOT_SPECIFIED', dt('The name of the theme was not specified.'));
    }
  }

  if (!$machine_name) {
    $machine_name = $name;
  }

  // Clean up the machine name.
  $machine_name = str_replace(' ', '_', strtolower($machine_name));
  $search = [
    '/[^a-z0-9_]/', // Remove characters not valid in function names.
    '/^[^a-z]+/',   // Functions must begin with an alpha character.
  ];
  $machine_name = preg_replace($search, '', $machine_name);

  // Determine the path to the new sub-theme.
  $subtheme_path = file_exists(DRUPAL_ROOT . '/themes/contrib') ? 'themes/custom' : 'themes';
  if ($path = drush_get_option('path')) {
    $subtheme_path = drush_trim_path($path);
  }
  $subtheme_path = drush_normalize_path(drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . $subtheme_path . '/' . $machine_name);

  // Ensure the destination directory exists.
  if (!is_dir(dirname($subtheme_path))) {
    if (FALSE) {
      // Allow localize.drupal.org to pick up the string to translate.
      t('The directory "!directory" was not found.', ['!directory' => dirname($subtheme_path)]);
    }
    return drush_set_error('UIKIT_BLOG_DESTINATION_NOT_FOUND', dt('The directory "!directory" was not found.', ['!directory' => dirname($subtheme_path)]));
  }

  // Ensure the STARTERKIT directory exists.
  $starterkit_path = drush_normalize_path(drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . drupal_get_path('theme', 'uikit_blog') . '/STARTERKIT');
  if (!is_dir($starterkit_path)) {
    if (FALSE) {
      // Allow localize.drupal.org to pick up the string to translate.
      t('The STARTERKIT directory was not found in "!directory"', ['!directory' => dirname($starterkit_path)]);
    }
    return drush_set_error('UIKIT_BLOG_STARTERKIT_NOT_FOUND', dt('The STARTERKIT directory was not found in "!directory"', ['!directory' => dirname($starterkit_path)]));
  }

  // Make a fresh copy of the original starter kit.
  drush_op('drush_copy_dir', $starterkit_path, $subtheme_path);

  // Rename the STARTERKIT files.
  $subtheme_info_file = $subtheme_path . '/' . $machine_name . '.info.yml';
  $subtheme_libraries_file = $subtheme_path . '/' . $machine_name . '.libraries.yml';
  $subtheme_theme_file = $subtheme_path . '/' . $machine_name . '.theme';

  $subtheme_css_base_file = $subtheme_path . '/css/' . $machine_name . '.base.css';
  $subtheme_css_component_file = $subtheme_path . '/css/' . $machine_name . '.component.css';
  $subtheme_css_layout_file = $subtheme_path . '/css/' . $machine_name . '.layout.css';
  $subtheme_css_theme_file = $subtheme_path . '/css/' . $machine_name . '.theme.css';

  $subtheme_js_theme_file = $subtheme_path . '/js/' . $machine_name . '.theme.js';

  $subtheme_settings_file = $subtheme_path . '/config/install/' . $machine_name . '.settings.yml';
  $subtheme_block_account_menu_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_account_menu.yml';
  $subtheme_block_account_menu_offcanvas_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_account_menu_offcanvas.yml';
  $subtheme_block_branding_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_branding.yml';
  $subtheme_block_breadcrumbs_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_breadcrumbs.yml';
  $subtheme_block_content_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_content.yml';
  $subtheme_block_footer_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_footer.yml';
  $subtheme_block_help_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_help.yml';
  $subtheme_block_local_actions_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_local_actions.yml';
  $subtheme_block_local_tasks_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_local_tasks.yml';
  $subtheme_block_main_menu_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_main_menu.yml';
  $subtheme_block_main_menu_offcanvas_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_main_menu_offcanvas.yml';
  $subtheme_block_messages_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_messages.yml';
  $subtheme_block_page_title_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_page_title.yml';
  $subtheme_block_powered_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_powered.yml';
  $subtheme_block_search_file = $subtheme_path . '/config/optional/block.block.' . $machine_name . '_search.yml';

  $subtheme_block_schema_file = $subtheme_path . '/config/schema/' . $machine_name . '.schema.yml';

  drush_op('rename', drush_normalize_path($subtheme_path . '/STARTERKIT.info.ymltmp'), drush_normalize_path($subtheme_info_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/STARTERKIT.libraries.yml'), drush_normalize_path($subtheme_libraries_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/STARTERKIT.theme'), drush_normalize_path($subtheme_theme_file));

  drush_op('rename', drush_normalize_path($subtheme_path . '/css/STARTERKIT.base.css'), drush_normalize_path($subtheme_css_base_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/css/STARTERKIT.component.css'), drush_normalize_path($subtheme_css_component_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/css/STARTERKIT.layout.css'), drush_normalize_path($subtheme_css_layout_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/css/STARTERKIT.theme.css'), drush_normalize_path($subtheme_css_theme_file));

  drush_op('rename', drush_normalize_path($subtheme_path . '/js/STARTERKIT.theme.js'), drush_normalize_path($subtheme_js_theme_file));

  drush_op('rename', drush_normalize_path($subtheme_path . '/config/install/STARTERKIT.settings.yml'), drush_normalize_path($subtheme_settings_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_account_menu.yml'), drush_normalize_path($subtheme_block_account_menu_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_account_menu_offcanvas.yml'), drush_normalize_path($subtheme_block_account_menu_offcanvas_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_branding.yml'), drush_normalize_path($subtheme_block_branding_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_breadcrumbs.yml'), drush_normalize_path($subtheme_block_breadcrumbs_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_content.yml'), drush_normalize_path($subtheme_block_content_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_footer.yml'), drush_normalize_path($subtheme_block_footer_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_help.yml'), drush_normalize_path($subtheme_block_help_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_local_actions.yml'), drush_normalize_path($subtheme_block_local_actions_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_local_tasks.yml'), drush_normalize_path($subtheme_block_local_tasks_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_main_menu.yml'), drush_normalize_path($subtheme_block_main_menu_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_main_menu_offcanvas.yml'), drush_normalize_path($subtheme_block_main_menu_offcanvas_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_messages.yml'), drush_normalize_path($subtheme_block_messages_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_page_title.yml'), drush_normalize_path($subtheme_block_page_title_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_powered.yml'), drush_normalize_path($subtheme_block_powered_file));
  drush_op('rename', drush_normalize_path($subtheme_path . '/config/optional/block.block.STARTERKIT_search.yml'), drush_normalize_path($subtheme_block_search_file));

  drush_op('rename', drush_normalize_path($subtheme_path . '/config/schema/STARTERKIT.schema.yml'), drush_normalize_path($subtheme_block_schema_file));

  // Alter the contents of the .info.yml file based on the command options.
  $alterations = [
    'name: STARTERKIT' => "name: '" . $name . "'",
    'STARTERKIT/global-styling' => $machine_name . '/global-styling',
  ];
  if ($description = drush_get_option('description')) {
    $alterations['UIkit Blog Sub-theme'] = $description;
  }
  drush_op('uikit_blog_file_str_replace', $subtheme_info_file, array_keys($alterations), $alterations);
  drush_op('uikit_blog_file_str_replace', $subtheme_info_file, 'STARTERKIT', $machine_name);

  // Replace all occurrences of 'STARTERKIT' with the machine name of our sub theme.
  drush_op('uikit_blog_file_str_replace', $subtheme_path . '/README.txt', 'STARTERKIT', $name);
  drush_op('uikit_blog_file_str_replace', $subtheme_libraries_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_theme_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_js_theme_file, 'Drupal.behaviors.STARTERKIT', str_replace(' ', '', 'Drupal.behaviors.' . $name));
  drush_op('uikit_blog_file_str_replace', $subtheme_js_theme_file, 'STARTERKIT', $machine_name);

  drush_op('uikit_blog_file_str_replace', $subtheme_path . '/theme-settings.php', 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_path . '/includes/alter.inc', 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_path . '/includes/preprocess.inc', 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_path . '/includes/theme.inc', 'STARTERKIT', $machine_name);

  drush_op('uikit_blog_file_str_replace', $subtheme_block_account_menu_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_account_menu_offcanvas_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_branding_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_breadcrumbs_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_content_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_footer_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_help_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_local_actions_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_local_tasks_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_main_menu_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_main_menu_offcanvas_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_messages_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_page_title_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_powered_file, 'STARTERKIT', $machine_name);
  drush_op('uikit_blog_file_str_replace', $subtheme_block_search_file, 'STARTERKIT', $machine_name);

  drush_op('uikit_blog_file_str_replace', $subtheme_block_schema_file, 'STARTERKIT theme', $name . ' theme');
  drush_op('uikit_blog_file_str_replace', $subtheme_block_schema_file, 'STARTERKIT.settings', $machine_name . '.settings');
  drush_op('uikit_blog_file_str_replace', $subtheme_block_schema_file, 'STARTERKIT settings', $name . ' settings');

  // Notify user of the newly created theme.
  if (FALSE) {
    // Allow localize.drupal.org to pick up the string to translate.
    t('Starterkit for "!name" created in: !path', ['!name' => $name, '!path' => $subtheme_path]);
  }
  drush_print(dt('Starterkit for "!name" created in: !path', [
    '!path' => $subtheme_path,
    '!name' => $name,
  ]));
}

/**
 * Replace strings in a file.
 */
function uikit_blog_file_str_replace($file_path, $find, $replace) {
  $file_path = drush_normalize_path($file_path);
  $file_contents = file_get_contents($file_path);
  $file_contents = str_replace($find, $replace, $file_contents);
  file_put_contents($file_path, $file_contents);
}
