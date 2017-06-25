<?php

namespace Drupal\uikit_blog;

use Drupal\uikit\UIkit;

/**
 * Class UIkitBlog
 */
class UIkitBlog {

  /**
   * Provide a render array for an image.
   *
   * @param string $uri
   *   The uri of the image to render.
   * @param array $attributes
   *   The attributes to apply to the rendered image.
   *
   * @return array
   *   Return a theme array of the image to render.
   */
  public static function renderImage($uri = NULL, $attributes = []) {
    $logo = UIkit::getThemeSetting('logo');
    return $render_logo = [
      '#theme' => 'image',
      '#uri' => $logo['url'],
      '#attributes' => $attributes,
    ];
  }
}
