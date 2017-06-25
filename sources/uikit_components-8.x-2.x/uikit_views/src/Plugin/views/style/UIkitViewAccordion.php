<?php

namespace Drupal\uikit_views\Plugin\views\style;

use Drupal\Core\Form\FormStateInterface;
use Drupal\views\Plugin\views\style\StylePluginBase;

/**
 * Style plugin to render each item in a UIkit Accordion component.
 *
 * @ingroup views_style_plugins
 *
 * @ViewsStyle(
 *   id = "uikit_view_accordion",
 *   title = @Translation("UIkit Accordion"),
 *   help = @Translation("Displays rows in a UIkit Accordion component"),
 *   theme = "uikit_view_accordion",
 *   display_types = {"normal"}
 * )
 */
class UIkitViewAccordion extends StylePluginBase {

  /**
   * Does the style plugin for itself support to add fields to it's output.
   *
   * @var bool
   */
  protected $usesFields = TRUE;

  /**
   * Does the style plugin allows to use style plugins.
   *
   * @var bool
   */
  protected $usesRowPlugin = TRUE;

  /**
   * {@inheritdoc}
   */
  protected function defineOptions() {
    $options = parent::defineOptions();

    $options['title_field'] = ['default' => NULL];
    $options['showfirst'] = ['default' => TRUE];
    $options['collapse'] = ['default' => TRUE];
    $options['animate'] = ['default' => TRUE];
    $options['easing'] = ['default' => 'swing'];
    $options['duration'] = ['default' => '300'];
    $options['toggle'] = ['default' => '.uk-accordion-title'];
    $options['containers'] = ['default' => '.uk-accordion-content'];
    $options['clsactive'] = ['default' => 'uk-active'];

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function buildOptionsForm(&$form, FormStateInterface $form_state) {
    parent::buildOptionsForm($form, $form_state);

    if (isset($form['grouping'])) {
      unset($form['grouping']);

      $form['title_field'] = [
        '#type' => 'select',
        '#title' => $this->t('Title field'),
        '#options' => $this->displayHandler->getFieldLabels(TRUE),
        '#required' => TRUE,
        '#default_value' => $this->options['title_field'],
        '#description' => $this->t('Select the field to use as the accordian title to create a toggle for the accordion items.'),
      ];
      $form['accordion_options'] = [
        '#type' => 'details',
        '#title' => $this->t('Accordion options'),
        '#open' => TRUE,
      ];
      $form['showfirst'] = [
        '#type' => 'checkbox',
        '#title' => $this->t('Show first item on init'),
        '#default_value' => $this->options['showfirst'],
        '#fieldset' => 'accordion_options',
      ];
      $form['collapse'] = [
        '#type' => 'checkbox',
        '#title' => $this->t('Allow multiple open items'),
        '#default_value' => $this->options['collapse'],
        '#fieldset' => 'accordion_options',
      ];
      $form['animate'] = [
        '#type' => 'checkbox',
        '#title' => $this->t('Animate toggle'),
        '#default_value' => $this->options['animate'],
        '#fieldset' => 'accordion_options',
      ];
      $form['easing'] = [
        '#type' => 'textfield',
        '#title' => $this->t('Animation function'),
        '#default_value' => $this->options['easing'],
        '#description' => $this->t('<strong>Note:</strong> The only easing implementations in the jQuery library are the default, called <em class="placeholder">swing</em>, and one that progresses at a constant pace, called <em class="placeholder">linear</em>. More easing functions are available with the use of plug-ins, most notably the <a href=":jqueryUI" target="_blank">jQuery UI suite</a>.', [':jqueryUI' => 'http://jqueryui.com/']),
        '#fieldset' => 'accordion_options',
        '#required' => TRUE,
      ];
      $form['duration'] = [
        '#type' => 'number',
        '#title' => $this->t('Animation duration'),
        '#default_value' => $this->options['duration'],
        '#fieldset' => 'accordion_options',
        '#required' => TRUE,
      ];
      $form['toggle'] = [
        '#type' => 'textfield',
        '#title' => $this->t('Css selector for toggles'),
        '#default_value' => $this->options['toggle'],
        '#fieldset' => 'accordion_options',
        '#required' => TRUE,
      ];
      $form['containers'] = [
        '#type' => 'textfield',
        '#title' => $this->t('Css selector for content containers'),
        '#default_value' => $this->options['containers'],
        '#fieldset' => 'accordion_options',
        '#required' => TRUE,
      ];
      $form['clsactive'] = [
        '#type' => 'textfield',
        '#title' => $this->t('Class to add when an item is active'),
        '#default_value' => $this->options['clsactive'],
        '#fieldset' => 'accordion_options',
        '#required' => TRUE,
      ];
    }
  }

}
