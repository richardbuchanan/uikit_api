<?php

/**
 * @file
 * Returns HTML for a tags field.
 *
 * Available variables:
 * - $variables['label_hidden']: A boolean indicating to show or hide the field
 *   label.
 * - $variables['title_attributes']: A string containing the attributes for the
 *   title.
 * - $variables['label']: The label for the field.
 * - $variables['content_attributes']: A string containing the attributes for
 *   the content's div.
 * - $variables['items']: An array of field items.
 * - $variables['item_attributes']: An array of attributes for each item.
 * - $variables['classes']: A string containing the classes for the wrapping
 *   div.
 * - $variables['attributes']: A string containing the attributes for the
 *   wrapping div.
 *
 * @see template_preprocess_field()
 * @see template_process_field()
 * @see uikit_preprocess_field()
 * @see field.tpl.php
 *
 * @ingroup uikit_themeable
 */

$output = '';

// Render the label, if it's not hidden.
if (!$variables['label_hidden']) {
  $output .= '<div class="uk-h4"' . $variables['title_attributes'] . '>' . $variables['label'] . '</div>';
}

// Render the items.
$output .= '<ul class="uk-subnav"' . $variables['content_attributes'] . '>';
foreach ($variables['items'] as $delta => $item) {
  $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
  $output .= '<li class="' . $classes . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</li>';
}
$output .= '</ul>';

// Render the top-level DIV.
$output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';

print $output;
