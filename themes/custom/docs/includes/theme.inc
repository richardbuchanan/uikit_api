<?php

/**
 * @file
 * The UIkit theme system, which controls the output of the UIkit theme.
 *
 * The theme system allows for nearly all output of the Drupal system to be
 * customized by UIkit themes.
 *
 * @ingroup uikit_themeable
 */

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
 * Implements theme_item_list().
 */
function docs_item_list(&$variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];

  // Only output the list container and title, if there are any list items.
  // Check to see whether the block title exists before adding a header.
  // Empty headers are not semantic and present accessibility challenges.
  $output = '<div class="item-list">';
  if (isset($title) && $title !== '') {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $attributes['class'] = array('uk-list', 'uk-list-line');
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

  $output .= '</div>';
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
 * Implements theme_more_link().
 */
function docs_more_link(&$variables) {
  return '<div class="more-link">' . l(t('More'), $variables['url'], array('attributes' => array('title' => $variables['title'], 'class' => array('uk-button uk-button-primary')))) . '</div>';
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
