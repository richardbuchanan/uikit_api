<?php

/**
 * @file
 * Returns HTML for a textfield form element.
 *
 * Available variables:
 * - $variables['element']: An associative array containing the properties of
 *   the element. Properties used: #title, #value, #description, #size,
 *   #maxlength, #required, #attributes, #autocomplete_path.
 *
 * @see theme_textfield()
 *
 * @ingroup uikit_themeable
 */

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
$element['#attributes']['size'] = '25';

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

$output = '<input' . drupal_attributes($element['#attributes']) . ' />';

print $output . $extra;
