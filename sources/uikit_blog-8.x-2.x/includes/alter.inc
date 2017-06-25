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

use Drupal\Core\Url;

/**
 * Implements hook_form_FORM_ID_alter() for search_form().
 */
function uikit_blog_form_search_form_alter(&$form, \Drupal\Core\Form\FormStateInterface $form_state, $form_id) {
  $form['help_link']['#options']['attributes']['class'] = [
    'search-help-link',
    'uk-display-block',
    'uk-form-row',
  ];
  unset($form['basic']['#attributes']['class']);
  $form['basic']['submit']['#attributes']['class'][] = 'uk-form-row';
}

/**
 * Implements hook_form_FORM_ID_alter() for search_block_form().
 */
function uikit_blog_form_search_block_form_alter(&$form, \Drupal\Core\Form\FormStateInterface $form_state, $form_id) {
  $form['actions']['submit']['#theme_wrappers'][] = 'input__search_button';
}

/**
 * Implements hook_form_FORM_ID_alter() for user_login_form().
 */
function uikit_blog_form_user_login_form_alter(&$form, \Drupal\Core\Form\FormStateInterface $form_state, $form_id) {
  $name_placeholder = t($form['name']['#title']->getUntranslatedString());
  unset($form['name']['#title']);
  unset($form['name']['#description']);
  $form['name']['#attributes']['class'][] = 'uk-width-1-1';
  $form['name']['#attributes']['class'][] = 'uk-form-large';
  $form['name']['#attributes']['placeholder'] = $name_placeholder;
  $form['name']['#weight'] = 1;

  $password_placeholder = t($form['pass']['#title']->getUntranslatedString());
  unset($form['pass']['#title']);
  unset($form['pass']['#description']);
  $form['pass']['#attributes']['class'][] = 'uk-width-1-1';
  $form['pass']['#attributes']['class'][] = 'uk-form-large';
  $form['pass']['#attributes']['placeholder'] = $password_placeholder;
  $form['pass']['#weight'] = 2;

  $form['user_links'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => 'uk-text-small',
    ),
    '#weight' => 3,
  );

  $user_can_register = \Drupal::config('user.settings')->get('register');
  switch ($user_can_register) {
    case 'visitors':
    case 'visitors_admin_approval':
    $form['user_links']['register'] = [
      '#type' => 'link',
      '#title' => t('Create new account'),
      '#url' => Url::fromRoute('user.register'),
      '#attributes' => [
        'class' => [
          'uk-float-left',
          'uk-link',
          'uk-link-muted',
        ],
      ],
    ];
      break;
  }

  $form['user_links']['reset_password'] = [
    '#type' => 'link',
    '#title' => t('Forgot password?'),
    '#url' => Url::fromRoute('user.pass'),
    '#attributes' => [
      'class' => [
        'uk-float-right',
        'uk-link',
        'uk-link-muted',
      ],
    ],
  ];

  $form['actions']['submit']['#attributes']['class'][] = 'uk-width-1-1';
  $form['actions']['submit']['#attributes']['class'][] = 'uk-button-large';
  $form['actions']['#weight'] = 4;
}

/**
 * Implements hook_theme_suggestions_HOOK_alter() for form templates.
 */
function uikit_blog_theme_suggestions_form_alter(array &$suggestions, array $variables) {
  $suggestions[] = 'form__' . $variables['element']['#form_id'];
}

/**
 * Implements hook_theme_suggestions_HOOK_alter() for user templates.
 */
function uikit_blog_theme_suggestions_user_alter(array &$suggestions, array $variables) {
  $suggestions[] = 'user__' . $variables['elements']['#view_mode'];
}

/**
 * Implements hook_theme_suggestions_HOOK_alter() for views_view.
 */
function uikit_blog_theme_suggestions_views_view_alter(array &$suggestions, array $variables) {
  $suggestions[] = 'views_view__' . $variables['view']->id();
}

/**
 * Implements hook_theme_suggestions_HOOK_alter() for views_view_unformatted.
 */
function uikit_blog_theme_suggestions_views_view_unformatted_alter(array &$suggestions, array $variables) {
  $suggestions[] = 'views_view_unformatted__' . $variables['view']->id();
}
