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

    $options['column_widths']['width_small'] = array('default' => 'uk-grid-width-small-1-1');
    $options['column_widths']['width_medium'] = array('default' => 'uk-grid-width-medium-1-2');
    $options['column_widths']['width_large'] = array('default' => 'uk-grid-width-large-1-3');
    $options['column_widths']['width_xlarge'] = array('default' => 'uk-grid-width-xlarge-1-4');
    $options['grid_divider'] = array('default' => TRUE);
    $options['grid_gutter'] = array('default' => 'default');

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $args = array(
      '@href' => 'https://getuikit.com/v2/docs/grid.html#even-grid-columns',
      '@title' => 'Grid component - UIkit documentation',
    );

    $breakpoints = array(
      'small' => t('Affects device widths of 480px and higher.'),
      'medium' => t('Affects device widths of 768px and higher.'),
      'large' => t('Affects device widths of 960px and higher.'),
      'xlarge' => t('Affects device widths of 1220px and higher.'),
    );

    $form['column_widths'] = array(
      '#type' => 'fieldset',
      '#title' => t('Grid columns'),
      '#description' => t("To create a grid whose child elements' widths are evenly split, we apply one class to the grid for each breakpoint. Each item in the grid is then automatically applied a width based on the number of columns selected for each breakpoint. See <a href='@href' target='_blank' title='@title'>Grid component</a> for more details.", $args),
    );

    foreach (['small', 'medium', 'large', 'xlarge'] as $size) {
      $form['column_widths']["width_${size}"] = array(
        '#type' => 'select',
        '#title' => t("uk-grid-width-${size}-*"),
        '#required' => TRUE,
        '#default_value' => $this->options['column_widths']["width_${size}"],
        '#options' => array(
          "uk-grid-width-${size}-1-1" => 1,
          "uk-grid-width-${size}-1-2" => 2,
          "uk-grid-width-${size}-1-3" => 3,
          "uk-grid-width-${size}-1-4" => 4,
          "uk-grid-width-${size}-1-5" => 5,
          "uk-grid-width-${size}-1-6" => 6,
          "uk-grid-width-${size}-1-10" => 10,
        ),
        '#description' => $breakpoints[$size],
      );
    }

    $form['grid_divider'] = array(
      '#type' => 'checkbox',
      '#title' => t('Grid divider'),
      '#default_value' => $this->options['grid_divider'],
      '#description' => t('Apply a horizontal border to each row in the grid, except the first row.'),
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
      '#description' => t('Grids automatically create a horizontal gutter between columns and a vertical one between two succeeding grids. By default, the grid gutter is wider on large screens.<br /><strong>Note</strong>: <em class="placeholder">Grid collapse</em> removes the grid gutter.'),
    );
  }

}
