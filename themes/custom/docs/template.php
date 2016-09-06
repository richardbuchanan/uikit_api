<?php

/**
 * @file
 * Process theme data for docs theme.
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
function docs_preprocess_api_functions(&$variables) {
  foreach ($variables['functions'] as $key => $function) {
    $variables['functions'][$key]['file'] = str_replace('./', '', $function['file']);
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
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_link(&$variables) {
  $path = $variables['path'];
  $components = parse_url($path);
  $external = isset($components['host']) ? TRUE : FALSE;

  if ($external) {
    $variables['options']['attributes']['target'] = '_blank';
    $variables['options']['html'] = TRUE;
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
}

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

    switch ($type) {
      case 'group':
        $type = $item->subgroup ? 'sub-topic' : 'topic';
        break;

      case 'mainpage':
        $type = FALSE;
        $title = check_plain($item->title);
        break;
    }

    if ($type) {
      $title = '<span class="uk-badge">' . $type . '</span> ' . $title;
      $title .= '<hr>';
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
  $output = 0 === strpos($variables['output'], './');

  if ($output) {
    $variables['output'] = str_replace('./', '', $variables['output']);
  }
}

/**
 * Implements template_preprocess_views_view_table().
 */
function docs_preprocess_views_view_table(&$variables) {
  $variables['classes_array'][] = 'uk-table';
  $variables['classes_array'][] = 'uk-table-hover';
  $variables['classes_array'][] = 'uk-table-striped';
  $variables['classes_array'][] = 'uk-table-condensed';
}

/**
 * Implements hook_js_alter().
 */
function docs_js_alter(&$javascript) {
  $theme = drupal_get_path('theme', 'docs');
  $ctools = drupal_get_path('module', 'ctools');
  $collapsible_div = $ctools . '/js/collapsible-div.js';

  if (isset($javascript['misc/autocomplete.js'])) {
    $javascript['misc/autocomplete.js']['data'] = $theme . '/js/autocomplete.js';
  }

  if (isset($javascript['misc/textarea.js'])) {
    $javascript['misc/textarea.js']['data'] = $theme . '/js/textarea.js';
  }
  if (isset($javascript[$collapsible_div])) {
    $javascript[$collapsible_div]['data'] = $theme . '/js/collapsible-div.js';
  }
}

/**
 * Implements hook_block_view_alter().
 */
function docs_block_view_alter(&$data, $block) {
  $delta = $block->delta;
  $module = $block->module;
  $region = $block->region;
  $branch = api_get_active_branch();

  if ($delta == 'navigation' && $module == 'api' && $region == 'sidebar_second') {
    $branch = api_get_active_branch();

    if (user_access('access API reference') && !empty($branch)) {
      // Figure out if this is the default branch for this project, the same
      // way the menu system decides.
      $branches = api_get_branches();
      $projects = _api_make_menu_projects();
      $is_default = ($branch->branch_name === $projects[$branch->project]['use branch']);
      $suffix = ($is_default) ? '' : '/' . $branch->branch_name;

      $types = array(
        'groups' => t('Topics'),
        'classes' => t('Classes'),
        'functions' => t('Functions'),
        'files' => t('Files'),
        'namespaces' => t('Namespaces'),
        'services' => t('Services'),
        'constants' => t('Constants'),
        'globals' => t('Globals'),
        'deprecated' => t('Deprecated'),
      );

      $links = array(
        '#theme_wrappers' => array('container__api__navigation'),
        '#attributes' => array(
          'class' => array('uk-panel', 'uk-panel-box', 'uk-active'),
        ),
      );

      $current_path = current_path();
      $counts = api_listing_counts($branch);
      $item = _db_api_active_item();

      foreach ($types as $type => $title) {
        if ($type === '' || $counts[$type] > 0) {
          $branch_path = 'api/' . $branch->project;
          $path = $branch_path;

          if ($type) {
            $path .= "/$type";
            $title = $title . '<span class="uk-badge uk-float-right">' . $counts[$type] . '</span>';
          }

          $path .= $suffix;
          $class = array();

          if ($type || ($type === '' && !$counts['groups'])) {

            if ($path === $current_path || ($item && preg_match('/^' . $item->object_type . '/', $type))) {
              $class[] = 'uk-active';
            }

            $links[] = array(
              '#theme' => 'link__api__navigation_link',
              '#text' => $title,
              '#path' => $path,
              '#options' => array(
                'html' => TRUE,
                'attributes' => array(
                  'class' => $class,
                ),
              ),
            );
          }
          else {
            $links[] = array(
              '#theme' => 'html_tag__api__navigation_link',
              '#tag' => 'div',
              '#value' => $title,
              '#attributes' => array(
                'class' => $class,
              ),
            );
          }
        }
      }

      $items = array();

      foreach ($branches as $obj) {
        $is_default = ($obj->branch_name === $projects[$obj->project]['use branch']);
        $suffix = ($is_default) ? '' : '/' . $obj->branch_name;

        $items[] = array(
          '#theme' => 'link',
          '#text' => $obj->title,
          '#path' => 'api/' . $obj->project . $suffix,
          '#options' => array(
            'html' => FALSE,
            'attributes' => array(),
          ),
          '#active' => $branch->branch_name === $obj->branch_name,
        );
      }

      $data = array(
        'subject' => t('API Navigation'),
        'content' => array(
          'links' => $links,
          'branches' => array(
            '#theme' => 'bootstrap_dropdown',
            '#toggle' => array(
              '#theme' => 'button',
              '#button_type' => 'button',
              '#value' => t('Projects') . ' <span class="caret"></span>',
              '#attributes' => array(
                'class' => array('btn-default', 'btn-block'),
              ),
            ),
            '#items' => $items,
          ),
        ),
      );
    }
  }
}

