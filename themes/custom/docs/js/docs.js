(function($) {

  $(function() {
    // Prevent empty anchor tags from being followed.
    $('article').on('click', '[href="#"], [href=""]', function (e) {
      e.preventDefault();
    });

    var loginForm = $('.docs-login-form');
    var username = loginForm.find('[name="name"]');
    var password = loginForm.find('[name="pass"]');
    var loginButton = loginForm.find('.form-submit');

    loginButton.click(function (e) {
      var usernameEmpty = username.val() === '';
      var passwordEmpty = password.val() === '';
      var message = '';
      loginForm.prev('.uk-alert').remove();
      username.removeClass('uk-form-danger');
      password.removeClass('uk-form-danger');

      if (usernameEmpty && passwordEmpty) {
        e.preventDefault();
        username.addClass('uk-form-danger');
        password.addClass('uk-form-danger');
        message = '<div class="uk-alert uk-alert-danger">Username and password are required.</div>';
        loginForm.before(message);
      }
      else if (usernameEmpty) {
        e.preventDefault();
        username.addClass('uk-form-danger');
        message = '<div class="uk-alert uk-alert-danger">Username is required.</div>';
        loginForm.before(message);
      }
      else if (passwordEmpty) {
        e.preventDefault();
        password.addClass('uk-form-danger');
        message = '<div class="uk-alert uk-alert-danger">Password is required.</div>';
        loginForm.before(message);
      }
    });
  });

  function tableDoubleScroll() {
    var overflowContainer = $('.uk-overflow-container');

    overflowContainer.doubleScroll();
    $('.doubleScroll-scroll').css('width', overflowContainer.find('table:not(.sticky-header)').width());
  }

  function bodyMinHeight() {
    var adminMenu = typeof Drupal.settings.admin_menu !== 'undefined';
    var adminMenuHeight = adminMenu ? 29 : 0;
    var headerHeight = $('#page-header').outerHeight(true);
    var footerHeight = $('#footer').outerHeight(true);
    var windowHeight = document.body.clientHeight;
    var minHeight = adminMenuHeight + headerHeight + footerHeight + 15;

    if ((windowHeight - minHeight) > 0) {
      $('#page').css('min-height', (windowHeight - minHeight));
    }
  }

  function footerPosition() {
    var bodyHeight = $('body').outerHeight(true) - 30;
    var adminMenu = $('#admin-menu');
    var page = $('#page');
    var pageHeader = $('#page-header');
    var footer = $('#footer');
    var contentHeight = adminMenu.outerHeight() + page.outerHeight() + pageHeader.outerHeight() + footer.outerHeight();

    if (location.pathname !== '/user/register') {
      if (contentHeight < bodyHeight) {
        footer.css({
          'position': 'fixed',
          'bottom': 0,
          'width': '100%'
        });
      }
      else {
        footer.css('position', 'static');
      }
    }
  }

  $(window).resize(function() {
    bodyMinHeight();
    footerPosition();
  });

  $(document).click(function() {
    bodyMinHeight();
    footerPosition();
  });

  $(document).ready(function() {
    bodyMinHeight();
    footerPosition();
    tableDoubleScroll();
  });

})(jQuery);

(function($) {

  Drupal.behaviors.externalLinks = {
    attach: function () {
      if (location.hostname === 'uikit-drupal.com') {
        $('a').each(function () {
          if (this.hostname !== location.host) {
            // Make sure all external links open in a new tab.
            $(this).prop('target', '_blank');

            if (/drupal/i.test(this.hostname)) {
              $(this).addClass('drupal-api');
            }
          }
        });
      }
    }
  };

  Drupal.behaviors.stickySidebar = {
    attach: function () {
      $('#region-sidebar-second-wrapper').each(function() {
        var windowHeight = $(window).outerHeight() - $('#page-header').outerHeight();
        var sidebarHeight = $(this).outerHeight();

        if (sidebarHeight > windowHeight) {
          $(this).removeAttr('data-uk-sticky');
        }
      });
    }
  };

  Drupal.behaviors.docsSVGFallback = {
    attach: function () {
      if (!Modernizr.svg) {
        $('img[src*="svg"]').attr('src', function() {
          return $(this).attr('src').replace('.svg', '.png');
        });
      }
    }
  };

  Drupal.behaviors.selectCode = {
    attach: function () {
      $('pre>code').click(function() {
        $(this).select();

        var text = this,
          range, selection;

        if (document.body.createTextRange) {
          range = document.body.createTextRange();
          range.moveToElementText(text);
          range.select();
        } else if (window.getSelection) {
          selection = window.getSelection();
          range = document.createRange();
          range.selectNodeContents(text);
          selection.removeAllRanges();
          selection.addRange(range);
        }
      });
    }
  };

  Drupal.behaviors.emptyParagraphs = {
    attach: function () {
      $('p').filter(function () { return $.trim(this.innerHTML) === '' }).remove();
    }
  };

  Drupal.behaviors.docsNavBar = {
    attach: function () {
      $('#offcanvas').find('[docs-nolink]').removeAttr('docs-nolink').attr('href', '#');
      $('[docs-nolink]')
        .on('click', function (e) {
          e.preventDefault();
        })
        .removeAttr('href');

      $('[docs-nav-divider]').siblings('ul').find('li:first-child').before('<li class="uk-nav-divider" docs-nav-divider-list-item></li>');
    }
  };

  Drupal.behaviors.navbarTitle = {
    attach: function () {
      $('.uk-navbar').find('a').each( function () {
        $(this).prop('title', '');
      })
    }
  };
})(jQuery);
