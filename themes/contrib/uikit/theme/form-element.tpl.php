<?php

/**
 * @file
 * Returns HTML for a form element.
 *
 * Available variables:
 * - $variables['element']: An associative array containing the properties of
 *   the element. Properties used: #title, #title_display, #description, #id,
 *   #required, #children, #type, #name.
 *
 * @see theme_form_element()
 *
 * @ingroup uikit_themeable
 */

$element = &$variables['element'];
$name = !empty($element['#name']) ? $element['#name'] : FALSE;
$type = !empty($element['#type']) ? $element['#type'] : FALSE;
$prefix = isset($element['#field_prefix']) ? $element['#field_prefix'] : '';
$suffix = isset($element['#field_suffix']) ? $element['#field_suffix'] : '';
$checkbox = $type && $type === 'checkbox';
/* $password = $type && $type === 'password'; */
$radio = $type && $type === 'radio';

// Create an attributes array for the wrapping container.
if (empty($element['#wrapper_attributes'])) {
  $element['#wrapper_attributes'] = array();
}

$wrapper_attributes = &$element['#wrapper_attributes'];

// This function is invoked as theme wrapper, but the rendered form element
// may not necessarily have been processed by form_builder().
$element += array(
  '#title_display' => 'before',
);

// Add wrapper ID for 'item' type.
if ($type && $type === 'item' && !empty($element['#markup']) && !empty($element['#id'])) {
  $wrapper_attributes['id'] = $element['#id'];
}

// Check for errors and set correct error class.
if ((isset($element['#parents']) && form_get_error($element))) {
  $wrapper_attributes['class'][] = 'uk-form-danger';
}

// Add necessary classes to wrapper container.
if ($name) {
  $wrapper_attributes['class'][] = 'form-item-' . drupal_html_class($name);
}
if ($type) {
  $wrapper_attributes['class'][] = 'form-type-' . drupal_html_class($type);
}
if (!empty($element['#attributes']['disabled'])) {
  $wrapper_attributes['class'][] = 'form-disabled';
}
if (!empty($element['#autocomplete_path']) && drupal_valid_path($element['#autocomplete_path'])) {
  $wrapper_attributes['class'][] = 'form-autocomplete';
}

// TODO: Add advanced password options in theme settings.
/*if ($password) {
  $pass_one = $name === 'pass[pass1]';
  $pass_two = $name === 'pass[pass2]';

  if ($pass_one) {
    $class = 'pass-strength-target';
  }
  elseif ($pass_two) {
    $class = 'pass-confirm-target';
  }

  $children = $element['#children'];
  $element['#children'] = '<div class="uk-form-password">';
  $element['#children'] .= $children;

  if (!$pass_one && !$pass_two) {
    $element['#children'] .= '<a href="" class="uk-form-password-toggle"';
    $element['#children'] .= ' data-uk-form-password>Show</a></div>';
  }
  else {
    $element['#children'] .= '</div><div class="' . $class . '"></div>';
  }
}
*/

// Add a space before the labels of checkboxes and radios.
if (($checkbox || $radio) && isset($element['#title'])) {
  $variables['element']['#title'] = ' ' . $element['#title'];
}

// Create a render array for the form element.
$build = array(
  '#theme_wrappers' => array('container__form_element'),
  '#attributes' => $wrapper_attributes,
);

// Render the label for the form element.
$build['label'] = array(
  '#markup' => theme('form_element_label', $variables),
);

// Increase the label weight if it should be displayed after the element.
if ($element['#title_display'] === 'after') {
  $build['label']['#weight'] = 10;
}

// Checkboxes and radios render the input element inside the label. If the
// element is neither of those, then the input element must be rendered here.
if (!$checkbox && !$radio) {

  if ((!empty($prefix) || !empty($suffix))) {
    if (!empty($element['#field_prefix'])) {
      $prefix = '<span class="form-item-prefix">' . $prefix . '</span>';
    }
    if (!empty($element['#field_suffix'])) {
      $suffix = '<span class="form-item-suffix">' . $suffix . '</span>';
    }

    // Add a wrapping container around the elements.
    $form_row_attributes['class'][] = 'uk-form-row';
    $prefix = '<div' . drupal_attributes($form_row_attributes) . '>' . $prefix;
    $suffix .= '</div>';
  }

  // Build the form element.
  $build['element'] = array(
    '#markup' => $element['#children'],
    '#prefix' => !empty($prefix) ? $prefix : NULL,
    '#suffix' => !empty($suffix) ? $suffix : NULL,
  );
}

// Construct the element's description markup.
if (!empty($element['#description'])) {
  $build['description'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('uk-form-help-block', 'uk-text-muted'),
    ),
    '#weight' => 20,
    0 => array('#markup' => $element['#description']),
  );
}

// Print the form element build array.
print drupal_render($build);
