<?php

/**
 * @file
 * Returns HTML for a fieldset form element and its children.
 *
 * Available variables:
 * - $variables['element']: An associative array containing the properties of
 *   the element. Properties used: #attributes, #children, #collapsed,
 *   #collapsible, #description, #id, #title, #value.
 *
 * @see uikit_preprocess_fieldset()
 * @see theme_fieldset()
 *
 * @ingroup uikit_themeable
 */

$element = $variables['element'];
element_set_attributes($element, array('id'));
_form_set_class($element, array('form-wrapper'));

// Grouped fieldsets are fieldsets grouped together, such as vertical tabs.
$group_fieldset = isset($element['#group_fieldset']) && $element['#group_fieldset'];

$output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';

if (!empty($element['#title'])) {
  $output .= '<legend><span class="fieldset-legend">' . $element['#title'] . '</span></legend>';
}

$output .= '<div class="fieldset-wrapper">';

if (!empty($element['#description'])) {
  $output .= '<div class="uk-form-help-block"><p>' . $element['#description'] . '</p></div>';
}

$output .= $element['#children'];

if (isset($element['#value'])) {
  $output .= $element['#value'];
}

$output .= '</div>';
$output .= "</fieldset>\n";

print $output;
