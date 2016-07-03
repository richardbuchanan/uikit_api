<?php

/**
 * @file
 * Returns HTML for a button form element.
 *
 * Available variables:
 * - $variables['element']: An associative array containing the properties of
 *   the element. Properties used: #attributes, #button_type, #name, #value.
 *
 * @see uikit_preprocess_button()
 * @see theme_button()
 *
 * @ingroup uikit_themeable
 */

$element = $variables['element'];
$element['#attributes']['type'] = 'submit';
element_set_attributes($element, array('id', 'name', 'value'));
$value = $element['#attributes']['value'];

$element['#attributes']['class'][] = 'form-' . $element['#button_type'];
if (!empty($element['#attributes']['disabled'])) {
  $element['#attributes']['class'][] = 'form-button-disabled';
}

print '<button' . drupal_attributes($element['#attributes']) . '>' . $value . '</button>';
