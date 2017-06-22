<?php

/**
 * @file
 * The UIkit theme system, which controls the output of the UIkit theme.
 *
 * The theme system allows for nearly all output of the Drupal system to be
 * customized by UIkit themes.
 */

/**
 * Implements theme_advanced_forum_simple_author_pane().
 */
function docs_advanced_forum_simple_author_pane(&$variables) {
  $context = $variables['context'];
  $account = user_load($context->uid);
  $alt = t("@user's picture", array('@user' => format_username($account)));
  $style = variable_get('user_picture_style', '');

  if (!empty($account->picture->uri)) {
    $filepath = $account->picture->uri;

    return theme('image_style', array(
      'style_name' => $style,
      'path' => $filepath,
      'title' => $alt,
      'alt' => $alt,
      'attributes' => array(
        'class' => array('uk-comment-avatar'),
      ),
    ));
  }
  else {
    $filepath = variable_get('user_picture_default');

    return theme('image', array(
      'path' => $filepath,
      'title' => $alt,
      'alt' => $alt,
      'attributes' => array(
        'class' => array('uk-comment-avatar'),
      ),
    ));
  }
}

/**
 * Implements theme_advanced_forum_node_type_create_list().
 */
function docs_advanced_forum_node_type_create_list(&$variables) {
  $forum_id = $variables['forum_id'];

  // Get the list of node types to display links for.
  $type_list = advanced_forum_node_type_create_list($forum_id);

  $output = '<ul class="uk-list">';
  $options = array(
    'attributes' => array(
      'class' => array('uk-button', 'uk-button-primary'),
    ),
  );

  if (is_array($type_list)) {
    foreach ($type_list as $type => $item) {
      $output .= '<li>' . l(t('New @node_type', array('@node_type' => $item['name'])), $item['href'], $options) . '</li>';
    }
  }
  else {
    // User did not have access to create any node types in this fourm so
    // we just return the denial text / login prompt.
    $output = '<li>' . $type_list . '</li>';
  }

  $output .= '</ul>';
  return $output;
}

/**
 * Implements theme_breadcrumb().
 */
function docs_breadcrumb(&$variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .uk-hidden.
    $output = '<h2 class="uk-hidden">' . t('You are here') . '</h2>';

    $output .= '<ul class="uk-breadcrumb uk-margin-small-bottom">';

    foreach ($breadcrumb as $crumb) {
      $output .= '<li>' . $crumb . '</li>';
    }

    $output .= '</ul>';
    return $output;
  }
}

/**
 * Implementation of theme_hook().
 */
function docs_captcha($element) {
  $captcha = theme_captcha($element);

  if (strncmp($element["element"]["#captcha_type"], "hidden_captcha/", 15) == 0) {
    // Generate a random class name.
    $chars = "abcdfghjkmnpqrstvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    $class = "";

    for ($i = 0; $i < 64; ++$i) {
      $class .= substr($chars, rand(0, strlen($chars) - 1), 1);
    }

    $class .= ' uk-form-row uk-hidden';

    // Hide the random class via css.
    drupal_add_css(".$class{display:none;width:0;height:0;overflow:hidden;}", "inline");

    // Html for the captcha.
    $captcha = "<div class=\"$class\">" . $captcha . "</div>";
  }

  return $captcha;
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
 * @return string
 *   Returns rendered wrapper element.
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
 * Implements theme_field().
 */
function docs_field__field_about_me__user(&$variables) {
  $output = '<div class="uk-margin-bottom user-profile-about">';
  $username = $variables['element']['#object']->name;

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<p class="uk-article-lead">About ' . $username . '</p>';
  }

  // Render the items.
  foreach ($variables['items'] as $delta => $item) {
    $output .= '<div>' . drupal_render($item) . '</div>';
  }

  $output .= '</div>';
  return $output;
}

/**
 * Implements theme_field().
 */