/**
 * Counts items by type for a branch.
 *
 * @param object $branch
 *   Object representing the branch to count.
 *
 * @return array
 *   Associative array where the keys are the type of listing ('functions',
 *   'classes', etc.) and the values are the count of how many there are in
 *   that listing for the given branch.
 */
function api_listing_counts($branch) {
  static $cached_counts = array();

  // Check the cache.
  $key = $branch->branch_name . $branch->branch_id;
  if (isset($cached_counts[$key])) {
    return $cached_counts[$key];
  }

  $return = array(
    'groups' => 0,
    'classes' => 0,
    'functions' => 0,
    'constants' => 0,
    'globals' => 0,
    'files' => 0,
    'namespaces' => 0,
    'deprecated' => 0,
    'services' => 0,
    'elements' => 0,
  );

  // These queries mirror what is done in the views used by api_page_listing().
  $query = db_select('api_documentation', 'ad')
    ->condition('branch_id', $branch->branch_id)
    ->condition('object_type', 'group')
    ->groupBy('branch_id');
  $query->addExpression('COUNT(*)', 'num');
  $return['groups'] = $query
    ->execute()
    ->fetchField();

  $query = db_select('api_documentation', 'ad')
    ->condition('branch_id', $branch->branch_id)
    ->condition('namespace', '', '<>')
    ->groupBy('namespace');
  $query->addExpression('COUNT(*)', 'num');
  $return['namespaces'] = $query
    ->execute()
    ->fetchField();

  $query = db_select('api_documentation', 'ad')
    ->condition('branch_id', $branch->branch_id)
    ->condition('object_type', array('class', 'interface', 'trait'))
    ->condition('class_did', 0)
    ->groupBy('branch_id');
  $query->addExpression('COUNT(*)', 'num');
  $return['classes'] = $query
    ->execute()
    ->fetchField();

  $query = db_select('api_reference_storage', 'ars')
    ->condition('branch_id', $branch->branch_id)
    ->condition('object_type', array('element'));
  $query->addExpression('COUNT(*)', 'num');
  $return['elements'] = $query
    ->execute()
    ->fetchField();

  $query = db_select('api_documentation', 'ad')
    ->condition('branch_id', $branch->branch_id)
    ->condition('deprecated', '', '<>')
    ->groupBy('branch_id');
  $query->addExpression('COUNT(*)', 'num');
  $return['deprecated'] = $query
    ->execute()
    ->fetchField();

  foreach (array('function', 'constant', 'global', 'file', 'service') as $type) {
    $query = db_select('api_documentation', 'ad')
      ->condition('branch_id', $branch->branch_id)
      ->condition('object_type', $type)
      ->condition('class_did', 0)
      ->groupBy('branch_id');
    $query->addExpression('COUNT(*)', 'num');
    $return[$type . 's'] = $query
      ->execute()
      ->fetchField();
  }

  $cached_counts[$key] = $return;
  return $return;
}

