<?php

/**
 * @file
 * Common get functions.
 */

/**
 * Gets the uikit library.
 *
 * Checks if the uikit library is installed, and is at least version 2.0.0 but
 * below version 3.0.0. This function is useful when you want to check if the
 * library can be loaded, for example if you wanted to add a stylesheet from the
 * library that is not added by default. This is also used to check the library
 * can be loaded before loading it.
 *
 * @return bool
 *   Returns TRUE if the library is installed and meets the version comparison,
 *   otherwise returns FALSE.
 */
function _uikit_library_load() {
  $library_load = FALSE;
  $library_detect = libraries_detect('uikit');
  $library_version = $library_detect['version'];
  $min_version = version_compare($library_version, '2.0.0') >= 0;
  $max_version = version_compare($library_version, '3.0.0') == -1;

  if ($min_version && $max_version) {
    if ($library_detect['installed']) {
      $library_load = TRUE;
    }
  }
  return $library_load;
}

/**
 * Gets the version information from the UIkit library.
 *
 * @param array $library
 *   An associative array containing all information about the library.
 * @param array $options
 *   An associative array containing with the following keys:
 *   - file: The filename to parse for the version, relative to the library
 *     path. For example: 'docs/changelog.txt'.
 *   - pattern: A string containing a regular expression (PCRE) to match the
 *     library version. For example: '@version\s+([0-9a-zA-Z\.-]+)@'. Note that
 *     the returned version is not the match of the entire pattern (i.e.
 *     '@version 1.2.3' in the above example) but the match of the first
 *     sub-pattern (i.e. '1.2.3' in the above example).
 *   - lines: (optional) The maximum number of lines to search the pattern in.
 *     Defaults to 20.
 *   - cols: (optional) The maximum number of characters per line to take into
 *     account. Defaults to 200. In case of minified or compressed files, this
 *     prevents reading the entire file into memory.
 *
 * @see libraries_get_path()
 */
function _uikit_get_library_version($library, $options) {
  $file = DRUPAL_ROOT . '/' . $library['library path'] . '/' . $options['file'];
  if (empty($options['file']) || !file_exists($file)) {
    return;
  }

  $file = fopen($file, 'r');

  while ($options['lines'] && $line = fgets($file, $options['cols'])) {
    if (preg_match($options['pattern'], $line, $version)) {
      fclose($file);
      return $version[1];
    }
    $options['lines']--;
  }
  fclose($file);
}

/**
 * Gets the path to the uikit_library library.
 *
 * @return string
 *   Returns the library path for uikit_library.
 */
function _uikit_get_library_path() {
  $library = libraries_detect('uikit');
  return $library['library path'];
}
