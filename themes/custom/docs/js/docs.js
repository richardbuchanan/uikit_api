(function($) {
  Drupal.behaviors.externalLinks = {
    attach: function () {
      $('a').each(function() {
        if (this.hostname != location.host) {
          // Make sure all external links open in a new tab.
          $(this).prop('target', '_blank');
        }
      });
    }
  };
})(jQuery);