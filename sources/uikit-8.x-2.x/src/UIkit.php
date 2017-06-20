<?php

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
  const UIKIT_LIBRARY = 'https://getuikit.com/v2/';

  /**
   * The UIkit library version supported in the UIkit base theme.
   *
   * @var string
   */
  const UIKIT_LIBRARY_VERSION = '2.27.4';

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
   *   The machine-name of the theme setting to retrieve.
   * @param $theme
   *   The theme to retrieve the setting for. Defaults to the active theme.
   *
   * @return mixed
   *   The theme setting's value.
   */
  public static function getThemeSetting($setting, $theme = NULL) {
    if (empty($theme)) {
      $theme = self::getActiveTheme();
    }

    if (!empty($setting)) {
      return theme_get_setting($setting, $theme);
    }
    else {
      throw new \LogicException('Missing argument $setting');
    }
  }

  /**
   * Retrieves the base style for a theme.
   *
   * @return mixed
   *   The base style for the theme.
   */
  public static function getBaseStyle() {
    return self::getThemeSetting('base_style');
  }

  /**
   * Retrieves the base-style library of the UIkit base theme.
   *
   * @return string
   *   The base-style's library to retrieve from the UIkit base theme.
   */
  public static function getUIkitLibrary() {
    switch (self::getBaseStyle()) {
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

  /**
   * Retrieves a component library of the UIkit base theme.
   *
   * @param string $component
   *   The component to retrieve.
   *
   * @return string
   *   The component's library to retrieve from the UIkit base theme.
   */
  public static function getUIkitComponent($component) {
    if (!empty($component)) {
      switch (self::getBaseStyle()) {
        case 'almost-flat':
          return "uikit/uikit.$component.almost-flat";

        case 'gradient':
          return "uikit/uikit.$component.gradient";

        default:
          return "uikit/uikit.$component";
      }
    }
    else {
      throw new \LogicException('Missing argument $component');
    }
  }

  /**
   * Retrieves the grid classes used in page.html.twig.
   *
   * @param bool $sidebar_first
   *   True if the sidebar_first region has content, false otherwise.
   * @param bool $sidebar_second
   *   True if the sidebar_second region has content, false otherwise.
   *
   * @return array
   *   An array of grid classes to use in page.html.twig.
   */
  public static function getGridClasses($sidebar_first = FALSE, $sidebar_second = FALSE) {
    $standard_layout = self::getThemeSetting('standard_sidebar_positions');
    $tablet_layout = self::getThemeSetting('tablet_sidebar_positions');
    $mobile_layout = self::getThemeSetting('mobile_sidebar_positions');

    $grid_classes = [
      'content' => [],
      'sidebar' => [],
    ];

    if ($sidebar_first) {
      $grid_classes['sidebar']['first'] = [];
    }
    if ($sidebar_second) {
      $grid_classes['sidebar']['second'] = [];
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

  /**
   * Retrieves the current page title.
   *
   * @return string
   *   The current page title.
   */
  public static function getPageTitle() {
    $request = \Drupal::request();
    $route_match = \Drupal::routeMatch();
    return \Drupal::service('title_resolver')->getTitle($request, $route_match->getRouteObject());
  }

}
