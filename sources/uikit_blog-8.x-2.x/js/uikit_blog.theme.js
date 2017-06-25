/**
 * @file
 * Attaches behaviors for uikit_blog.
 */

(function ($, Drupal, drupalSettings) {

  'use strict';

  Drupal.behaviors.UIkitBlog = {
    attach: function () {

      if (drupalSettings.uikit_tooltips) {
        // Prepare the tooltip options for data-uk-tooltip.
        var tooltipOptions = '{';
        var i = 0;

        $.each(drupalSettings.uikit_tooltip_options, function (index, value) {
          if (i < drupalSettings.uikit_tooltips.length) {
            // All but the last option should be followed with a comma.
            tooltipOptions += index + ":" + value + ",";
            i++;
          }
          else {
            tooltipOptions += index + ":" + value;
          }
        });

        tooltipOptions += '}';

        $('[title]').each(function () {
          // Add data-uk-tooltip with the tooltip options to all elements with
          // the title attribute.
          $(this).attr('data-uk-tooltip', tooltipOptions);
        });
      }
    }
  };
})(jQuery, Drupal, drupalSettings);