function docs_field__field_image__forum(&$variables) {
  $output = '<div class="uk-panel uk-panel-box uk-panel-box-secondary uk-panel-header uk-margin-large-top uk-margin-large-bottom">';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<h3 class="uk-panel-title">' . $variables['label'] . '</h3>';
  }

  foreach ($variables['items'] as $delta => $item) {
    $variables['items'][$delta]['#theme_hook_suggestions'][] = 'image__forum_post';
    $output .= drupal_render($item);
  }
  $output .= '</div>';

  return $output;
}

/**
 * Implements theme_image().
 */
function docs_image__forum($variables) {
  $attributes = $variables['attributes'];
  $attributes['src'] = file_create_url($variables['path']);

  foreach (array('width', 'height', 'alt', 'title') as $key) {
    if (isset($variables[$key])) {
      $attributes[$key] = $variables[$key];
    }
  }

  return '<img' . drupal_attributes($attributes) . ' />';
}

/**
 * Implements theme_image_formatter().
 */
function docs_image_formatter($variables) {
  $item = $variables['item'];
  $image = array(
    'path' => $item['uri'],
  );

  if (array_key_exists('alt', $item)) {
    $image['alt'] = $item['alt'];
  }

  if (isset($item['attributes'])) {
    $image['attributes'] = $item['attributes'];
  }

  if (isset($item['width']) && isset($item['height'])) {
    $image['width'] = $item['width'];
    $image['height'] = $item['height'];
  }

  // Do not output an empty 'title' attribute.
  if (isset($item['title']) && drupal_strlen($item['title']) > 0) {
    $image['title'] = $item['title'];
  }

  if ($variables['image_style']) {
    $image['style_name'] = $variables['image_style'];
    $output = theme('image_style', $image);
  }
  else {
    $output = theme('image', $image);
  }

  // The link path and link options are both optional, but for the options to be
  // processed, the link path must at least be an empty string.
  if (isset($variables['path']['path'])) {
    $path = $variables['path']['path'];
    $options = isset($variables['path']['options']) ? $variables['path']['options'] : array();

    // When displaying an image inside a link, the html option must be TRUE.
    $options['html'] = TRUE;

    if ($variables['image_style'] && $variables['image_style'] == 'forum_image') {
      uikit_get_cdn_asset('lightbox');
      uikit_get_cdn_asset('slidenav');
      $options['attributes']['data-uk-lightbox'] = "{group:'forum-post-images'}";
    }

    $output = l($output, $path, $options);
  }

  return $output;
}

/**
 * Implements theme_item_list().
 */
function docs_item_list(&$variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];
  $pager = in_array('uk-pagination', $variables['attributes']['class']);

  // Only output the list container and title, if there are any list items.
  // Check to see whether the block title exists before adding a header.
  // Empty headers are not semantic and present accessibility challenges.
  $output = '';
  if (!$pager) {
    $output .= '<div class="item-list">';
  }
  if (isset($title) && $title !== '') {
    $output .= '<h3>' . $title . '</h3>';
  }

  // Do not add uk-list classes if this is a pager.
  if (!$pager) {
    $attributes['class'][] = 'uk-list';
    $attributes['class'][] = 'uk-list-line';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    $i = 0;
    foreach ($items as $item) {
      $attributes = array();
      $children = array();
      $data = '';
      $i++;
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }

      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array(
          'items' => $children,
          'title' => NULL,
          'type' => $type,
          'attributes' => $attributes,
        ));
      }

      if ($i == 1) {
        $attributes['class'][] = 'first';
      }

      if ($i == $num_items) {
        $attributes['class'][] = 'last';
      }

      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }

    $output .= "</$type>";
  }

  if (!$pager) {
    $output .= '</div>';
  }
  return $output;
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
 * @return string
 *   Returns a rendered list item.
 *
 * @see l()
 * @see url()
 */
function docs_link__api($variables) {
  $active = FALSE;

  if (in_array('uk-active', $variables['options']['attributes']['class'])) {
    $active = TRUE;
  }

  return '<li' . ($active ? ' class="uk-active"' : '') . '><a href="' . check_plain(url($variables['path'], $variables['options'])) . '" ' . drupal_attributes($variables['options']['attributes']) . ' >' . ($variables['options']['html'] ? $variables['text'] : check_plain($variables['text'])) . '</a></li>';
}

