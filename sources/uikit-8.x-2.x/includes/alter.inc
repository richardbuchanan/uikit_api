<?php

/**
 * @file
 * Modify structured content arrays.
 *
 * These hooks are called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * content structure has been built.
 *
 * If the theme wishes to act on the rendered HTML of the content rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_HOOK().
 *
 * @see drupal_render()
 * @see theme()
 */

use \Drupal\block\Entity\Block;

/**
 * Implements hook_theme_suggestions_HOOK_alter() for block templates.
 */
function uikit_theme_suggestions_block_alter(array &$suggestions, array $variables) {
  $base_plugin_id = $variables['elements']['#base_plugin_id'];
  $system_menu_block = $base_plugin_id == 'system_menu_block';

  if ($system_menu_block) {
    $id = $variables['elements']['#id'];
    $block = Block::load($id);
    $region = $block->get('region');
    $suggestions[] = 'block__' . $region . '__menu';
  }
}
