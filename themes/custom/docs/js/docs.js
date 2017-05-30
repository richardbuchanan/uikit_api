(function($) {

  $(document).ready(function() {
    footerPosition();
  });

  $(window).resize(function() {
    footerPosition();
  });

  $(document).click(function() {
    footerPosition();
  });

  $(function() {
    // Prevent empty anchor tags from being followed.
    $('article').on('click', '[href="#"], [href=""]', function (e) {
      e.preventDefault();
    });

  });

  function footerPosition() {
    var bodyHeight = $('body').outerHeight(true) - 30;
    var adminMenu = $('#admin-menu');
    var page = $('#page');
    var pageHeader = $('#page-header');
    var footer = $('#footer');
    var contentHeight = adminMenu.outerHeight() + page.outerHeight() + pageHeader.outerHeight() + footer.outerHeight();

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
      $('pre').click(function() {
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

  Drupal.behaviors.donateForm = {
    attach: function () {
      var other = $('.form-item-line-item-fields-commerce-donate-amount-und-other').hide();

      $('input[name="line_item_fields[commerce_donate_amount][und][select]"]').change(function() {
        if (this.value === 'select_or_other') {
          other.show();
        }
        else {
          other.hide();
        }
      });
    }
  }
})(jQuery);
