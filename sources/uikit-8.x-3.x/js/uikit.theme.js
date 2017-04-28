/**
 * @file
 * Attaches behaviors for the UIkit theme.
 */

(function ($) {

  'use strict';

  Drupal.behaviors.uikitButtonLinks = {
    attach: function () {
      var buttonLink = $('a.button');

      buttonLink.each(function () {
        var coreButton = !this.classList.contains('uk-button');
        var dangerButton = this.classList.contains('button--danger');

        if (coreButton) {
          // Add the uk-button class to button links.
          $(this).addClass('uk-button');
        }

        if (dangerButton) {
          // Add the uk-button-danger class to button--danger links.
          $(this).addClass('uk-button-danger');
        }
      })
    }
  };
})(jQuery);