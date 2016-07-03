<?php

/**
 * @file
 * Returns HTML for a list of available node types for node creation.
 *
 * Available variables:
 * - $variables['content']: An array of content types.
 *
 * @see theme_node_add_list()
 *
 * @ingroup uikit_themeable
 */

$content = $variables['content'];
$output = '';

if ($content) {
  $output = '<dl class="uk-description-list-line">';
  foreach ($content as $item) {
    $output .= '<dt>' . l($item['title'], $item['href'], $item['localized_options']) . '</dt>';
    $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
  }
  $output .= '</dl>';
}
else {
  $output = '<p>' . t('You have not created any content types yet. Go to the <a href="@create-content">content type creation page</a> to add a new content type.', array('@create-content' => url('admin/structure/types/add'))) . '</p>';
}
print $output;
