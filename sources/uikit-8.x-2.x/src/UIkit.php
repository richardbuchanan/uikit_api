<?php
/**
 * @file
 * Contains \Drupal\uikit\UIkit.
 */

namespace Drupal\uikit;

/**
 * Provides helper functions for the UIkit base theme.
 */
class UIkit {

  /**
   * The UIkit library project page.
   *
   * @var string
   */
  const UIKIT_LIBRARY = 'https://getuikit.com';

  /**
   * The UIkit library version supported in the UIkit base theme.
   *
   * @var string
   */
  const UIKIT_LIBRARY_VERSION = '2.27.2';

  /**
   * The UIkit library documentation site.
   *
   * @var string
   */
  const UIKIT_LIBRARY_DOCUMENTATION = 'https://getuikit.com/v2/index.html';

  /**
   * The Drupal project page for the UIkit base theme.
   *
   * @var string
   */
  const UIKIT_PROJECT = 'https://www.drupal.org/project/uikit';

  /**
   * The Drupal project branch for the UIkit base theme.
   *
   * @var string
   */
  const UIKIT_PROJECT_BRANCH = '8.x-2.x';

  /**
   * The Drupal project API site for the UIkit base theme.
   *
   * @var string
   */
  const UIKIT_PROJECT_API = 'http://uikit-drupal.com';

  /**
   * Retrieves the active theme.
   *
   * @return
   *   The active theme's machine name.
   */
  public static function getActiveTheme() {
    return \Drupal::theme()->getActiveTheme()->getName();
  }

  /**
   * Retrieves a theme setting.
   *
   * @param null $setting
   *   The setting to get.
   * @param $theme
   *   The theme to get the setting for. Default is active theme.
   *
   * @return mixed
   *   The theme setting's value.
   */
  public static function getThemeSetting($setting, $theme = NULL) {
    if (empty($theme)) {
      $theme = UIkit::getActiveTheme();
    }

    return theme_get_setting($setting, $theme);
  }

  public static function getBaseStyle() {
    return UIkit::getThemeSetting('base_style');
  }

  public static function getUIkitLibrary() {
    switch (UIkit::getBaseStyle()) {
      case 'almost-flat':
        return 'uikit/uikit.almost-flat';
        break;

      case 'gradient':
        return 'uikit/uikit.gradient';
        break;

      default:
        return 'uikit/uikit';
    }
  }

  public static function getUIkitComponent($component) {
    switch (UIkit::getBaseStyle()) {
      case 'almost-flat':
        return "uikit/uikit.$component.almost-flat";

      case 'gradient':
        return "uikit/uikit.$component.gradient";

      default:
        return "uikit/uikit.$component";
    }
  }

