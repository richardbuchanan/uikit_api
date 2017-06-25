<?php

/**
 * @file
 * Set up variables to be placed within the template (.html.twig) files.
 *
 * The variables set up here apply to both templates (.html.twig) files and
 * functions (theme_HOOK). These are also used for providing
 * @link https://www.drupal.org/node/2354645 Twig Template naming conventions @endlink.
 *
 * @see process.inc
 */

use Drupal\Core\Url;
use Drupal\file\Entity\File;
use Drupal\uikit\UIkit;

/**
 * Implements template_preprocess_page().
 */
function uikit_blog_preprocess_page(&$variables) {
  // Add the sticky navbar component to the header element.
  $variables['header_attributes']['uk-sticky'] = '';
  $variables['header_attributes']['media'] = '(min-width: 960px)';

  // Change the page attribute classes to new array.
  $variables['page_attributes']['class'] = ['uk-container'];

  $tooltips = UIkit::getThemeSetting('uikit_tooltips');
  $variables['#attached']['drupalSettings']['uikit_tooltips'] = 'false';
  if ($tooltips) {
    // Pass uikit_tooltips to drupalSettings with "true" value.
    $variables['#attached']['drupalSettings']['uikit_tooltips'] = 'true';

    // Create tooltip options array.
    $tooltip_options['pos'] = UIkit::getThemeSetting('tooltip_position');
    $tooltip_options['offset'] = UIkit::getThemeSetting('tooltip_offset');
    $tooltip_options['animation'] = UIkit::getThemeSetting('tooltip_animation');
    $tooltip_options['duration'] = UIkit::getThemeSetting('tooltip_duration');
    $tooltip_options['delay'] = UIkit::getThemeSetting('tooltip_delay');
    $tooltip_options['cls'] = UIkit::getThemeSetting('tooltip_active_class');

    // Pass $tooltip_options to drupalSettings.
    $variables['#attached']['drupalSettings']['uikit_tooltip_options'] = $tooltip_options;
  }
}

/**
 * Implements template_preprocess_node().
 */
function uikit_blog_preprocess_node(&$variables) {
  $node = $variables['node'];

  // Get and set the node creation date format to display for nodes. This will
  // fallback to 'medium' when the user has not selected a different format in
  // the theme settings.
  $created = $node->getCreatedTime();
  $date_format = UIkit::getThemeSetting('node_date_format') ? UIkit::getThemeSetting('node_date_format') : 'medium';

  if ($date_format != 'custom') {
    $date = \Drupal::service('date.formatter')
      ->format($created, $date_format);
  }
  else {
    $date_format = UIKit::getThemeSetting('node_date_format__custom');
    $date = \Drupal::service('date.formatter')
      ->format($created, 'custom', $date_format);
  }

  // Change the date variable to our new formatted date.
  $variables['date'] = $date;
}

/**
 * Implements template_preprocess_form().
 */
function uikit_blog_preprocess_form(&$variables) {
  // Add the form id as a variable.
  $variables['form_id'] = $variables['element']['#form_id'];
}

/**
 * Implements hook_preprocess_HOOK() for input.html.twig.
 */
function uikit_blog_preprocess_input(&$variables) {
  $element = $variables['element'];
  $submit = isset($element['#type']) && $element['#type'] == 'submit';

  if ($submit) {
    // Add the uk-button class.
    $variables['attributes']['class'] = ['uk-button'];

    // Add uk-button-* classes based on the value of the button.
    $value = $element['#value']->render();
    switch ($value) {
      case 'Advanced search':
      case 'Create new account':
      case 'Log in':
      case 'Save':
      case 'Search':
      case 'Send message':
      case 'Submit':
        $variables['attributes']['class'][] = 'uk-button-primary';
        break;

      case 'Preview':
        $variables['attributes']['class'][] = 'uk-button-warning';
        break;

      default:
        $variables['attributes']['class'][] = 'uk-button-default';
    }
  }
}

/**
 * Implements template_preprocess_links() for links--node.html.twig.
 */
