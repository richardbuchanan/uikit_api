<?php

/**
 * @file
 * Returns HTML for a form element label and required marker.
 */

$element = $variables['element'];
// This is also used in the installer, pre-database setup.
$t = get_t();

// If title and required marker are both empty, output no label.
if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
  return '';
}

// If the element is required, a required marker is appended to the label.
$required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

$title = filter_xss_admin($element['#title']);

$attributes = array();
if ($element['#title_display'] != 'after') {
  $attributes['class'] = array('uk-form-label');
}
// Show label only to screen readers to avoid disruption in visual flows.
elseif ($element['#title_display'] == 'invisible') {
  $attributes['class'][] = 'element-invisible';
}

if (!empty($element['#id'])) {
  $attributes['for'] = $element['#id'];
}

// The leading whitespace helps visually separate fields from inline labels.
print ' <label' . drupal_attributes($attributes) . '>' . $t('!title !required', array('!title' => $title, '!required' => $required)) . "</label>\n";
