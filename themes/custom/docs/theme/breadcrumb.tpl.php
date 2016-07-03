<?php

/**
 * @file
 * Returns HTML for a breadcrumb trail.
 */

$breadcrumb = $variables['breadcrumb'];
$path = explode('/', current_path());

if (!empty($breadcrumb)) {
  // Provide a navigational heading to give context for breadcrumb links to
  // screen-reader users. Make the heading invisible with .uk-hidden.
  $output = '<h2 class="uk-hidden">' . t('You are here') . '</h2>';

  $output .= '<ul class="uk-breadcrumb uk-margin-small-bottom">';

  foreach ($breadcrumb as $crumb) {
    $output .= '<li>' . $crumb . '</li>';
  }

  $output .= '</ul>';
  print $output;
}
