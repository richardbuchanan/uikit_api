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
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_api_defined(&$variables) {
  $variables['file_link'] = str_replace('./', '', $variables['file_link']);
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_api_file_page(&$variables) {
  $see = isset($variables['see']) ? $variables['see'] : FALSE;
  $objects = isset($variables['objects']) ? $variables['objects'] : FALSE;
  $alternatives = isset($variables['alternatives']) && !empty($variables['alternatives']) ? $variables['alternatives'] : FALSE;
  $defined = isset($variables['defined']) ? $variables['defined'] : FALSE;

  if ($see) {
    // Replace see also paragraphs with list items.
    $see = str_replace('<p>', '<li>', $see);
    $see = str_replace('</p>', '</li>', $see);
    $variables['see'] = $see;
  }
  if ($objects) {
    // Replace the objects text with an page anchor and link icon.
    $position = strpos($objects, '</h3>');
    $length = $position + 5;
    $old_title_html = substr($objects, 0, $length);
    $old_title_text = substr($objects, 4, $length - 9);
    $title_id = str_replace(' ', '-', strtolower($old_title_text));
    $new_title = '<a href="#' . $title_id . '" class="uk-link-muted docs-link-anchor">';
    $new_title .= '<h3 id="' . $title_id . '">' . $old_title_text;
    $new_title .= '<i class="uk-icon uk-icon-link uk-text-muted"></i>';
    $new_title .= '</h3></a>';
    $variables['objects'] = str_replace($old_title_html, $new_title, $objects);
  }
  if ($alternatives) {
    // Replace arbitrary text in the alternative links.
    $alternatives = str_replace('7.x-2.x sources/uikit-7.x-2.x/', '7.x-2.x ', $alternatives);
    $alternatives = str_replace('7.x-3.x sources/uikit-7.x-3.x/', '7.x-3.x ', $alternatives);
    $alternatives = str_replace('8.x-2.x sources/uikit-8.x-2.x/', '8.x-2.x ', $alternatives);
    $variables['alternatives'] = $alternatives;
  }
  if ($defined) {
    // Replace arbitrary text in the defined file text.
    $defined = str_replace('sources/uikit-7.x-2.x/', '', $defined);
    $defined = str_replace('sources/uikit-7.x-3.x/', '', $defined);
    $defined = str_replace('sources/uikit-8.x-2.x/', '', $defined);
    $variables['defined'] = $defined;
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_api_function_page(&$variables) {
  $see = isset($variables['see']) ? $variables['see'] : FALSE;
  $objects = isset($variables['objects']) ? $variables['objects'] : FALSE;

  if ($see) {
    $see = str_replace('<p>', '<li>', $see);
    $see = str_replace('</p>', '</li>', $see);
    $variables['see'] = $see;
  }
  if ($objects) {
    $position = strpos($objects, '</h3>');
    $length = $position + 5;
    $old_title_html = substr($objects, 0, $length);
    $old_title_text = substr($objects, 4, $length - 9);
    $title_id = str_replace(' ', '-', strtolower($old_title_text));
    $new_title = '<a href="#' . $title_id . '" class="uk-link-muted docs-link-anchor">';
    $new_title .= '<h3 id="' . $title_id . '">' . $old_title_text;
    $new_title .= '<i class="uk-icon uk-icon-link uk-text-muted"></i>';
    $new_title .= '</h3></a>';
    $variables['objects'] = str_replace($old_title_html, $new_title, $objects);
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_api_functions(&$variables) {
  foreach ($variables['functions'] as $key => $function) {
    $variables['functions'][$key]['file'] = str_replace('./', '', $function['file']);
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_api_global_page(&$variables) {
  $see = isset($variables['see']) ? $variables['see'] : FALSE;
  $objects = isset($variables['objects']) ? $variables['objects'] : FALSE;

  if ($see) {
    $see = str_replace('<p>', '<li>', $see);
    $see = str_replace('</p>', '</li>', $see);
    $variables['see'] = $see;
  }
  if ($objects) {
    $position = strpos($objects, '</h3>');
    $length = $position + 5;
    $old_title_html = substr($objects, 0, $length);
    $old_title_text = substr($objects, 4, $length - 9);
    $title_id = str_replace(' ', '-', strtolower($old_title_text));
    $new_title = '<a href="#' . $title_id . '" class="uk-link-muted docs-link-anchor">';
    $new_title .= '<h3 id="' . $title_id . '">' . $old_title_text;
    $new_title .= '<i class="uk-icon uk-icon-link uk-text-muted"></i>';
    $new_title .= '</h3></a>';
    $variables['objects'] = str_replace($old_title_html, $new_title, $objects);
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_api_group_page(&$variables) {
  $see = isset($variables['see']) ? $variables['see'] : FALSE;
  $objects = isset($variables['objects']) ? $variables['objects'] : FALSE;
  $alternatives = isset($variables['alternatives']) && !empty($variables['alternatives']) ? $variables['alternatives'] : FALSE;
  $defined = isset($variables['defined']) ? $variables['defined'] : FALSE;

  if ($see) {
    // Replace see also paragraphs with list items.
    $see = str_replace('<p>', '<li>', $see);
    $see = str_replace('</p>', '</li>', $see);
    $variables['see'] = $see;
  }
  if ($objects) {
    // Replace the objects text with an page anchor and link icon.
    $position = strpos($objects, '</h3>');
    $length = $position + 5;
    $old_title_html = substr($objects, 0, $length);
    $old_title_text = substr($objects, 4, $length - 9);
    $title_id = str_replace(' ', '-', strtolower($old_title_text));
    $new_title = '<a href="#' . $title_id . '" class="uk-link-muted docs-link-anchor">';
    $new_title .= '<h3 id="' . $title_id . '">' . $old_title_text;
    $new_title .= '<i class="uk-icon uk-icon-link uk-text-muted"></i>';
    $new_title .= '</h3></a>';
    $variables['objects'] = str_replace($old_title_html, $new_title, $objects);
  }
  if ($alternatives) {
    // Replace arbitrary text in the alternative links.
    $alternatives = str_replace('7.x-2.x documentation/uikit-7.x-2.x/', '7.x-2.x ', $alternatives);
    $alternatives = str_replace('7.x-3.x documentation/uikit-7.x-3.x/', '7.x-3.x ', $alternatives);
    $alternatives = str_replace('8.x-2.x documentation/uikit-8.x-2.x/', '8.x-2.x ', $alternatives);
    $variables['alternatives'] = $alternatives;
  }
  if ($defined) {
    // Replace arbitrary text in the defined file text.
    $defined = str_replace('documentation/<wbr />uikit-7.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('documentation/<wbr />uikit-7.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('documentation/<wbr />uikit-8.x-2.x/<wbr />', '', $defined);
    $variables['defined'] = $defined;
  }
}

/**
 * Implements template_preprocess_block().
 */
function docs_preprocess_block(&$variables) {
  $block_id = $variables['block_html_id'];
  $region = $variables['block']->region;
  $feed = substr($block_id, 0, 21) === 'block-aggregator-feed';

  if ($feed && $region == 'sidebar_second') {
    $content = str_replace('<ul class="uk-list">', '<ul>', $variables['content']);
    $variables['content'] = $content;
  }

  if ($region == 'sidebar_first' || $region == 'sidebar_second') {
    $variables['classes_array'][] = 'uk-margin-bottom';
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_breadcrumb(&$variables) {
  $breadcrumb = $variables['breadcrumb'];
  if (!empty($breadcrumb)) {
    foreach ($breadcrumb as $key => $crumb) {
      if ($key == 0 || $key == 1) {
        unset($variables['breadcrumb'][$key]);
      }
    }
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_button(&$variables) {
  $variables['element']['#attributes']['class'][] = 'uk-button-primary';
}

/**
 * Implements template_preprocess_comment_wrapper().
 */
function docs_preprocess_comment_wrapper(&$variables) {
  $variables['classes_array'] = array('comment-wrapper');
  $variables['content']['comment_form']['actions']['#attributes']['class'][] = 'uk-margin-top';
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_link(&$variables) {
  $path = $variables['path'];
  $components = parse_url($path);
  $external = isset($components['host']) ? TRUE : FALSE;
  $local = isset($components['host']) && $components['host'] == $_SERVER['HTTP_HOST'];

  if ($external && !$local) {
    $variables['options']['attributes']['target'] = '_blank';
    $variables['options']['html'] = TRUE;
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_menu_link(&$variables) {
  $href = $variables['element']['#href'];
  $theme = $variables['element']['#theme'];

  if ($theme == 'menu_link__navbar') {
    switch ($href) {
      case 'api/uikit':
        $variables['element']['#localized_options']['attributes']['title'] = t('UIkit 7.x-2.x');
        break;

      case 'api/uikit_admin':
        $variables['element']['#localized_options']['attributes']['title'] = t('UIkit Admin 7.x-2.x');
        break;

      case 'api/uikit_components':
        $variables['element']['#localized_options']['attributes']['title'] = t('UIkit Components 7.x-1.x');
        break;
    }
  }
}

/**
 * Implements template_preprocess_node().
 */
function docs_preprocess_node(&$variables) {
  $node_url = $variables['node_url'];
  $uri = ltrim($_SERVER['REQUEST_URI'], '/');

  if (empty($uri)) {
    $uri = 'this site';
  }
  else {
    $uri = '"' . $uri . '"';
  }

  switch ($node_url) {
    case '/403':
      module_load_include('inc', 'contact', 'contact.pages');
      $contact_form = drupal_get_form('contact_site_form');
      $login_form = drupal_get_form('user_login_block');
      $variables['theme_hook_suggestions'][] = 'node__access_denied';
      $variables['access_message'] = user_is_logged_in() ? 'Please contact your administrator.' : 'Try logging in.';
      $variables['login_form'] = drupal_render($login_form);
      $variables['contact_form'] = render($contact_form);
      $variables['uri'] = $uri;
      break;

    case '/404':
      $variables['theme_hook_suggestions'][] = 'node__page_not_found';
      $variables['search_block'] = module_invoke('search', 'block_view', 'search');
      $variables['uri'] = $uri;
      break;
  }
}

/**
 * Implemments template_preprocess_page().
 */
function docs_preprocess_page(&$variables) {
  $docs = drupal_get_path('theme', 'docs');
  $svg_logo = '/' . $docs . '/logo_large.svg';
  $variables['logo'] = $svg_logo;

  $variables['header_attributes_array']['class'] = array();

  $current_page = explode('/', current_path());
  if ($current_page[0] == 'layouts') {
    $variables['display_breadcrumb'] = FALSE;
    $variables['title'] = '';
  }
}

/**
 * Implemments hook_preprocess_HOOK().
 */
function docs_preprocess_region(&$variables) {
  global $user;
  $is_admin = in_array('administrator', $user->roles);
  $region = $variables['region'];

  if ($region == 'sidebar_second') {
    $top = user_is_logged_in() && $is_admin ? '44' : '15';
    $variables['wrapper_attributes_array']['data-uk-sticky'] = '{boundary: true, media: \'(min-width: 768px)\', top: ' . $top . '}';
    $variables['wrapper_attributes_array']['class'][] = 'uk-panel';
    $variables['wrapper_attributes_array']['class'][] = 'uk-panel-box';
    $variables['wrapper_attributes_array']['class'][] = 'uk-panel-box-secondary';

    drupal_add_css("//cdnjs.cloudflare.com/ajax/libs/uikit/2.26.4/css/components/sticky.min.css", array(
      'type' => 'external',
      'group' => CSS_THEME,
      'every_page' => TRUE,
      'weight' => -10,
      'version' => '2.26.4',
    ));
    drupal_add_js("//cdnjs.cloudflare.com/ajax/libs/uikit/2.26.4/js/components/sticky.min.js", array(
      'type' => 'external',
      'group' => JS_THEME,
      'every_page' => TRUE,
      'weight' => -10,
      'version' => '2.26.4',
    ));
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_table(&$variables) {
  $classes = $variables['attributes']['class'];

  foreach ($classes as $key => $class) {
    if ($class == 'uk-text-nowrap') {
      unset($variables['attributes']['class'][$key]);
    }
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_textfield(&$variables) {
  $element = $variables['element'];
  $autocomplete = isset($element['#autocomplete_path']) ? $element['#autocomplete_path'] : FALSE;
  $api_search = FALSE;

  if ($autocomplete) {
    $autocomplete_path = explode('/', $autocomplete);
    $api_search = $autocomplete_path[0] == 'api' &&
      $autocomplete_path[1] == 'search' &&
      $autocomplete_path[2] == 'autocomplete';
  }

  if ($api_search) {
    $variables['theme_hook_suggestions'][] = 'textfield__api_search';
  }
}

/**
 * Implements template_preprocess_views_view_field().
 */
function docs_preprocess_views_view_field(&$variables) {
  $display = $variables['view']->current_display;
  $block_files = $display == 'block_files';
  $block_listing = $display == 'block_listing';
  $block_items_in_group = 'block_items_in_group';

  if (($block_files || $block_listing || $block_items_in_group) && !empty($variables['output'])) {
    $output = $variables['output'];
    $output = str_replace('sources/<wbr />uikit-7.x-2.x/<wbr />', '', $output);
    $output = str_replace('sources/<wbr />uikit-7.x-3.x/<wbr />', '', $output);
    $output = str_replace('sources/<wbr />uikit-8.x-2.x/<wbr />', '', $output);
    $variables['output'] = $output;
  }
}
