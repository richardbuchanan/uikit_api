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
  const UIKIT_LIBRARY = 'https://getuikit.com/';

  /**
   * The UIkit library version supported in the UIkit base theme.
   *
   * @var string
   */
  const UIKIT_LIBRARY_VERSION = '3.0.0-beta.25';

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
  const UIKIT_PROJECT_BRANCH = '8.x-3.x';

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
      $grid_classes['content'][] = 'uk-width-1-2@l';
      $grid_classes['sidebar']['first'][] = 'uk-width-1-4@l';
      $grid_classes['sidebar']['second'][] = 'uk-width-1-4@l';

      switch ($standard_layout) {
        case 'holy-grail':
          $grid_classes['content'][] = 'uk-push-large-1-4';
          $grid_classes['sidebar']['first'][] = 'uk-pull-1-2@l';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-@l';
          break;

        case 'sidebars-left':
          $grid_classes['content'][] = 'uk-push-1-2@l';
          $grid_classes['sidebar']['first'][] = 'uk-pull-1-2@l';
          $grid_classes['sidebar']['second'][] = 'uk-pull-1-2@l';
          break;

        case 'sidebars-right':
          $grid_classes['content'][] = 'uk-push-pull-@l';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-@l';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-@l';
          break;
      }

      switch ($tablet_layout) {
        case 'holy-grail':
          $grid_classes['content'][] = 'uk-width-1-2@m';
          $grid_classes['content'][] = 'uk-push-1-4@m';

          $grid_classes['sidebar']['first'][] = 'uk-width-1-4@m';
          $grid_classes['sidebar']['first'][] = 'uk-pull-1-2@m';

          $grid_classes['sidebar']['second'][] = 'uk-width-1-4@m';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-@m';
          break;

        case 'sidebars-left':
          $grid_classes['content'][] = 'uk-width-1-2@m';
          $grid_classes['content'][] = 'uk-push-1-2@m';

          $grid_classes['sidebar']['first'][] = 'uk-width-1-4@m';
          $grid_classes['sidebar']['first'][] = 'uk-pull-1-2@m';

          $grid_classes['sidebar']['second'][] = 'uk-width-1-4@m';
          $grid_classes['sidebar']['second'][] = 'uk-pull-1-2@m';
          break;

        case 'sidebars-right':
          $grid_classes['content'][] = 'uk-width-1-2@m';
          $grid_classes['content'][] = 'uk-push-pull-@m';

          $grid_classes['sidebar']['first'][] = 'uk-width-1-4@m';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-@m';

          $grid_classes['sidebar']['second'][] = 'uk-width-1-4@m';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-@m';
          break;

        case 'sidebar-left-stacked':
          $grid_classes['content'][] = 'uk-width-3-4@m';
          $grid_classes['content'][] = 'uk-push-1-4@m';

          $grid_classes['sidebar']['first'][] = 'uk-width-1-4@m';
          $grid_classes['sidebar']['first'][] = 'uk-pull-3-4@m';

          $grid_classes['sidebar']['second'][] = 'uk-width-1-1@m';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-@m';
          break;

        case 'sidebar-right-stacked':
          $grid_classes['content'][] = 'uk-width-3-4@m';
          $grid_classes['content'][] = 'uk-push-pull-@m';

          $grid_classes['sidebar']['first'][] = 'uk-width-1-4@m';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-@m';

          $grid_classes['sidebar']['second'][] = 'uk-width-1-1@m';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-@m';
          break;
      }

      switch ($mobile_layout) {
        case 'sidebars-stacked':
          $grid_classes['content'][] = 'uk-width-1-1@s';
          $grid_classes['content'][] = 'uk-width-1-1';
          $grid_classes['content'][] = 'uk-push-pull-@s';

          $grid_classes['sidebar']['first'][] = 'uk-width-1-1@s';
          $grid_classes['sidebar']['first'][] = 'uk-width-1-1';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-@s';

          $grid_classes['sidebar']['second'][] = 'uk-width-1-1@s';
          $grid_classes['sidebar']['second'][] = 'uk-width-1-1';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-@s';
          break;

        case 'sidebars-vertical':
          $grid_classes['content'][] = 'uk-width-1-1@s';
          $grid_classes['content'][] = 'uk-width-1-1';
          $grid_classes['content'][] = 'uk-push-pull-@s';

          $grid_classes['sidebar']['first'][] = 'uk-width-1-2@s';
          $grid_classes['sidebar']['first'][] = 'uk-width-1-2';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-@s';

          $grid_classes['sidebar']['second'][] = 'uk-width-1-2@s';
          $grid_classes['sidebar']['second'][] = 'uk-width-1-2';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-@s';
          break;
      }
    }
    elseif ($sidebar_first) {
      $grid_classes['content'][] = 'uk-width-3-4@l';
      $grid_classes['sidebar']['first'][] = 'uk-width-1-4@l';
      $grid_classes['content'][] = 'uk-width-3-4@m';
      $grid_classes['sidebar']['first'][] = 'uk-width-1-4@m';

      switch ($standard_layout) {
        case 'holy-grail':
          $grid_classes['content'][] = 'uk-push-1-4@l';
          $grid_classes['sidebar']['first'][] = 'uk-pull-3-4@l';
          break;

        case 'sidebars-left':
          $grid_classes['content'][] = 'uk-push-1-4@l';
          $grid_classes['sidebar']['first'][] = 'uk-pull-3-4@l';
          break;

        case 'sidebars-right':
          $grid_classes['content'][] = 'uk-push-pull-@l';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-@l';
          break;
      }

      switch ($tablet_layout) {
        case 'holy-grail':
          $grid_classes['content'][] = 'uk-push-1-4@m';
          $grid_classes['sidebar']['first'][] = 'uk-pull-3-4@m';
          break;

        case 'sidebars-left':
          $grid_classes['content'][] = 'uk-push-1-4@m';
          $grid_classes['sidebar']['first'][] = 'uk-pull-3-4@m';
          break;

        case 'sidebars-right':
          $grid_classes['content'][] = 'uk-push-pull-@m';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-@m';
          break;

        case 'sidebar-left-stacked':
          $grid_classes['content'][] = 'uk-push-1-4@m';
          $grid_classes['sidebar']['first'][] = 'uk-pull-3-4@m';
          break;

        case 'sidebar-right-stacked':
          $grid_classes['content'][] = 'uk-push-pull-@m';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-@m';
          break;
      }
    }
    elseif ($sidebar_second) {
      $grid_classes['content'][] = 'uk-width-3-4@l';
      $grid_classes['sidebar']['second'][] = 'uk-width-1-4@l';

      switch ($standard_layout) {
        case 'holy-grail':
          $grid_classes['content'][] = 'uk-push-pull-@l';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-@l';
          break;

        case 'sidebars-left':
          $grid_classes['content'][] = 'uk-push-1-4@l';
          $grid_classes['sidebar']['second'][] = 'uk-pull-3-4@l';
          break;

        case 'sidebars-right':
          $grid_classes['content'][] = 'uk-push-pull-@l';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-@l';
          break;
      }

      switch ($tablet_layout) {
        case 'holy-grail':
          $grid_classes['content'][] = 'uk-width-3-4@m';
          $grid_classes['sidebar']['second'][] = 'uk-width-1-4@m';
          $grid_classes['content'][] = 'uk-push-pull-@m';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-@m';
          break;

        case 'sidebars-left':
          $grid_classes['content'][] = 'uk-width-3-4@m';
          $grid_classes['sidebar']['second'][] = 'uk-width-1-4@m';
          $grid_classes['content'][] = 'uk-push-1-4@m';
          $grid_classes['sidebar']['second'][] = 'uk-pull-3-4@m';
          break;

        case 'sidebars-right':
          $grid_classes['content'][] = 'uk-width-3-4@m';
          $grid_classes['sidebar']['second'][] = 'uk-width-1-4@m';
          $grid_classes['content'][] = 'uk-push-pull-@m';
          $grid_classes['sidebar']['first'][] = 'uk-push-pull-@m';
          break;

        case 'sidebar-left-stacked':
          $grid_classes['content'][] = 'uk-width-1-1@m';
          $grid_classes['sidebar']['second'][] = 'uk-width-1-1@m';
          $grid_classes['content'][] = 'uk-push-pull-@m';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-@m';
          break;

        case 'sidebar-right-stacked':
          $grid_classes['content'][] = 'uk-width-1-1@m';
          $grid_classes['sidebar']['second'][] = 'uk-width-1-1@m';
          $grid_classes['content'][] = 'uk-push-pull-@m';
          $grid_classes['sidebar']['second'][] = 'uk-push-pull-@m';
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
