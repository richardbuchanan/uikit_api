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

use Drupal\docs\Docs;

/**
 * Implements template_preprocess_html().
 */
function docs_preprocess_html(&$variables) {
  $current_path = current_path();
  $api_projects = Docs::getApiProjects();

  foreach ($api_projects as $project) {
    if ($project['url'] == $current_path) {
      $variables['head_title_array']['title'] = $project['title'];
    }
    elseif ($project['default_url'] == $current_path) {
      $variables['head_title_array']['title'] = $project['title'];
    }
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
  elseif ($current_page[0] == 'search') {
    $variables['display_breadcrumb'] = FALSE;
  }

  if (drupal_is_front_page()) {
    $variables['title'] = '';
    $variables['page_container_attributes_array'] = array(
      'id' => 'page',
    );
    $variables['navbar_attributes_array'] = array(
      'id' => 'page-navbar',
      'class' => array('uk-navbar', 'uk-navbar-attached'),
    );
  }
  else {
    $variables['page_container_attributes_array']['class'][] = 'uk-margin-bottom';
    $alias = drupal_get_path_alias(current_path());

    if ($alias == '403' || $alias == '404' || $alias == 'getting-involved') {
      $variables['title'] = FALSE;
    }
  }

  if (isset($variables['page']['content']['system_main']['comment_form'])) {
    $name = $variables['page']['content']['system_main']['comment_form']['#node']->name;
    $node_title = $variables['page']['content']['system_main']['comment_form']['#node']->title;
    $title = t('Reply to <em class="placeholder">@title</em> by @author', array(
      '@title' => $node_title,
      '@author' => $name,
    ));
    drupal_set_title($title, PASS_THROUGH);
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

    $variables['wrapper_attributes_array']['class'][] = 'uk-panel';
    $variables['wrapper_attributes_array']['class'][] = 'uk-panel-box';
    $variables['wrapper_attributes_array']['class'][] = 'uk-panel-box-secondary';
  }
}

/**
 * Implements template_preprocess_block().
 */
function docs_preprocess_block(&$variables) {
  $block_id = $variables['block_html_id'];
  $region = $variables['block']->region;
  $feed = substr($block_id, 0, 21) === 'block-aggregator-feed';
  $book_navigation = $block_id == 'block-book-navigation';

  if ($feed && $region == 'sidebar_second') {
    $content = str_replace('<ul class="uk-list">', '<ul>', $variables['content']);
    $variables['content'] = $content;
  }

  if ($region == 'sidebar_first' || $region == 'sidebar_second') {
    $variables['classes_array'][] = 'uk-margin-bottom';
  }

  if ($book_navigation) {
    $variables['classes_array'] = array('block', 'block-book');
    foreach ($variables['elements'] as $element_key => $element) {
      $book_toc_element = is_array($element) && isset($element['#theme_wrappers']);

      if ($book_toc_element) {
        foreach ($element as $book_toc_key => $book_toc) {
          $book_parent = is_array($book_toc) && isset($book_toc['#theme']);

          if ($book_parent) {
            $title = $book_toc['#title'];
            $href = $book_toc['#href'];
            $block_title = l(t('@title', array('@title' => $title)), $href);
            $variables['block']->subject = $block_title;
            $variables['book_menu_nav_header'] = $block_title;

            if ($book_toc['#below']) {
              $nav_header = array(
                '#theme' => 'menu_link__book_toc',
                '#title' => $book_toc['#title'],
                '#href' => $href,
                '#attributes' => array('class' => 'uk-nav-header'),
                '#below' => array(),
                '#original_link' => array('depth' => 0),
                '#nav_header' => TRUE,
              );
              $book_toc['#below']['#theme_wrappers'] = array('menu_tree__book_toc__block');
              $book_menu = $book_toc['#below'];
              array_unshift($book_menu, $nav_header);
              $variables['book_menu'] = $book_menu;
            }
          }
        }
      }
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
      unset($login_form['links']);
      $login_form['actions']['#attributes']['class'][] = 'uk-margin-top';
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

  if ($variables['type'] == 'forum') {
    $variables['classes_array'][] = 'uk-comment';
    $variables['classes_array'][] = 'uk-margin-bottom';
    $account = $variables['account'];
    $signature = '';

    $random_quotes = $account->field_random_quotes['und'][0]['value'];
    if ($random_quotes) {
      $quotes_author = $account->field_random_quotes_author['und'][0]['value'];
      $random_quote = docs_companion_get_random_quote($quotes_author);
      $signature = "<p>$random_quote</p><small>$quotes_author</small>";
    }
    elseif (!empty($account->signature)) {
      $signature = $account->signature;
    }

    $variables['author_link'] = theme('username', array('account' => $account));
    $variables['author_signature'] = $signature;
  }
}

/**
 * Implements template_preprocess_comment().
 */
function docs_preprocess_comment(&$variables) {
  if (isset($variables['theme_hook_suggestion']) && $variables['theme_hook_suggestion'] == 'advanced_forum_post') {
    $account = $variables['account'];
    dpm($account);

    $comment = $variables['elements']['#comment'];
    $id = $variables['id'] + 1;
    $uri = entity_uri('comment', $comment);
    $uri['options'] += array('attributes' => array('class' => array('permalink'), 'rel' => 'bookmark'));

    $variables['author_link'] = theme('username', array('account' => $account));
    $variables['classes_array'][] = 'uk-margin-bottom';
    $variables['permalink'] = l(t('#@id', array('@id' => $id)), $uri['path'], $uri['options']);
  }
}

/**
 * Implements template_preprocess_comment_wrapper().
 */
function docs_preprocess_comment_wrapper(&$variables) {
  $variables['classes_array'] = array('comment-wrapper');
  $variables['content']['comment_form']['actions']['#attributes']['class'][] = 'uk-margin-top';

  if (isset($variables['content']['comment_form']['#form_id']) && $variables['content']['comment_form']['#form_id'] == 'comment_node_forum_form') {
    $variables['original_author'] = $variables['content']['#node']->name;
  }
  else {
    $variables['original_author'] = 0;
  }
}

/**
 * Implements template_preprocess_menu_tree().
 */
function docs_preprocess_menu_tree(&$variables) {
  $theme_wrappers = $variables['#tree']['#theme_wrappers'];

  foreach ($theme_wrappers as $theme_wrapper) {
    preg_match('/(menu_tree__book_toc_\d+$)/', $theme_wrapper, $book_toc);
    if (isset($book_toc[1])) {
      $theme_wrappers = array('menu_tree__book_toc');
    }
  }

  $variables['theme_hook_suggestions'] = $theme_wrappers;
}

/**
 * Implements template_preprocess_user_profile().
 */
function docs_preprocess_user_profile(&$variables) {
  $account = $variables['elements']['#account'];
  $signature = $account->signature;
  $quotes = isset($account->field_random_quotes['und']) ? $account->field_random_quotes['und'][0]['value'] : 0;
  $quotes_author = isset($account->field_random_quotes_author['und']) ? $account->field_random_quotes_author['und'][0]['value'] : 0;
  $signature_output = '<div class="user-signature uk-float-right">';

  $variables['elements']['user_picture']['#weight'] = 0;

  if ($quotes && $quotes_author) {
    $random_quote = docs_companion_get_random_quote($quotes_author);
    $signature = "<p>$random_quote</p>";
    $signature .= "<small>$quotes_author</small>";
  }

  if ($quotes || !empty($signature)) {
    $signature_output .= "<blockquote>$signature</blockquote>";
    $signature_output .= '</div>';

    $variables['elements']['signature'] = array(
      '#markup' => $signature_output,
      '#weight' => 1,
    );
  }

  $variables['elements']['divider'] = array(
    '#markup' => '<hr class="uk-article-divider user-profile-divider">',
    '#weight' => 2,
  );

  $variables['elements']['field_about_me']['#weight'] = 3;
  $variables['elements']['summary']['#weight'] = 4;

  // Helpful $user_profile variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    $variables['user_profile'][$key] = $variables['elements'][$key];
  }
}

/**
 * Implements template_preprocess_views_view().
 */
function docs_preprocess_views_view__advanced_forum_topic_list(&$variables) {
  $variables['forum_tools'] = 0;
  $tid = $variables['view']->query->where[0]['conditions'][0]['value'];
  $mark_as_read = array();
  advanced_forum_get_mark_read_link($tid, $mark_as_read);
  if (isset($mark_as_read['mark-read'])) {
    $variables['forum_tools'] = l($mark_as_read['mark-read']['title'], $mark_as_read['mark-read']['href']);
  }

  $path = explode('/', current_path());
  $tid = $path[1];
  $forum = taxonomy_term_load($tid);
  $variables['parent_forum'] = count($forum->forums);
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
    $output = str_replace('sources/<wbr />uikit-8.x-3.x/<wbr />', '', $output);
    $output = str_replace('sources/<wbr />uikit_admin-7.x-2.x/<wbr />', '', $output);
    $output = str_replace('sources/<wbr />uikit_blog-8.x-2.x/<wbr />', '', $output);
    $output = str_replace('sources/<wbr />uikit_blog-8.x-3.x/<wbr />', '', $output);
    $output = str_replace('sources/<wbr />uikit_components-7.x-2.x/<wbr />', '', $output);
    $output = str_replace('sources/<wbr />uikit_components-7.x-3.x/<wbr />', '', $output);
    $output = str_replace('sources/<wbr />uikit_components-8.x-2.x/<wbr />', '', $output);
    $output = str_replace('sources/<wbr />uikit_components-8.x-3.x/<wbr />', '', $output);

    $output = str_replace('sources/uikit-7.x-2.x/', '', $output);
    $output = str_replace('sources/uikit-7.x-3.x/', '', $output);
    $output = str_replace('sources/uikit-8.x-2.x/', '', $output);
    $output = str_replace('sources/uikit-8.x-3.x/', '', $output);
    $output = str_replace('sources/uikit_admin-7.x-2.x/', '', $output);
    $output = str_replace('sources/uikit_blog-8.x-2.x/', '', $output);
    $output = str_replace('sources/uikit_blog-8.x-3.x/', '', $output);
    $output = str_replace('sources/uikit_components-7.x-2.x/', '', $output);
    $output = str_replace('sources/uikit_components-7.x-3.x/', '', $output);
    $output = str_replace('sources/uikit_components-8.x-2.x/', '', $output);
    $output = str_replace('sources/uikit_components-8.x-3.x/', '', $output);
    $variables['output'] = $output;
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_forum_icon(&$variables) {
  $variables['icon'] = 0;

  switch ($variables['icon_class']) {
    case 'default':
      $variables['icon'] = '<i class="uk-icon uk-icon-comments uk-icon-medium uk-text-primary"></i>';
      break;

    case 'new':
      $variables['icon'] = '<i class="uk-icon uk-icon-comments uk-icon-medium uk-text-primary"></i>';
      $variables['icon'] .= '<i class="uk-icon uk-icon-plus uk-position-absolute uk-contrast docs-icon-mini"></i>';
      break;

    case 'hot':
      $variables['icon'] = '<i class="uk-icon uk-icon-comments uk-icon-medium uk-text-success"></i>';
      break;

    case 'hot-new':
      $variables['icon'] = '<i class="uk-icon uk-icon-comments uk-icon-medium uk-text-success"></i>';
      $variables['icon'] .= '<i class="uk-icon uk-icon-plus uk-position-absolute uk-contrast docs-icon-mini"></i>';
      break;

    case 'sticky':
      $variables['icon'] = '<i class="uk-icon uk-icon-comments uk-icon-medium"></i>';
      $variables['icon'] .= '<i class="uk-icon uk-icon-thumb-tack uk-position-absolute uk-contrast docs-icon-mini"></i>';
      break;

    case 'closed':
      $variables['icon'] = '<i class="uk-icon uk-icon-comments uk-icon-medium uk-text-danger"></i>';
      $variables['icon'] .= '<i class="uk-icon uk-icon-lock uk-position-absolute uk-contrast docs-icon-mini"></i>';
      break;
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_forum_list(&$variables) {
  foreach ($variables['tables'] as $table_id => $table) {
    foreach ($table['items'] as $item_id => $item) {
      if ($item->new_topics || $item->new_posts || $item->child_new_topics || $item->child_new_posts) {
        $variables['tables'][$table_id]['items'][$item_id]->badge_classes = 'uk-badge uk-badge-success';
        $variables['tables'][$table_id]['items'][$item_id]->icon_classes = 'uk-icon uk-icon-star uk-icon-medium';
        $variables['tables'][$table_id]['items'][$item_id]->icon_text = t('New posts');
      }
      else {
        $variables['tables'][$table_id]['items'][$item_id]->badge_classes = 'uk-badge';
        $variables['tables'][$table_id]['items'][$item_id]->icon_classes = 'uk-icon uk-icon-star uk-icon-medium';
        $variables['tables'][$table_id]['items'][$item_id]->icon_text = t('No new posts');
      }

      if (isset($item->subforums) && $item->subforums) {
        $subforum_list = $item->subforum_list;
        $subforums = array();

        foreach ($subforum_list as $subforum_id => $subforum) {
          $new_posts = '<span class="uk-badge uk-badge-success"><i class="uk-icon uk-icon-star uk-icon-medium"></i></span>';
          $no_new_posts = '<span class="uk-badge"><i class="uk-icon uk-icon-star uk-icon-medium"></i></span>';

          $subforums[$subforum_id] = '<td>';
          $subforums[$subforum_id] .= '<div class="uk-margin-top uk-margin-large-left">';
          $subforums[$subforum_id] .= $subforum->new_posts ? $new_posts : $no_new_posts;

          $subforums[$subforum_id] .= '<span class="forum-name uk-margin-left uk-vertical-align-middle">';
          $subforums[$subforum_id] .= l($subforum->name, $subforum->link);
          $subforums[$subforum_id] .= '</span>';

          $subforums[$subforum_id] .= '<div class="uk-form-help-block uk-margin-large-left uk-text-muted">' . $subforum->description . '</div>';

          $subforums[$subforum_id] .= '</div>';
          $subforums[$subforum_id] .= '</td>';

          $subforums[$subforum_id] .= '<td class="uk-text-top">';
          $subforums[$subforum_id] .= '<span>' . $subforum->total_topics . '</span>';
          $subforums[$subforum_id] .= '</td>';

          $subforums[$subforum_id] .= '<td class="uk-text-top">';
          $subforums[$subforum_id] .= '<span>' . $subforum->total_posts . '</span>';
          $subforums[$subforum_id] .= '</td>';

          $subforums[$subforum_id] .= '<td class="uk-text-top">';
          $subforums[$subforum_id] .= '<span>' . $subforum->last_post . '</span>';
          $subforums[$subforum_id] .= '</td>';
        }

        $item->subforums = $subforums;
      }
    }
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_forum_submitted(&$variables) {
  if (isset($variables['topic']->node_title)) {
    $nid = $variables['topic']->nid;
    $node = new stdClass();
    $node->nid = $nid;
    $node->type = $variables['topic']->type;

    $comment_count = db_query('SELECT COUNT(cid) FROM {comment} WHERE nid = :nid', array(':nid' => $nid))->fetchField();
    $new_replies = advanced_forum_reply_num_new($nid);
    $query = advanced_forum_page_first_new($comment_count, $new_replies, $node);

    $title_length = variable_get('advanced_forum_topic_title_length', 15);
    if ($title_length == 0) {
      $short_topic_title = $variables['topic']->node_title;
    }
    else {
      $short_topic_title = truncate_utf8($variables['topic']->node_title, $title_length, TRUE, TRUE);
    }

    $fragment = ($new_replies) ? 'new' : NULL;

    $variables['topic_link'] = l($short_topic_title, "node/$nid", array(
      'query' => $query,
      'fragment' => $fragment,
      'attributes' => array(
        'title' => t('@title', array('@title' => $variables['topic']->node_title)),
      ),
    ));
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_forums(&$variables) {
  $variables['latest_users'] = 0;
  $latest_users = advanced_forum_statistics_latest_users();
  if (empty($variables['parents'])) {
    $variables['latest_users'] = implode(', ', $latest_users);
  }

  $variables['forum_legend'] = 0;
  if (!empty($variables['forums'])) {
    $variables['forum_legend'] = theme('advanced_forum_forum_legend');
  }

  $variables['forum_tools'] = 0;

  if (!$variables['tid']) {
    $mark_as_read = array();
    advanced_forum_get_mark_read_link($variables['tid'], $mark_as_read);
    if (isset($mark_as_read['mark-read'])) {
      $variables['forum_tools'] = l($mark_as_read['mark-read']['title'], $mark_as_read['mark-read']['href']);
    }
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_image(&$variables) {
  $style = isset($variables['style_name']) ? $variables['style_name'] : 0;

  if ($style == 'forum_image') {
    $variables['theme_hook_suggestions'][] = 'image__forum';
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_api_class_page(&$variables) {
  $alternatives = isset($variables['alternatives']) && !empty($variables['alternatives']) ? $variables['alternatives'] : FALSE;
  $defined = isset($variables['defined']) ? $variables['defined'] : FALSE;

  if ($alternatives) {
    // Replace arbitrary text in the alternative links.
    $alternatives = str_replace('7.x-2.x sources/uikit-7.x-2.x/', '7.x-2.x ', $alternatives);
    $alternatives = str_replace('7.x-3.x sources/uikit-7.x-3.x/', '7.x-3.x ', $alternatives);
    $alternatives = str_replace('8.x-2.x sources/uikit-8.x-2.x/', '8.x-2.x ', $alternatives);
    $alternatives = str_replace('8.x-3.x sources/uikit-8.x-3.x/', '8.x-3.x ', $alternatives);
    $alternatives = str_replace('7.x-2.x sources/uikit_admin-7.x-2.x/', '7.x-2.x ', $alternatives);
    $alternatives = str_replace('8.x-2.x sources/uikit_blog-8.x-2.x/', '8.x-2.x ', $alternatives);
    $alternatives = str_replace('8.x-3.x sources/uikit_blog-8.x-3.x/', '8.x-3.x ', $alternatives);
    $alternatives = str_replace('7.x-2.x sources/uikit_components-7.x-2.x/', '7.x-2.x ', $alternatives);
    $alternatives = str_replace('7.x-3.x sources/uikit_components-7.x-3.x/', '7.x-3.x ', $alternatives);
    $alternatives = str_replace('8.x-2.x sources/uikit_components-8.x-2.x/', '8.x-2.x ', $alternatives);
    $alternatives = str_replace('8.x-3.x sources/uikit_components-8.x-3.x/', '8.x-3.x ', $alternatives);
    $variables['alternatives'] = $alternatives;
  }
  if ($defined) {
    // Replace arbitrary text in the defined file text.
    $defined = str_replace('sources/<wbr />uikit-7.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit-7.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit-8.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit-8.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_admin-7.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_blog-8.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_blog-8.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_components-7.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_components-7.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_components-8.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_components-8.x-3.x/<wbr />', '', $defined);
    $variables['defined'] = $defined;
  }
}

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
    $alternatives = str_replace('8.x-3.x sources/uikit-8.x-3.x/', '8.x-3.x ', $alternatives);
    $alternatives = str_replace('7.x-2.x sources/uikit_admin-7.x-2.x/', '7.x-2.x ', $alternatives);
    $alternatives = str_replace('8.x-2.x sources/uikit_blog-8.x-2.x/', '8.x-2.x ', $alternatives);
    $alternatives = str_replace('8.x-3.x sources/uikit_blog-8.x-3.x/', '8.x-3.x ', $alternatives);
    $alternatives = str_replace('7.x-1.x sources/uikit_components-7.x-2.x/', '7.x-1.x ', $alternatives);
    $alternatives = str_replace('8.x-1.x sources/uikit_components-7.x-3.x/', '8.x-1.x ', $alternatives);
    $alternatives = str_replace('7.x-1.x sources/uikit_components-8.x-2.x/', '7.x-1.x ', $alternatives);
    $alternatives = str_replace('8.x-1.x sources/uikit_components-8.x-3.x/', '8.x-1.x ', $alternatives);
    $variables['alternatives'] = $alternatives;
  }
  if ($defined) {
    // Replace arbitrary text in the defined file text.
    $defined = str_replace('sources/uikit-7.x-2.x/', '', $defined);
    $defined = str_replace('sources/uikit-7.x-3.x/', '', $defined);
    $defined = str_replace('sources/uikit-8.x-2.x/', '', $defined);
    $defined = str_replace('sources/uikit-8.x-3.x/', '', $defined);
    $defined = str_replace('sources/uikit_admin-7.x-2.x/', '', $defined);
    $defined = str_replace('sources/uikit_blog-8.x-2.x/', '', $defined);
    $defined = str_replace('sources/uikit_blog-8.x-3.x/', '', $defined);
    $defined = str_replace('sources/uikit_components-7.x-2.x/', '', $defined);
    $defined = str_replace('sources/uikit_components-7.x-3.x/', '', $defined);
    $defined = str_replace('sources/uikit_components-8.x-2.x/', '', $defined);
    $defined = str_replace('sources/uikit_components-8.x-3.x/', '', $defined);
    $defined = str_replace('sources/<wbr />uikit-7.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit-7.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit-8.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit-8.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_blog-8.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_blog-8.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_admin-7.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_components-7.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_components-7.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_components-8.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_components-8.x-3.x/<wbr />', '', $defined);
    $variables['defined'] = $defined;
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_api_function_page(&$variables) {
  $see = isset($variables['see']) ? $variables['see'] : FALSE;
  $objects = isset($variables['objects']) ? $variables['objects'] : FALSE;
  $defined = isset($variables['defined']) ? $variables['defined'] : FALSE;

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
  if ($defined) {
    // Replace arbitrary text in the defined file text.
    $defined = str_replace('sources/<wbr />uikit-7.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit-7.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit-8.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit-8.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_admin-7.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_blog-8.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_blog-8.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_components-7.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_components-7.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_components-8.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('sources/<wbr />uikit_components-8.x-3.x/<wbr />', '', $defined);
    $variables['defined'] = $defined;
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_api_functions(&$variables) {
  foreach ($variables['functions'] as $key => $function) {
    $file = $function['file'];

    if (strpos($file, 'uikit-7.x-2.x') !== false) {
      $variables['functions'][$key]['file'] = str_replace('sources/<wbr />uikit-7.x-2.x/<wbr />', '', $file);
    }
    elseif (strpos($file, 'uikit-7.x-3.x') !== false) {
      $variables['functions'][$key]['file'] = str_replace('sources/<wbr />uikit-7.x-3.x/<wbr />', '', $file);
    }
    elseif (strpos($file, 'uikit-8.x-2.x') !== false) {
      $variables['functions'][$key]['file'] = str_replace('sources/<wbr />uikit-8.x-2.x/<wbr />', '', $file);
    }
    elseif (strpos($file, 'uikit-8.x-3.x') !== false) {
      $variables['functions'][$key]['file'] = str_replace('sources/<wbr />uikit-8.x-3.x/<wbr />', '', $file);
    }
    elseif (strpos($file, 'uikit_admin-7.x-2.x') !== false) {
      $variables['functions'][$key]['file'] = str_replace('sources/<wbr />uikit_admin-7.x-2.x/<wbr />', '', $file);
    }
    elseif (strpos($file, 'uikit_blog-8.x-2.x') !== false) {
      $variables['functions'][$key]['file'] = str_replace('sources/<wbr />uikit_blog-8.x-2.x/<wbr />', '', $file);
    }
    elseif (strpos($file, 'uikit_blog-8.x-3.x') !== false) {
      $variables['functions'][$key]['file'] = str_replace('sources/<wbr />uikit_blog-8.x-3.x/<wbr />', '', $file);
    }
    elseif (strpos($file, 'uikit_components-7.x-2.x') !== false) {
      $variables['functions'][$key]['file'] = str_replace('sources/<wbr />uikit_components-7.x-2.x/<wbr />', '', $file);
    }
    elseif (strpos($file, 'uikit_components-7.x-3.x') !== false) {
      $variables['functions'][$key]['file'] = str_replace('sources/<wbr />uikit_components-7.x-3.x/<wbr />', '', $file);
    }
    elseif (strpos($file, 'uikit_components-8.x-2.x') !== false) {
      $variables['functions'][$key]['file'] = str_replace('sources/<wbr />uikit_components-8.x-2.x/<wbr />', '', $file);
    }
    elseif (strpos($file, 'uikit_components-8.x-3.x') !== false) {
      $variables['functions'][$key]['file'] = str_replace('sources/<wbr />uikit_components-8.x-3.x/<wbr />', '', $file);
    }
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
    $alternatives = str_replace('8.x-3.x documentation/uikit-8.x-3.x/', '8.x-3.x ', $alternatives);
    $alternatives = str_replace('7.x-2.x documentation/uikit_admin-7.x-2.x/', '7.x-2.x ', $alternatives);
    $alternatives = str_replace('8.x-2.x documentation/uikit_blog-8.x-2.x/', '8.x-2.x ', $alternatives);
    $alternatives = str_replace('8.x-3.x documentation/uikit_blog-8.x-3.x/', '8.x-3.x ', $alternatives);
    $alternatives = str_replace('7.x-2.x documentation/uikit_components-7.x-2.x/', '7.x-2.x ', $alternatives);
    $alternatives = str_replace('7.x-3.x documentation/uikit_components-7.x-3.x/', '7.x-3.x ', $alternatives);
    $alternatives = str_replace('8.x-2.x documentation/uikit_components-8.x-2.x/', '8.x-2.x ', $alternatives);
    $alternatives = str_replace('8.x-3.x documentation/uikit_components-8.x-3.x/', '8.x-3.x ', $alternatives);
    $variables['alternatives'] = $alternatives;
  }
  if ($defined) {
    // Replace arbitrary text in the defined file text.
    $defined = str_replace('documentation/<wbr />uikit-7.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('documentation/<wbr />uikit-7.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('documentation/<wbr />uikit-8.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('documentation/<wbr />uikit-8.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('documentation/<wbr />uikit_admin-7.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('documentation/<wbr />uikit_blog-8.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('documentation/<wbr />uikit_blog-8.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('documentation/<wbr />uikit_components-7.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('documentation/<wbr />uikit_components-7.x-3.x/<wbr />', '', $defined);
    $defined = str_replace('documentation/<wbr />uikit_components-8.x-2.x/<wbr />', '', $defined);
    $defined = str_replace('documentation/<wbr />uikit_components-8.x-3.x/<wbr />', '', $defined);
    $variables['defined'] = $defined;
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_breadcrumb(&$variables) {
  $breadcrumb = $variables['breadcrumb'];
  if (!empty($breadcrumb)) {
    foreach ($breadcrumb as $key => $crumb) {
      preg_match_all('/<a[^>]+href=([\'"])(.+?)\1[^>]*>/i', $crumb, $result);
      $href = $result[2][0];

      if ($key == 0 || ($key == 1 && $href != '/forum')) {
        unset($variables['breadcrumb'][$key]);
      }
    }
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_button(&$variables) {
  $button_classes = array(
    'uk-button-primary',
    'uk-button-warning',
    'uk-button-danger',
    'uk-button-link',
  );
  $classes = $variables['element']['#attributes']['class'];
  $has_button_class = FALSE;

  foreach ($button_classes as $button_class) {
    if (in_array($button_class, $classes)) {
      $has_button_class = TRUE;
    }
  }

  if (!$has_button_class) {
    $variables['element']['#attributes']['class'][] = 'uk-button-primary';
  }
}

/**
 * Implements hook_preprocess_HOOK() for theme_fieldset().
 */
function docs_preprocess_fieldset(&$variables) {
  if ($variables['element']['#id'] == 'edit-advanced' && $variables['element']['#title'] == 'Advanced search') {
    $variables['element']['#collapsed'] = FALSE;
  }
  $collapsible = isset($variables['element']['#collapsible']) && $variables['element']['#collapsible'];
  $collapsed = isset($variables['element']['#collapsed']) ? $variables['element']['#collapsed'] : 0;

  if ($collapsible && !$collapsed) {
    $variables['element']['#attributes']['data-uk-accordion'] = '{showfirst: true}';
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_image_button(&$variables) {
  $variables['element']['#attributes']['class'][] = 'uk-margin-top';
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
  if ($path == 'user/login' && current_path() != 'user' && current_path() != 'user/login') {
    $variables['options']['attributes']['data-uk-modal'] = '';
    $variables['path'] = '#user-login-modal';
    $variables['options']['external'] = TRUE;
    unset($variables['options']['query']);
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function docs_preprocess_menu_link(&$variables) {
  $href = $variables['element']['#href'];
  $theme = $variables['element']['#theme'];

  preg_match('/(menu_link__book_toc)/', $theme, $book_toc);
  if (isset($book_toc[1])) {
    $variables['theme_hook_suggestions'][] = 'menu_link__book_toc';
  }

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
 * Implements template_preprocess_user_picture().
 */
function docs_preprocess_user_picture(&$variables) {
  $variables['user_picture'] = '';
  $variables['classes_array'] = array(
    'uk-float-left',
    'uk-margin-right',
    'uk-margin-bottom',
  );

  if (variable_get('user_pictures', 0)) {
    $account = $variables['account'];
    if (!empty($account->picture)) {
      // @TODO: Ideally this function would only be passed file objects, but
      // since there's a lot of legacy code that JOINs the {users} table to
      // {node} or {comments} and passes the results into this function if we
      // a numeric value in the picture field we'll assume it's a file id
      // and load it for them. Once we've got user_load_multiple() and
      // comment_load_multiple() functions the user module will be able to load
      // the picture files in mass during the object's load process.
      if (is_numeric($account->picture)) {
        $account->picture = file_load($account->picture);
      }
      if (!empty($account->picture->uri)) {
        $filepath = $account->picture->uri;
      }
    }
    elseif (variable_get('user_picture_default', '')) {
      $filepath = variable_get('user_picture_default', '');
    }
    if (isset($filepath)) {
      $alt = t("@user's picture", array('@user' => format_username($account)));
      // If the image does not have a valid Drupal scheme (for eg. HTTP),
      // don't load image styles.
      if (module_exists('image') && file_valid_uri($filepath) && $style = variable_get('user_picture_style', '')) {
        $variables['user_picture'] = theme('image_style', array(
          'style_name' => $style,
          'path' => $filepath,
          'alt' => $alt,
          'title' => $alt,
          'attributes' => array(
            'class' => array('uk-thumbnail'),
          ),
        ));
      }
      else {
        $variables['user_picture'] = theme('image', array(
          'path' => $filepath,
          'alt' => $alt,
          'attributes' => array(
            'class' => array('uk-thumbnail'),
          ),
        ));
      }
    }
  }
}
