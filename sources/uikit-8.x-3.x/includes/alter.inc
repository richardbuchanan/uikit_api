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
use Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_form_FORM_ID_alter() for Drupal\search\Form\SearchPageForm.
 */
function uikit_form_search_form_alter(&$form, FormStateInterface $form_state, $form_id) {
  // SearchPageForm assigns a class to the help link as a string instead of an
  // an array. Let's fix that first.
  if (!is_array($form['help_link']['#options']['attributes']['class'])) {
    $help_link_classes = explode(' ', $form['help_link']['#options']['attributes']['class']);
    $form['help_link']['#options']['attributes']['class'] = $help_link_classes;
  }

  // Now add some classes to the help link for better spacing below the search
  // input.
  $form['help_link']['#options']['attributes']['class'][] = 'uk-display-inline-block';
  $form['help_link']['#options']['attributes']['class'][] = 'uk-margin-small-top';
}

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

  // Add block__REGION__menu to system menu blocks and block__navbar__item to
  // non-system menu and non-system branding blocks.
  $system_branding_block = $base_plugin_id == 'system_branding_block';
  $system_menu_block = $base_plugin_id == 'system_menu_block';
  if ($system_menu_block) {
    $suggestions[] = 'block__' . $region . '__menu';
  }
  elseif ($region == 'navbar' && !$system_branding_block) {
    $suggestions[] = 'block__navbar__item';
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter() for container templates.
 */
function uikit_theme_suggestions_container_alter(array &$suggestions, array $variables) {
  if (isset($variables['element']['administration_menu'])) {
    $suggestions[] = 'container__admin__toolbar';
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
