<?php

/**
 * @file
 * Returns HTML for a single local action link.
 *
 * Available variables:
 * $variables['element']: A render element containing:
 *   - #link: A menu link array with 'title', 'href', and 'localized_options'
 *     keys.
 *
 * @see theme_menu_local_action()
 *
 * @ingroup uikit_themeable
 */

$link = $variables['element']['#link'];

$output = '<li class="uk-active">';
if (isset($link['href'])) {
  $output .= l($link['title'], $link['href'], isset($link['localized_options']) ? $link['localized_options'] : array());
}
elseif (!empty($link['localized_options']['html'])) {
  $output .= $link['title'];
}
else {
  $output .= check_plain($link['title']);
}
$output .= "</li>\n";

print $output;
