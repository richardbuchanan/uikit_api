<?php

/**
 * @file
 * Returns HTML for a form.
 */

$element = $variables['element'];

if (isset($element['#action'])) {
  $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
}

element_set_attributes($element, array('method', 'id'));

if (empty($element['#attributes']['accept-charset'])) {
  $element['#attributes']['accept-charset'] = "UTF-8";
}

$element['#attributes']['class'] = array('uk-form', 'uk-form-stacked', 'uk-margin-bottom');
// Anonymous DIV to satisfy XHTML compliance.
print '<form' . drupal_attributes($element['#attributes']) . '><div>' . $element['#children'] . '</div></form>';
