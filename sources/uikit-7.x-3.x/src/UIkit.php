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
  const UIKIT_PROJECT_BRANCH = '7.x-3.x';

  /**
   * The Drupal project API site for the UIkit base theme.
   *
   * @var string
   */
  const UIKIT_PROJECT_API = 'http://uikit-drupal.com/api/uikit/7.x-3.x';

  /**
   * The jQuery library version UIkit supports.
   *
   * @var string
   */
  const UIKIT_JQUERY_VERSION = '2.1.4';

  /**
   * The jQuery Migrate library version UIkit supports.
   *
   * @var string
   */
  const UIKIT_JQUERY_MIGRATE_VERSION = '1.4.1';

  /**
   * Retrieves the active theme.
   *
   * @return
   *   The active theme's machine name.
   */
  public static function getActiveTheme() {
    global $theme;
    return $theme;
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
      $theme = UIkit::getActiveTheme();
    }

    if (!empty($setting)) {
      return theme_get_setting($setting, $theme);
    }
    else {
      throw new \LogicException('Missing argument $setting');
    }
  }

  /**
   * Retrieves the current page title.
   *
   * @return string
   *   The current page title.
   */
  public static function getPageTitle() {
    return drupal_get_title();
  }
}