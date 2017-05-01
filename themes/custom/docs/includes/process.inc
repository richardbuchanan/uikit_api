<?php

/**
 * @file
 * Set up variables to be placed within the template (.tpl.php) files.
 *
 * The variables set up here apply to both templates (.tpl.php) files and
 * functions (theme_HOOK). See preprocess.inc for providing
 * @link https://www.drupal.org/node/223440 template suggestions @endlink.
 *
 * @see preprocess.inc
 */

/**
 * Implements template_process_page().
 */
function docs_process_page(&$variables) {
  $variables['title_attributes_array'] = array(
    'id' => 'page-title',
    'class' => array(
      'uk-article-title',
      'uk-margin-top-remove',
    ),
  );

  if ($item = _db_api_active_item()) {
    $type = $item->object_type;
    $title = preg_replace('/^' . $type . '\s?/i', '', $variables['title']);
    $filename = $item->file_name;
    $file_extension = pathinfo($filename, PATHINFO_EXTENSION);
    $prism = '';

    switch ($type) {
      case 'group':
        $type = $item->subgroup ? 'sub-topic' : 'topic';
        break;

      case 'mainpage':
        $type = FALSE;
        $title = check_plain($item->title);
        break;
    }

    switch ($file_extension) {
      case 'engine':
      case 'inc':
      case 'install':
      case 'module':
      case 'php':
      case 'profile':
      case 'test':
      case 'theme':
        $prism = 'prism.php.js';
        break;

      case 'twig':
      case 'yml':
      case 'ymltmp':
        $prism = 'prism.yaml_twig.js';
        break;

      case 'info':
      case 'txt':
        $prism = 'prism.ini.js';
        break;

      case 'css':
      case 'js':
        $prism = 'prism.css_js.js';
        break;

      case 'sh':
        $prism = 'prism.bash.js';
        break;

      case 'htm':
      case 'html':
        $prism = 'prism.html.js';
        break;
    }

    if ($type) {
      $title = '<span class="uk-badge">' . $type . '</span> ' . $title;
      $title .= '<hr>';
    }

    if ($prism) {
      $docs = drupal_get_path('theme', 'docs');
      $prism = $docs . '/vendor/prism/' . $prism;
      drupal_add_js($prism, array(
        'group' => JS_THEME,
      ));
    }

    $variables['title'] = $title;
    $variables['title_attributes_array']['class'][] = 'docs-api-title';
  }
  $path_alias = drupal_get_path_alias();

  switch ($path_alias) {
    case '403':
    case '404':
      $variables['title_class'] = 'uk-hidden';
      break;
  }

  $variables['title_attributes'] = drupal_attributes(($variables['title_attributes_array']));
}

/**
 * Implements template_preprocess_views_view_table().
 */
function docs_process_views_view_table(&$variables) {
  $view = $variables['view'];
  $display = $view->display;
  $display_default = isset($display['default']) ? $display['default'] : 0;
  $id = $display_default ? $display_default->id : 0;
  $name = $view->name;
  $attributes_array = array();

  $attributes_array['class'] = array(
    'uk-table-hover',
    'uk-table-striped',
    'uk-table-condensed',
    'uk-text-nowrap',
  );

  if ($id) {
    $view_id = array(str_replace('_', '-', $name));
    $view_id[] = str_replace('_', '-', $id);
    $attributes_array['id'] = implode('-', $view_id);
  }

  $variables['attributes_array'] = $attributes_array;
}
