<?php

/**
 * @file
 * Returns HTML for a form.
 *
 * Available variables:
 * - $variables['element']: An associative array containing the properties of
 *   the element. Properties used: #action, #method, #attributes, #children.
 *
 * @see uikit_preprocess_form()
 * @see theme_form()
 *
 * @ingroup uikit_themeable
 */

$element = $variables['element'];
if (isset($element['#action'])) {
  $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
}
element_set_attributes($element, array('method', 'id'));
if (empty($element['#attributes']['accept-charset'])) {
  $element['#attributes']['accept-charset'] = "UTF-8";
}
// Anonymous DIV to satisfy XHTML compliance.
print '<form' . drupal_attributes($element['#attributes']) . '><div>' . $element['#children'] . '</div></form>';
