<?php

/**
 * @file
 * Returns HTML for a single local task link.
 *
 * Available variables:
 * $variables['element']: A render element containing:
 *   - #link: A menu link array with 'title', 'href', and 'localized_options'
 *     keys.
 *   - #active: A boolean indicating whether the local task is active.
 *
 * @see theme_menu_local_task()
 *
 * @ingroup uikit_themeable
 */

$link = $variables['element']['#link'];
$link_text = $link['title'];

if (!empty($variables['element']['#active'])) {
  // Add text to indicate active tab for non-visual users.
  $active = '<span class="uk-hidden">' . t('(active tab)') . '</span>';

  // If the link does not contain HTML already, check_plain() it now.
  // After we set 'html'=TRUE the link will not be sanitized by l().
  if (empty($link['localized_options']['html'])) {
    $link['title'] = check_plain($link['title']);
  }
  $link['localized_options']['html'] = TRUE;
  $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
}

print '<li' . (!empty($variables['element']['#active']) ? ' class="uk-active"' : '') . '>' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n";
