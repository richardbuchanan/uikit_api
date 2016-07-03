<?php

/**
 * @file
 * Returns HTML for primary and secondary local tasks.
 *
 * Available variables:
 * - $variables['primary']: (optional) An array of local tasks (tabs).
 * - $variables['secondary']: (optional) An array of local tasks (tabs).
 *
 * @see menu_local_tasks()
 * @see uikit_preprocess_menu_local_tasks()
 * @see uikit_process_menu_local_tasks()
 * @see theme_menu_local_tasks()
 *
 * @ingroup uikit_themeable
 */

$output = '';

if (!empty($variables['primary'])) {
  $variables['primary']['#prefix'] = '<h2 class="uk-hidden">' . t('Primary tabs') . '</h2>';
  $variables['primary']['#prefix'] .= "<ul$primary_attributes>";
  $variables['primary']['#suffix'] = '</ul>';
  $output .= drupal_render($variables['primary']);
}
if (!empty($variables['secondary'])) {
  $variables['secondary']['#prefix'] = '<h2 class="uk-hidden">' . t('Secondary tabs') . '</h2>';
  $variables['secondary']['#prefix'] .= "<ul$secondary_attributes>";
  $variables['secondary']['#suffix'] = '</ul>';
  $output .= drupal_render($variables['secondary']);
}

print $output;
