/**
 * @file
 * Attaches behaviors for uikit_blog.
 */

(function ($, Drupal, drupalSettings) {

  'use strict';

  Drupal.behaviors.UIkitBlogTooltips = {
    attach: function () {

      if (drupalSettings.uikit_tooltips) {
        $.each(drupalSettings.uikit_tooltip_options, function (index, value) {
          $('[title]').each(function () {
            $(this).attr(index, value);
          });
        });

        $('[title]').each(function () {
          $(this).attr('uk-tooltip', '');
          UIkit.tooltip($(this));
        });
      }
    }
  };

  Drupal.behaviors.UIkitBlogAccordions = {
    attach: function () {
      $('[uk-accordion]').each(function () {
        UIkit.tooltip($(this));
      });
    }
  };
})(jQuery, Drupal, drupalSettings);