/**
 * Returns HTML to wrap child elements in the API navigation block container.
 *
 * Used for grouped form items. Can also be used as a theme wrapper for any
 * renderable element, to surround it with a <div> and add attributes such as
 * classes or an HTML ID.
 *
 * See the @link forms_api_reference.html Form API reference @endlink for more
 * information on the #theme_wrappers render array property.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #id, #attributes, #children.
 *
 * @ingroup themeable
 */
function docs_container__api($variables) {
  $element = $variables['element'];
  // Ensure #attributes is set.
  $element += array('#attributes' => array());

  // Special handling for form elements.
  if (isset($element['#array_parents'])) {
    // Assign an html ID.
    if (!isset($element['#attributes']['id'])) {
      $element['#attributes']['id'] = $element['#id'];
    }
    // Add the 'form-wrapper' class.
    $element['#attributes']['class'][] = 'form-wrapper';
  }

  return '<div' . drupal_attributes($element['#attributes']) . '><ul class="uk-nav uk-nav-side">' . $element['#children'] . '</ul></div>';
}

/**
 * Returns HTML for a link in the API navigation block.
 *
 * All Drupal code that outputs a link should call the l() function. That
 * function performs some initial preprocessing, and then, if necessary, calls
 * theme('link') for rendering the anchor tag.
 *
 * To optimize performance for sites that don't need custom theming of links,
 * the l() function includes an inline copy of this function, and uses that
 * copy if none of the enabled modules or the active theme implement any
 * preprocess or process functions or override this theme implementation.
 *
 * @param array $variables
 *   An associative array containing the keys:
 *   - text: The text of the link.
 *   - path: The internal path or external URL being linked to. It is used as
 *     the $path parameter of the url() function.
 *   - options: (optional) An array that defaults to empty, but can contain:
 *     - attributes: Can contain optional attributes:
 *       - class: must be declared in an array. Example: 'class' =>
 *         array('class_name1','class_name2').
 *       - title: must be a string. Example: 'title' => 'Example title'
 *       - Others are more flexible as long as they work with
 *         drupal_attributes($variables['options']['attributes]).
 *     - html: Boolean flag that tells whether text contains HTML or plain
 *       text. If set to TRUE, the text value will not be sanitized so the
 *       calling function must ensure that it already contains safe HTML.
 *   The elements $variables['options']['attributes'] and
 *   $variables['options']['html'] are used in this function similarly to the
 *   way that $options['attributes'] and $options['html'] are used in l().
 *   The link itself is built by the url() function, which takes
 *   $variables['path'] and $variables['options'] as arguments.
 *
 * @see l()
 * @see url()
 */
function docs_link__api($variables) {
  $active = FALSE;

  if (in_array('uk-active', $variables['options']['attributes']['class'])) {
    $active = TRUE;
  }

  return '<li' . ($active ? ' class="uk-active"' : '') . '><a href="' . check_plain(url($variables['path'], $variables['options'])) . '"' . drupal_attributes($variables['options']['attributes']) . '>' . ($variables['options']['html'] ? $variables['text'] : check_plain($variables['text'])) . '</a></li>';
}

/**
 * Implementation of theme_hook().
 */
function docs_captcha($element) {
  $captcha = theme_captcha($element);
  if (strncmp($element["element"]["#captcha_type"], "hidden_captcha/", 15) == 0) {
    //generate a random class name
    $chars = "abcdfghjkmnpqrstvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    $class = "";
    for ($i = 0; $i < 64; ++$i) $class .= substr($chars, rand(0, strlen($chars)-1), 1);
    $class .= ' uk-form-row uk-hidden';
    //hide the random class via css
    drupal_add_css(".$class{display:none;width:0;height:0;overflow:hidden;}","inline"); // TODO: move the random class to an external file
    //html for the captcha
    $captcha = "<div class=\"$class\">" . $captcha . "</div>";
  }
  return $captcha;
}
