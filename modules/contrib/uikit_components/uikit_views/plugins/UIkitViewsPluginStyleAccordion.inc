<?php

/**
 * @file
 * Contains the accordion style plugin.
 */

/**
 * Style plugin to render each item in UIkit accordion.
 *
 * @ingroup views_style_plugins
 */
class UIkitViewsPluginStyleAccordion extends views_plugin_style {

  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['title_field'] = array('default' => NULL);
    $options['showfirst'] = array('default' => TRUE);
    $options['collapse'] = array('default' => TRUE);
    $options['animate'] = array('default' => TRUE);
    $options['easing'] = array('default' => 'swing');
    $options['duration'] = array('default' => '300');
    $options['toggle'] = array('default' => '.uk-accordion-title');
    $options['containers'] = array('default' => '.uk-accordion-content');
    $options['clsactive'] = array('default' => 'uk-active');

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    if (isset($form['grouping'])) {
      $title_field_options = array();

      foreach (element_children($form['grouping']) as $key => $value) {
        if (!empty($form['grouping'][$key]['field']['#options']) && is_array($form['grouping'][$key]['field']['#options'])) {
          $title_field_options = array_merge($title_field_options, $form['grouping'][$key]['field']['#options']);
        }
      }

      $form['title_field'] = array(
        '#type' => 'select',
        '#title' => t('Title field'),
        '#options' => $title_field_options,
        '#required' => TRUE,
        '#default_value' => $this->options['title_field'],
        '#description' => t('Select the field to use as the accordian title to create a toggle for the accordion items.'),
      );
      $form['showfirst'] = array(
        '#type' => 'checkbox',
        '#title' => t('Show first item on init'),
        '#default_value' => $this->options['showfirst'],
      );
      $form['collapse'] = array(
        '#type' => 'checkbox',
        '#title' => t('Allow multiple open items'),
        '#default_value' => $this->options['collapse'],
      );
      $form['animate'] = array(
        '#type' => 'checkbox',
        '#title' => t('Animate toggle'),
        '#default_value' => $this->options['animate'],
      );
      $form['easing'] = array(
        '#type' => 'textfield',
        '#title' => t('Animation function'),
        '#default_value' => $this->options['easing'],
        '#description' => t('<strong>Note:</strong> The only easing implementations in the jQuery library are the default, called <em class="placeholder">swing</em>, and one that progresses at a constant pace, called <em class="placeholder">linear</em>. More easing functions are available with the use of plug-ins, most notably the <a href="@jqueryUI" target="_blank">jQuery UI suite</a>.', array('@jqueryUI' => 'http://jqueryui.com/')),
        '#required' => TRUE,
      );
      $form['duration'] = array(
        '#type' => 'number',
        '#title' => t('Animation duration'),
        '#default_value' => $this->options['duration'],
        '#required' => TRUE,
      );
      $form['toggle'] = array(
        '#type' => 'textfield',
        '#title' => t('Css selector for toggles'),
        '#default_value' => $this->options['toggle'],
        '#required' => TRUE,
      );
      $form['containers'] = array(
        '#type' => 'textfield',
        '#title' => t('Css selector for content containers'),
        '#default_value' => $this->options['containers'],
        '#required' => TRUE,
      );
      $form['clsactive'] = array(
        '#type' => 'textfield',
        '#title' => t('Class to add when an item is active'),
        '#default_value' => $this->options['clsactive'],
        '#required' => TRUE,
      );
    }
  }

}
