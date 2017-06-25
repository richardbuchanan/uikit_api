<?php

/**
 * @file
 * Contains the UIkit Views grid style plugin.
 */

/**
 * Style plugin to render each item in a UIkit grid component.
 *
 * @ingroup views_style_plugins
 */
class UIkitViewsPluginStyleGrid extends views_plugin_style {

  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['row_class'] = array('default' => '');

    $options['width_@s'] = array('default' => 'uk-child-width-1-1@s');
    $options['width_@m'] = array('default' => 'uk-child-width-1-2@m');
    $options['width_@l'] = array('default' => 'uk-child-width-1-3@l');
    $options['width_@xl'] = array('default' => 'uk-child-width-1-4@xl');
    $options['grid_divider'] = array('default' => FALSE);
    $options['grid_gutter'] = array('default' => 'default');

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $args = array(
      '@href' => 'https://getuikit.com/docs/grid#child-width',
      '@title' => 'Grid component - UIkit documentation',
    );

    $breakpoints = array(
      '@s' => t('Affects device widths of 640px and higher.'),
      '@m' => t('Affects device widths of 960px and higher.'),
      '@l' => t('Affects device widths of 1200px and higher.'),
      '@xl' => t('Affects device widths of 1600px and higher.'),
    );

    $form['column_widths'] = array(
      '#type' => 'fieldset',
      '#title' => t('Grid columns'),
      '#description' => t("To create a grid whose child elements' widths are evenly split, we apply one class to the grid for each breakpoint. Each item in the grid is then automatically applied a width based on the number of columns selected for each breakpoint. See <a href='@href' target='_blank' title='@title'>Grid component</a> for more details.", $args),
    );

    foreach (['@s', '@m', '@l', '@xl'] as $size) {
      $form['column_widths']["width_${size}"] = array(
        '#type' => 'select',
        '#title' => t("uk-child-width-*${size}"),
        '#required' => TRUE,
        '#default_value' => $this->options["width_${size}"],
        '#options' => array(
          "uk-child-width-1-1${size}" => 1,
          "uk-child-width-1-2${size}" => 2,
          "uk-child-width-1-3${size}" => 3,
          "uk-child-width-1-4${size}" => 4,
          "uk-child-width-1-5${size}" => 5,
          "uk-child-width-1-6${size}" => 6,
          "uk-child-width-1-10${size}" => 10,
        ),
        '#description' => $breakpoints[$size],
      );
    }

    $form['grid_divider'] = array(
      '#type' => 'checkbox',
      '#title' => t('Grid divider'),
      '#default_value' => $this->options['grid_divider'],
      '#description' => t('Separate grid cells with lines.'),
    );
    $form['grid_gutter'] = array(
      '#type' => 'select',
      '#title' => t('Grid gutter'),
      '#required' => TRUE,
      '#default_value' => $this->options['grid_gutter'],
      '#options' => array(
        'default' => t('Default gutter'),
        'uk-grid-small' => t('Small gutter'),
        'uk-grid-medium' => t('Medium gutter'),
        'uk-grid-large' => t('Large gutter'),
        'uk-grid-collapse' => t('Collapse gutter'),
      ),
      '#description' => t('By default, the grid gutter is wider on large screens.<br /><strong>Note</strong>: <em class="placeholder">Grid collapse</em> removes the grid gutter.'),
    );
  }

}
