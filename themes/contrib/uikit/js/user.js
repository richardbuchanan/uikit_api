/**
 * @file
 * Override Drupal's password behaviors.
 *
 * UIkit's password component requires changes to the password field template.
 * This causes the User module's user.js to not work as expected, so this script
 * replaces it.
 */

(function ($) {

  /**
   * Attach handlers to evaluate the strength of any password fields.
   *
   * Checks that its confirmation is correct.
   */
  Drupal.behaviors.password = {
    attach: function (context, settings) {
      var translate = settings.password;
      $('input.password-field', context).once('password', function () {
        var passwordCheckStrength = true;
        var passwordCheckMatches = true;
        var passwordInput = $(this);
        var innerWrapper = $(this).parent().parent().find('.pass-strength-target');
        var outerWrapper = $(this).parent().parent().parent();

        // Add identifying class to password element parent.
        innerWrapper.addClass('password-parent');

        // Add the password confirmation layer.
        var confirmTarget = $('input.password-confirm', outerWrapper).parent().parent().find('.pass-confirm-target');
        confirmTarget.addClass('uk-panel uk-panel-box uk-margin').before('<div class="password-confirm">' + translate['confirmTitle'] + ' <span></span></div>').addClass('confirm-parent').hide();
        var confirmInput = $('input.password-confirm', outerWrapper);
        var confirmResult = $('div.password-confirm', outerWrapper);
        var confirmChild = $('span', confirmResult);

        // Add the description box.
        var passwordMeter = '<div class="password-strength"><div class="password-indicator"><div class="indicator"></div></div><div class="password-strength-title">' + translate['strengthTitle'] + ' <span class="password-strength-text" aria-live="assertive"></span></div></div>';
        $(confirmInput).parent().parent().find('.pass-confirm-target').append('<div class="password-suggestions description"></div>');
        $(innerWrapper).prepend(passwordMeter);
        var passwordDescription = $('div.password-suggestions', outerWrapper).hide();

        // Check the password strength.
        var passwordCheck = function () {

          // Evaluate the password strength.
          var result = Drupal.evaluatePasswordStrength(passwordInput.val(), settings.password);

          // Update the suggestions for how to improve the password.
          if (passwordDescription.html() != result.message) {
            var message = result.message.replace('To make your password stronger:<ul>', '<h3 class="uk-panel-title">To make your password stronger</h3><ul class="uk-list">');
            passwordDescription.html(message);
            console.log(message);
          }

          // Only show the description box if there is a weakness in the password.
          if (result.strength == 100) {
            passwordDescription.hide();
          }
          else {
            passwordDescription.show();
          }

          // Adjust the length of the strength indicator.
          $(innerWrapper).find('.indicator').css('width', result.strength + '%');

          // Adjust the length of the strength indicator.
          var indicatorClass = 'is-weak';
          var strength = result.strength;

          if (strength < 60) {
            indicatorClass = 'is-weak';
          }
          else if (strength >= 60 && strength < 75) {
            indicatorClass = 'is-fair';
          }
          else if (strength >= 75 && strength < 87.5) {
            indicatorClass = 'is-good';
          }
          else {
            indicatorClass = 'is-strong';
          }

          $(innerWrapper).find('.indicator')
            .css('width', result.strength + '%')
            .removeClass('is-weak is-fair is-good is-strong')
            .addClass(indicatorClass);

          // Update the strength indication text.
          $(innerWrapper).find('.password-strength-text').html(result.indicatorText);

          passwordCheckMatch();
          passwordCheckAll();
        };

        // Check that password and confirmation inputs match.
        var passwordCheckMatch = function () {

          if (confirmInput.val()) {
            var success = passwordInput.val() === confirmInput.val();

            // Show the confirm result.
            confirmResult.show();

            // Remove the previous styling if any exists.
            if (this.confirmClass) {
              confirmChild.removeClass(this.confirmClass);
            }

            // Fill in the success message and set the class accordingly.
            var confirmClass = success ? 'ok' : 'error';
            confirmChild.html(translate['confirm' + (success ? 'Success' : 'Failure')]).removeClass('ok error').addClass(confirmClass);
            this.confirmClass = confirmClass;
          }
          else {
            // confirmResult.hide();
          }
        };

        var passwordCheckAll = function () {
          var result = Drupal.evaluatePasswordStrength(passwordInput.val(), settings.password);
          var success = passwordInput.val() === confirmInput.val();

          if (result.strength == 100) {
            confirmTarget.hide();
          }
          else {
            confirmTarget.show();
          }
        };

        // Monitor keyup and blur events.
        // Blur must be used because a mouse paste does not trigger keyup.
        passwordInput.keyup(passwordCheck).focus(passwordCheck).blur(passwordCheck);
        confirmInput.keyup(passwordCheckMatch).blur(passwordCheckMatch);
        confirmInput.keyup(passwordCheckAll).focus(passwordCheckAll).blur(passwordCheckAll);
      });
    }
  };

  /**
 * Evaluate the strength of a user's password.
 *
 * Returns the estimated strength and the relevant output message.
 */
  Drupal.evaluatePasswordStrength = function (password, translate) {
    password = $.trim(password);

    var weaknesses = 0, strength = 100, msg = [];

    var hasLowercase = /[a-z]+/.test(password);
    var hasUppercase = /[A-Z]+/.test(password);
    var hasNumbers = /[0-9]+/.test(password);
    var hasPunctuation = /[^a-zA-Z0-9]+/.test(password);

    // If there is a username edit box on the page, compare password to that, otherwise
    // use value from the database.
    var usernameBox = $('input.username');
    var username = (usernameBox.length > 0) ? usernameBox.val() : translate.username;

    // Lose 5 points for every character less than 6, plus a 30 point penalty.
    if (password.length < 6) {
      msg.push(translate.tooShort);
      strength -= ((6 - password.length) * 5) + 30;
    }

    // Count weaknesses.
    if (!hasLowercase) {
      msg.push(translate.addLowerCase);
      weaknesses++;
    }
    if (!hasUppercase) {
      msg.push(translate.addUpperCase);
      weaknesses++;
    }
    if (!hasNumbers) {
      msg.push(translate.addNumbers);
      weaknesses++;
    }
    if (!hasPunctuation) {
      msg.push(translate.addPunctuation);
      weaknesses++;
    }

    // Apply penalty for each weakness (balanced against length penalty).
    switch (weaknesses) {
      case 1:
        strength -= 12.5;
        break;

      case 2:
        strength -= 25;
        break;

      case 3:
        strength -= 40;
        break;

      case 4:
        strength -= 40;
        break;
    }

    // Check if password is the same as the username.
    if (password !== '' && password.toLowerCase() === username.toLowerCase()) {
      msg.push(translate.sameAsUsername);
      // Passwords the same as username are always very weak.
      strength = 5;
    }

    // Based on the strength, work out what text should be shown by the password strength meter.
    var indicatorText;
    if (strength < 60) {
      indicatorText = translate.weak;
    }
    else if (strength < 70) {
      indicatorText = translate.fair;
    }
    else if (strength < 80) {
      indicatorText = translate.good;
    }
    else if (strength <= 100) {
      indicatorText = translate.strong;
    }

    // Assemble the final message.
    msg = translate.hasWeaknesses + '<ul><li>' + msg.join('</li><li>') + '</li></ul>';
    return { strength: strength, message: msg, indicatorText: indicatorText };

  };

  /**
   * Field instance settings screen.
   *
   * Force the 'Display on registration form' checkbox checked whenever
   * 'Required' is checked.
   */
  Drupal.behaviors.fieldUserRegistration = {
    attach: function (context, settings) {
      var $checkbox = $('form#field-ui-field-edit-form input#edit-instance-settings-user-register-form');

      if ($checkbox.length) {
        $('input#edit-instance-required', context).once('user-register-form-checkbox', function () {
          $(this).bind('change', function (e) {
            if ($(this).attr('checked')) {
              $checkbox.attr('checked', true);
            }
          });
        });

      }
    }
  };

})(jQuery);
