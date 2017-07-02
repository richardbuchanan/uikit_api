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
 * Implements hook_form_FORM_ID_alter() for the search form.
 */
function uikit_form_search_form_alter(&$form, \Drupal\Core\Form\FormStateInterface $form_state, $form_id) {
  // Drupal core does not place the submit buttons or the help link in container
  // elements. First copy, then remove these elements.
  $submit = $form['basic']['submit'];
  $help_link = $form['help_link'];
  unset($form['basic']['submit']);

  // Create the new containers.
  $form['basic']['actions'] = [
    '#type' => 'actions',
  ];
  $form['help_link'] = [
    '#type' => 'container',
  ];

  // Place the submit buttons and help link inside their respective containers.
  $form['basic']['actions']['submit'] = $submit;
  $form['help_link']['help'] = $help_link;

  // Now do the same for the advanced search form, if set.
  if (isset($form['advanced'])) {
    $advanced_submit = $form['advanced']['submit'];
    unset($form['advanced']['submit']);

    // Remove the prefix and suffix from the advanced submit element.
    unset($advanced_submit['#prefix']);
    unset($advanced_submit['#suffix']);

    $form['advanced']['actions'] = [
      '#type' => 'actions',
    ];

    $form['advanced']['actions']['submit'] = $advanced_submit;
  }
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

  // Add block__REGION__menu to system menu blocks.
  $system_menu_block = $base_plugin_id == 'system_menu_block';
  if ($system_menu_block) {
    $suggestions[] = 'block__' . $region . '__menu';
  }

  // Add block__REGION__branding to system branding blocks.
  $system_branding_block = $base_plugin_id == 'system_branding_block';
  if ($system_branding_block) {
    $suggestions[] = 'block__' . $region . '__branding';
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
