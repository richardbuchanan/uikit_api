/**
 * @file
 * Attaches behaviors to the UIkit theme.
 */

(function ($) {
  'use strict';

  $(function() {
    var navbar = $('.uk-navbar-nav');

    // Prevent navbar parent links from being used as a link when clicked.
    navbar.on('click', '[href="#"], [href=""]', function (e) {
      e.preventDefault();
    }).find('[href="#"]').prop('href', '');
  });
})(jQuery);