function uikit_blog_preprocess_links__node(&$variables) {
  foreach ($variables['links'] as $key => $item) {
    if (isset($item['link'])) {
      $attributes = $item['link']['#options']['attributes'];
      $class_string = isset($attributes['class']) && !is_array($attributes['class']);

      if ($class_string) {
        // Not all modules set the classes as an array, so convert the class
        // string to an array.
        $classes = explode(' ' , $attributes['class']);
        $variables['links'][$key]['link']['#options']['attributes']['class'] = $classes;

        foreach ($classes as $class_key => $class) {
          if ($class == 'hidden') {
            // Add the uk-hidden class to items with the hidden class.
            $variables['links'][$key]['attributes']['class'][] = 'uk-hidden';
          }
        }
      }
    }
  }
}

/**
 * Implements template_preprocess_menu().
 */
function uikit_blog_preprocess_menu(&$variables) {
  $current_path = \Drupal::service('path.current')->getPath();
  $front_page = Drupal::config('system.site')->get('page.front');

  foreach ($variables['items'] as $key => $item) {
    if ($current_path == $item['url']->toString()) {
      // Add the uk-active class when current page matches the url.
      $variables['items'][$key]['attributes']->addClass('uk-active');
    }
    elseif ($current_path == $front_page && $item['url']->toString() == '/') {
      // Checking if the front page is the active link requires a little more
      // work before adding the uk-active class. This still works when using the
      // frontpage view with a pager and separate pages.
      $variables['items'][$key]['attributes']->addClass('uk-active');
    }
  }
}

/**
 * Implements template_preprocess_menu_local_tasks().
 */
function uikit_blog_preprocess_menu_local_tasks(&$variables) {
  $current_path = \Drupal::service('path.current')->getPath();
  $user_login = Url::fromRoute('user.login')->toString();
  $user_page = Url::fromRoute('user.page')->toString();
  $user_pass = Url::fromRoute('user.pass')->toString();
  $user_register = Url::fromRoute('user.register')->toString();
  $user_is_anonymous = \Drupal::currentUser()->isAnonymous();

  if ($user_is_anonymous) {
    // Remove the local task menus when the user is anonymous and visiting one
    // of the user login/register/password pages.
    switch ($current_path) {
      case $user_login:
      case $user_page:
      case $user_pass:
      case $user_register:
        $variables['primary'] = [];
        $variables['secondary'] = [];
        break;
    }
  }
}

/**
 * Implements template_preprocess_page_title().
 */
function uikit_blog_preprocess_page_title(&$variables) {
  $variables['title_attributes']['class'][] = 'uk-text-center';
}

/**
 * Implements template_preprocess_user().
 */
function uikit_blog_preprocess_user(&$variables) {
  $user_picture = !$variables['elements']['#user']->user_picture->isEmpty();
  $default_user_picture_setting = UIkit::getThemeSetting('default_user_picture');
  $user_picture_custom = FALSE;
  $user_picture_icon = FALSE;

  if (!$user_picture) {
    // Since Drupal 8 removes the option to set a default user picture, use the
    // UIkit Blog theme settings to render a default.
    $custom_user_picture_setting = UIkit::getThemeSetting('custom_user_picture_upload');
    $custom_user_icon = UIkit::getThemeSetting('custom_user_picture_icon');

    switch ($default_user_picture_setting) {
      case 'icon':
        // Custom UIkit icon.
        $user_picture_icon = $custom_user_icon;
        break;

      case 'custom':
        // Custom picture upload.
        $user_picture_custom = $custom_user_picture_setting;
        $file = File::load($user_picture_custom[0]);
        $path = $file->getFileUri();
        $user_picture_custom = [
          '#theme' => 'image_style',
          '#style_name' => 'thumbnail',
          '#uri' => $path,
        ];
        break;
    }
  }
  else {
    $variables['content']['user_picture'] = $variables['elements']['#user']->user_picture->view('large');
    $variables['content']['user_picture'][0]['#item_attributes']['class'][] = 'uk-border-circle';
  }

  // Set three new variables to be called in user.html.twig to determine what to
  // render as the default user picture. user_picture_default is the image
  // supplied by each user, or otherwise FALSE. user_picture_custom uses the
  // image uploaded in the theme settings when a user has not uploaded their
  // own image. user_picture_icon is the default fallback, using a Font Awesome
  // icon as chosen in the theme settings.
  $variables['user_picture_default'] = $user_picture;
  $variables['user_picture_custom'] = $user_picture_custom;
  $variables['user_picture_icon'] = $user_picture_icon;
}
