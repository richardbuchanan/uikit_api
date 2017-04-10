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
 * @see \Drupal\Core\Render\RendererInterface
 * @see \Drupal\Core\Render\Renderer
 */

use Drupal\block\Entity\Block;

/**
 * Implements hook_theme_suggestions_HOOK_alter() for block templates.
 */
function uikit_theme_suggestions_block_alter(array &$suggestions, array $variables) {
  $base_plugin_id = $variables['elements']['#base_plugin_id'];
  $id = $variables['elements']['#id'];
  $block = Block::load($id);
  $region = $block->get('region');

  // Add block__REGION to theme suggestions.
  $suggestions[] = 'block__' . $region;

  // Add block__REGION__menu to system menu blocks.
  $system_menu_block = $base_plugin_id == 'system_menu_block';
  if ($system_menu_block) {
    $suggestions[] = 'block__' . $region . '__menu';
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter() for form element templates.
 */
function uikit_theme_suggestions_form_element_alter(array &$suggestions, array $variables) {
  $type = $variables['element']['#type'];

  // Add suggestions with the element type.
  $suggestions[] = 'form_element__' . $type;

  // Add suggestions for checkbox and radios to style advanced form elements.
  $form_advanced = $type == 'checkbox' || $type == 'radio';
  if ($form_advanced) {
    $suggestions[] = 'form_element__' . 'advanced';
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter() for menu templates.
 */
function uikit_theme_suggestions_menu_alter(array &$suggestions, array $variables) {
  $menu_name = $variables['menu_name'];
  $navbar = in_array('menu__navbar', $suggestions);

  if ($navbar) {
    // Add suggestion to navbar menus for themeing separate menus in the navbar.
    $suggestions[] = 'menu__navbar__' . $menu_name;
  }
}