  public static function getGridClasses($sidebar_first = FALSE, $sidebar_second = FALSE) {
    $standard_layout = UIkit::getThemeSetting('standard_sidebar_positions');
    $tablet_layout = UIkit::getThemeSetting('tablet_sidebar_positions');
    $mobile_layout = UIkit::getThemeSetting('mobile_sidebar_positions');

    $grid_classes = array(
      'content' => array(),
      'sidebar' => array(),
    );

    if ($sidebar_first) {
      $grid_classes['sidebar']['first'] = array();
    }
    if ($sidebar_second) {
      $grid_classes['sidebar']['second'] = array();
    }

    if ($sidebar_first && $sidebar_second) {
      $grid_classes['content'][] = 'uk-width-large-1-2';
      $grid_classes['sidebar']['first'][] = 'uk-width-large-1-4';
      $grid_classes['sidebar']['second'][] = 'uk-width-large-1-4';

      switch ($standard_layout) {
        case 'holy-grail':
          $grid_classes['content'][] = 'uk-push-large-1-4';
          $grid_classes['sidebar']['first'][] = 'uk-pull-large-1-2';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-large';
          break;

        case 'sidebars-left':
          $grid_classes['content'][] = 'uk-push-large-1-2';
          $grid_classes['sidebar']['first'][] = 'uk-pull-large-1-2';
          $grid_classes['sidebar']['second'][] = 'uk-pull-large-1-2';
          break;

        case 'sidebars-right':
          $grid_classes['content'][] = 'uk-push-pull-large';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-large';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-large';
          break;
      }

      switch ($tablet_layout) {
        case 'holy-grail':
          $grid_classes['content'][] = 'uk-width-medium-1-2';
          $grid_classes['content'][] = 'uk-push-medium-1-4';

          $grid_classes['sidebar']['first'][] = 'uk-width-medium-1-4';
          $grid_classes['sidebar']['first'][] = 'uk-pull-medium-1-2';

          $grid_classes['sidebar']['second'][] = 'uk-width-medium-1-4';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-medium';
          break;

        case 'sidebars-left':
          $grid_classes['content'][] = 'uk-width-medium-1-2';
          $grid_classes['content'][] = 'uk-push-medium-1-2';

          $grid_classes['sidebar']['first'][] = 'uk-width-medium-1-4';
          $grid_classes['sidebar']['first'][] = 'uk-pull-medium-1-2';

          $grid_classes['sidebar']['second'][] = 'uk-width-medium-1-4';
          $grid_classes['sidebar']['second'][] = 'uk-pull-medium-1-2';
          break;

        case 'sidebars-right':
          $grid_classes['content'][] = 'uk-width-medium-1-2';
          $grid_classes['content'][] = 'uk-push-pull-medium';

          $grid_classes['sidebar']['first'][] = 'uk-width-medium-1-4';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-medium';

          $grid_classes['sidebar']['second'][] = 'uk-width-medium-1-4';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-medium';
          break;

        case 'sidebar-left-stacked':
          $grid_classes['content'][] = 'uk-width-medium-3-4';
          $grid_classes['content'][] = 'uk-push-medium-1-4';

          $grid_classes['sidebar']['first'][] = 'uk-width-medium-1-4';
          $grid_classes['sidebar']['first'][] = 'uk-pull-medium-3-4';

          $grid_classes['sidebar']['second'][] = 'uk-width-medium-1-1';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-medium';
          break;

        case 'sidebar-right-stacked':
          $grid_classes['content'][] = 'uk-width-medium-3-4';
          $grid_classes['content'][] = 'uk-push-pull-medium';

          $grid_classes['sidebar']['first'][] = 'uk-width-medium-1-4';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-medium';

          $grid_classes['sidebar']['second'][] = 'uk-width-medium-1-1';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-medium';
          break;
      }

      switch ($mobile_layout) {
        case 'sidebars-stacked':
          $grid_classes['content'][] = 'uk-width-small-1-1';
          $grid_classes['content'][] = 'uk-width-1-1';
          $grid_classes['content'][] = 'uk-push-pull-small';

          $grid_classes['sidebar']['first'][] = 'uk-width-small-1-1';
          $grid_classes['sidebar']['first'][] = 'uk-width-1-1';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-small';

          $grid_classes['sidebar']['second'][] = 'uk-width-small-1-1';
          $grid_classes['sidebar']['second'][] = 'uk-width-1-1';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-small';
          break;

        case 'sidebars-vertical':
          $grid_classes['content'][] = 'uk-width-small-1-1';
          $grid_classes['content'][] = 'uk-width-1-1';
          $grid_classes['content'][] = 'uk-push-pull-small';

          $grid_classes['sidebar']['first'][] = 'uk-width-small-1-2';
          $grid_classes['sidebar']['first'][] = 'uk-width-1-2';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-small';

          $grid_classes['sidebar']['second'][] = 'uk-width-small-1-2';
          $grid_classes['sidebar']['second'][] = 'uk-width-1-2';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-small';
          break;
      }
    }
    elseif ($sidebar_first) {
      $grid_classes['content'][] = 'uk-width-large-3-4';
      $grid_classes['sidebar']['first'][] = 'uk-width-large-1-4';
      $grid_classes['content'][] = 'uk-width-medium-3-4';
      $grid_classes['sidebar']['first'][] = 'uk-width-medium-1-4';

      switch ($standard_layout) {
        case 'holy-grail':
          $grid_classes['content'][] = 'uk-push-large-1-4';
          $grid_classes['sidebar']['first'][] = 'uk-pull-large-3-4';
          break;

        case 'sidebars-left':
          $grid_classes['content'][] = 'uk-push-large-1-4';
          $grid_classes['sidebar']['first'][] = 'uk-pull-large-3-4';
          break;

        case 'sidebars-right':
          $grid_classes['content'][] = 'uk-push-pull-large';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-large';
          break;
      }

      switch ($tablet_layout) {
        case 'holy-grail':
          $grid_classes['content'][] = 'uk-push-medium-1-4';
          $grid_classes['sidebar']['first'][] = 'uk-pull-medium-3-4';
          break;

        case 'sidebars-left':
          $grid_classes['content'][] = 'uk-push-medium-1-4';
          $grid_classes['sidebar']['first'][] = 'uk-pull-medium-3-4';
          break;

        case 'sidebars-right':
          $grid_classes['content'][] = 'uk-push-pull-medium';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-medium';
          break;

        case 'sidebar-left-stacked':
          $grid_classes['content'][] = 'uk-push-medium-1-4';
          $grid_classes['sidebar']['first'][] = 'uk-pull-medium-3-4';
          break;

        case 'sidebar-right-stacked':
          $grid_classes['content'][] = 'uk-push-pull-medium';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-medium';
          break;
      }
    }
    elseif ($sidebar_second) {
      $grid_classes['content'][] = 'uk-width-large-3-4';
      $grid_classes['sidebar']['second'][] = 'uk-width-large-1-4';

      switch ($standard_layout) {
        case 'holy-grail':
          $grid_classes['content'][] = 'uk-push-pull-large';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-large';
          break;

        case 'sidebars-left':
          $grid_classes['content'][] = 'uk-push-large-1-4';
          $grid_classes['sidebar']['second'][] = 'uk-pull-large-3-4';
          break;

        case 'sidebars-right':
          $grid_classes['content'][] = 'uk-push-pull-large';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-large';
          break;
      }

      switch ($tablet_layout) {
        case 'holy-grail':
          $grid_classes['content'][] = 'uk-width-medium-3-4';
          $grid_classes['sidebar']['second'][] = 'uk-width-medium-1-4';
          $grid_classes['content'][] = 'uk-push-pull-medium';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-medium';
          break;

        case 'sidebars-left':
          $grid_classes['content'][] = 'uk-width-medium-3-4';
          $grid_classes['sidebar']['second'][] = 'uk-width-medium-1-4';
          $grid_classes['content'][] = 'uk-push-medium-1-4';
          $grid_classes['sidebar']['second'][] = 'uk-pull-medium-3-4';
          break;

        case 'sidebars-right':
          $grid_classes['content'][] = 'uk-width-medium-3-4';
          $grid_classes['sidebar']['second'][] = 'uk-width-medium-1-4';
          $grid_classes['content'][] = 'uk-push-pull-medium';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-medium';
          break;

        case 'sidebar-left-stacked':
          $grid_classes['content'][] = 'uk-width-medium-1-1';
          $grid_classes['sidebar']['second'][] = 'uk-width-medium-1-1';
          $grid_classes['content'][] = 'uk-push-pull-medium';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-medium';
          break;

        case 'sidebar-right-stacked':
          $grid_classes['content'][] = 'uk-width-medium-1-1';
          $grid_classes['sidebar']['second'][] = 'uk-width-medium-1-1';
          $grid_classes['content'][] = 'uk-push-pull-medium';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-medium';
          break;
      }
    }
    else {
      $grid_classes['content'][] = 'uk-width-1-1';
    }

    return $grid_classes;
  }

  public static function getPageTitle() {
    $request = \Drupal::request();
    $route_match = \Drupal::routeMatch();
    return \Drupal::service('title_resolver')->getTitle($request, $route_match->getRouteObject());
  }
}