/**
 * Implements theme_links() for comment links.
 */
function docs_links__comment($variables) {
  $links = $variables['links'];
  $heading = $variables['heading'];
  $output = '';

  if (count($links) > 0) {
    // Treat the heading first if it is present to prepend it to the list of
    // links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading is a
        // string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $link['attributes']['class'] = array(str_replace('_', '-', $key));

      // Add the UIkit button utility classes.
      $link['attributes']['class'][] = 'uk-button';

      if ($key == 'node-readmore') {
        $link['attributes']['class'][] = 'uk-button-primary';
      }

      $link['attributes']['class'][] = 'uk-margin-small-right';

      // Add first and last classes to the list of links to help out themers.
      if ($i == 1) {
        $link['attributes']['class'][] = 'first';
      }

      if ($i == $num_links) {
        $link['attributes']['class'][] = 'last';
      }

      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for
        // adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }

        $span_attributes = '';

        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }

        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;
    }

  }

  return $output;
}

/**
 * Implements theme_mark().
 */
function docs_mark($variables) {
  $type = $variables['type'];
  global $user;
  if ($user->uid) {
    if ($type == MARK_NEW) {
      return ' <span class="uk-text-danger">' . t('new') . '</span>';
    }
    elseif ($type == MARK_UPDATED) {
      return ' <span class="uk-text-danger">' . t('updated') . '</span>';
    }
  }
}

/**
 * Implements theme_menu_link() for book toc menu links.
 */
function docs_menu_link__book_toc(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';
  $class_not_array = isset($element['#attributes']['class']) && !is_array($element['#attributes']['class']);

  if ($class_not_array) {
    $classes = explode(' ', $element['#attributes']['class']);
    $element['#attributes']['class'] = $classes;
  }

  if (in_array('active-trail', $element['#attributes']['class'])) {
    $element['#attributes']['class'][] = 'uk-active';
  }
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }

  $nav_header = isset($element['#nav_header']) && $element['#nav_header'];
  if ($nav_header) {
    $output = l($element['#title'], $element['#href']);
  }
  else {
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  }
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . '</li>';
}

/**
 * Implements theme_menu_tree() for book toc menus.
 */
