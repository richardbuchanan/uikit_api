<?php

/**
 * @file
 * Returns HTML for the content of an administrative block.
 *
 * Available variables:
 * - $variables['content']: An array containing information about the block.
 *   Each element of the array represents an administrative menu item, and must
 *   at least contain the keys 'title', 'href', and 'localized_options', which
 *   are passed to l(). A 'description' key may also be provided.
 *
 * @see theme_admin_block_content()
 *
 * @ingroup uikit_themeable
 */

$content = $variables['content'];
$output = '';

if (!empty($content)) {
  $class = 'uk-description-list-line';
  if ($compact = system_admin_compact_mode()) {
    $class .= ' compact';
  }
  $output .= '<dl class="' . $class . '">';
  foreach ($content as $item) {
    $output .= '<dt>' . l($item['title'], $item['href'], $item['localized_options']) . '</dt>';
    if (!$compact && isset($item['description'])) {
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
  }
  $output .= '</dl>';
}
print $output;
