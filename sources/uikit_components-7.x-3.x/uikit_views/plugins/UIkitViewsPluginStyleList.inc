<?php

/**
 * @file
 * Contains the list style plugin.
 */

/**
 * Style plugin to render each item in UIkit list.
 *
 * @ingroup views_style_plugins
 */
class UIkitViewsPluginStyleList extends views_plugin_style {

  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['wrapper_class'] = array('default' => '');
    $options['modifier'] = array('default' => 'default');
    $options['large_modifier'] = array('default' => 0);

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $args = array(
      '@href' => 'https://getuikit.com/docs/list',
      '@title' => 'List component - UIkit documentation',
    );

    $form['wrapper_class'] = array(
      '#title' => t('Wrapper class'),
      '#description' => t('The class to provide on the wrapper, outside the list.'),
      '#type' => 'textfield',
      '#size' => '30',
      '#default_value' => $this->options['wrapper_class'],
    );
    $form['modifier'] = array(
      '#title' => t('List modifider'),
      '#description' => t('The modifier to apply to the list. See <a href="@href" target="_blank" title="@title">List component</a> to view examples of each list modifier.', $args),
      '#type' => 'select',
      '#default_value' => $this->options['modifier'],
      '#options' => array(
        'default' => t('Default list'),
        'uk-list-bullet' => t('Bullet list'),
        'uk-list-divider' => t('Divided list'),
        'uk-list-striped' => t('Striped list'),
      ),
    );
    $form['large_modifier'] = array(
      '#title' => t('Large modifier'),
      '#description' => t('Increase the spacing between list items.'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['large_modifier'],
    );
  }

}
