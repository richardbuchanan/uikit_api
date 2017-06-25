CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Recommendations
 * Installation
 * Configuration
 * Creating a sub-theme
 * Maintainers


INTRODUCTION
------------

The UIkit theme is a lightweight frontend framework with a comprehensive
collection of HTML, CSS, and JS components. It is a great alternative to other
frontend frameworks, plus is very lightweight and provides a lot of useful tools
for customizing with very little requirements.

 * For a full description of the theme, visit the project page:
   https://drupal.org/project/uikit

 * To submit bug reports and feature suggestions, or to track changes:
   https://drupal.org/project/issues/uikit


REQUIREMENTS
------------

There are no requirements to using UIkit.


RECOMMENDATIONS
------------

The following modules are recommended and fully supported by the UIkit for
Drupal theme.

 * UIkit Components:
   Provides additional components and functionality to the UIkit base theme.
   https://www.drupal.org/project/uikit_components


INSTALLATION
------------

 * Install as you would normally install a contributed Drupal theme. See:
   https://www.drupal.org/getting-started/install-contrib/themes
   for further information.
 * It is recommended to create a sub-theme to use as the default theme on your
   site instead of using the UIkit base theme as the default theme. Any changes
   made to the UIkit base theme will be overwritten when you update UIkit.
   See the Creating a sub-theme section below to learn how to create a UIkit
   sub-theme.


CONFIGURATION
-------------

The theme settings can be found at admin/appearance/settings/uikit. Each UIkit
component has its own settings, as well as many settings to control the
behavior of Drupal core components. As the development of this theme continues,
more settings will be added through updates.


CREATING A SUB-THEME
--------------------

Since any changes made to the UIkit base theme will be overwritten when UIkit is
updated, it is highly recommended to create a UIkit sub-theme to use as the
default theme on your Drupal site.

There are three ways to create a UIkit sub-theme:
 * Following the documentation on drupal.org
   (https://www.drupal.org/docs/8/theming-drupal-8/creating-a-drupal-8-sub-theme-or-sub-theme-of-sub-theme)
 * Copying the STARTERKIT folder in the UIkit base theme and changing the
   filenames and functions/settings from STARTERKIT to your sub-theme name.
 * Using the automated Drush commands UIkit offers.

The first option is recommended for advanced themers who want complete control
over how the sub-theme functions and understands sub-theme inheritance.

The second option is pretty straight forward and also recommended for advanced
themers who understand Drupal 8 theme file structures and knows how to rename
files and functions.

The third option is by far the easiest and is the preferred method of creating
a UIkit sub-theme. We've included a Drush command which requires very little
input from the user to automatically create a UIkit sub-theme with the correct
file structure, filenames and functions.

Learn how to create a UIkit sub-theme using the Drush option:
https://www.drupal.org/docs/8/themes/uikit/creating-a-sub-theme


MAINTAINERS
-----------

Current maintainers:
 * Richard C Buchanan, III (Richard Buchanan)
   - https://www.drupal.org/u/richard-buchanan
