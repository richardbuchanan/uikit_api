<?php

/**
 * @file
 * Returns HTML for status and/or error messages, grouped by type.
 *
 * Available variables:
 * - $variables['display']: (optional) Set to 'status' or 'error' to display
 *   only messages of that type.
 *
 * @see theme_status_messages()
 *
 * @ingroup uikit_themeable
 */

$display = $variables['display'];
$output = '';

$status_heading = array(
  'status' => t('Status message'),
  'error' => t('Error message'),
  'warning' => t('Warning message'),
);
foreach (drupal_get_messages($display) as $type => $messages) {
  $class = 'uk-alert-';

  switch ($type) {
    case 'status':
      $class .= 'success';
      break;

    case 'error':
      $class .= 'danger';
      break;

    case 'warning':
      $class .= 'warning';
      break;
  }

  $output .= "<div class=\"uk-alert $class\" data-uk-alert>\n";
  $output .= '<a class="uk-alert-close uk-close"></a>';

  if (!empty($status_heading[$type])) {
    $output .= '<h2 class="uk-hidden">' . $status_heading[$type] . "</h2>\n";
  }

  if (count($messages) > 1) {
    $output .= " <ul>\n";
    foreach ($messages as $message) {
      $output .= '  <li>' . $message . "</li>\n";
    }
    $output .= " </ul>\n";
  }
  else {
    $output .= reset($messages);
  }

  $output .= "</div>\n";
}

print $output;