function docs_menu_tree__book_toc($variables) {
  return '<ul class="uk-list uk-list-striped uk-text-center uk-margin-large-top uk-margin-large-bottom">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree() for book toc block menus.
 */
function docs_menu_tree__book_toc__block($variables) {
  return '<ul class="uk-nav uk-nav-side">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_more_link().
 */
function docs_more_link(&$variables) {
  return '<div class="more-link">' . l(t('More'), $variables['url'], array('attributes' => array('title' => $variables['title'], 'class' => array('uk-button uk-button-primary')))) . '</div>';
}

/**
 * Implements theme_table().
 */
function docs_table($variables) {
  $header = $variables['header'];
  $rows = $variables['rows'];
  $attributes = $variables['attributes'];
  $caption = $variables['caption'];
  $colgroups = $variables['colgroups'];
  $sticky = $variables['sticky'];
  $empty = $variables['empty'];

  // Add sticky headers, if applicable.
  if (count($header) && $sticky) {
    drupal_add_js('misc/tableheader.js');
    // Add 'sticky-enabled' class to the table to identify it for JS.
    // This is needed to target tables constructed by this function.
    $attributes['class'][] = 'sticky-enabled';
  }

  $output = '<div class="uk-overflow-container">';
  $output .= '<table' . drupal_attributes($attributes) . '>';

  if (isset($caption)) {
    $output .= '<caption>' . $caption . '</caption>';
  }

  // Format the table columns:
  if (count($colgroups)) {
    foreach ($colgroups as $colgroup) {
      $attributes = array();

      // Check if we're dealing with a simple or complex column.
      if (isset($colgroup['data'])) {
        foreach ($colgroup as $key => $value) {
          if ($key == 'data') {
            $cols = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $cols = $colgroup;
      }

      // Build colgroup.
      if (is_array($cols) && count($cols)) {
        $output .= ' <colgroup' . drupal_attributes($attributes) . '>';

        foreach ($cols as $col) {
          $output .= ' <col' . drupal_attributes($col) . ' />';
        }

        $output .= '</colgroup>';
      }
      else {
        $output .= ' <colgroup' . drupal_attributes($attributes) . ' />';
      }
    }
  }

  // Add the 'empty' row message if available.
  if (!count($rows) && $empty) {
    $header_count = 0;

    foreach ($header as $header_cell) {
      if (is_array($header_cell)) {
        $header_count += isset($header_cell['colspan']) ? $header_cell['colspan'] : 1;
      }
      else {
        $header_count++;
      }
    }

    $rows[] = array(
      array(
        'data' => $empty,
        'colspan' => $header_count,
        'class' => array('empty', 'message'),
      ),
    );
  }

  // Format the table header:
  if (count($header)) {
    $ts = tablesort_init($header);
    // HTML requires that the thead tag has tr tags in it followed by tbody
    // tags. Using ternary operator to check and see if we have any rows.
    $output .= (count($rows) ? '<thead><tr class="uk-text-left">' : '<tr>');

    foreach ($header as $cell) {
      $cell = tablesort_header($cell, $header, $ts);
      $output .= _theme_table_cell($cell, TRUE);
    }

    // Using ternary operator to close the tags based on whether or not there
    // are rows.
    $output .= (count($rows) ? '</tr></thead>' : '</tr>');
  }
  else {
    $ts = array();
  }

  // Format the table rows:
  if (count($rows)) {
    $output .= '<tbody>';
    $flip = array('even' => 'odd', 'odd' => 'even');
    $class = 'even';

    foreach ($rows as $row) {
      // Check if we're dealing with a simple or complex row.
      if (isset($row['data'])) {
        $cells = $row['data'];
        $no_striping = isset($row['no_striping']) ? $row['no_striping'] : FALSE;

        // Set the attributes array and exclude 'data' and 'no_striping'.
        $attributes = $row;
        unset($attributes['data']);
        unset($attributes['no_striping']);
      }
      else {
        $cells = $row;
        $attributes = array();
        $no_striping = FALSE;
      }

      if (count($cells)) {
        // Add odd/even class.
        if (!$no_striping) {
          $class = $flip[$class];
          $attributes['class'][] = $class;
        }

        $attributes['class'][] = 'uk-text-left';
        $attributes['class'][] = 'uk-table-middle';

        // Build row.
        $output .= '<tr' . drupal_attributes($attributes) . '>';
        $i = 0;

        foreach ($cells as $cell) {
          $cell = tablesort_cell($cell, $header, $ts, $i++);
          $output .= _theme_table_cell($cell);
        }
        $output .= '</tr>';
      }
    }
    $output .= '</tbody>';
  }

  $output .= '</table>';
  $output .= '</div>';
  return $output;
}

/**
 * Implements theme_tablesort_indicator().
 */
function docs_tablesort_indicator(&$variables) {
  if ($variables['style'] == "asc") {
    return ' <i class="uk-icon-chevron-down"></i>';
  }
  else {
    return ' <i class="uk-icon-chevron-up"></i>';
  }
}

/**
 * Implements theme_textfield() for the API search field element.
 */
function docs_textfield__api_search(&$variables) {
  $element = $variables['element'];
  element_set_attributes($element, array(
    'id',
    'name',
    'value',
    'size',
    'maxlength',
  ));
  _form_set_class($element, array('form-text'));

  $element['#attributes']['type'] = 'text';
  $element['#attributes']['size'] = '60';

  $extra = '';
  if ($element['#autocomplete_path'] && !empty($element['#autocomplete_input'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#autocomplete_input']['#id'];
    $attributes['value'] = $element['#autocomplete_input']['#url_value'];
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }

  $output = '<div class="uk-form-icon">';
  $output .= '<i id="' . $attributes['id'] . '-icon" class="uk-icon-refresh"></i>';
  $output .= '<input' . drupal_attributes($element['#attributes']) . ' />';
  $output .= '</div>';

  return $output . $extra;
}
