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
    $options['class'] = array('default' => '');

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $args = array(
      '@href' => 'https://getuikit.com/v2/docs/list.html',
      '@title' => 'List component - UIkit documentation',
    );

    $form['wrapper_class'] = array(
      '#title' => t('Wrapper class'),
      '#description' => t('The class to provide on the wrapper, outside the list.'),
      '#type' => 'textfield',
      '#size' => '30',
      '#default_value' => $this->options['wrapper_class'],
    );
    $form['class'] = array(
      '#title' => t('List class'),
      '#description' => t('The modifier to apply to the list. See <a href="@href" target="_blank" title="@title">List component</a> to view examples of each list modifier.', $args),
      '#type' => 'select',
      '#default_value' => $this->options['class'],
      '#options' => array(
        'default' => t('Default'),
        'uk-list-line' => t('List line'),
        'uk-list-striped' => t('List striped'),
        'uk-list-space' => t('List space'),
      ),
    );
  }

}
