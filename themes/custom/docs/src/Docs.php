<?php

namespace Drupal\docs;

/**
 * Provides helper functions for the Docs theme.
 */
class Docs {

  public static function getApiProjects() {
    $projects = array();

    $api_default_core_compatibility = variable_get('api_default_core_compatibility');
    $api_default_project = variable_get('api_default_project');

    foreach (api_get_branches() as $key => $branch) {
      $name = $branch->branch_name;
      $core_compatibility = $branch->core_compatibility;
      $project = $branch->project;
      $preferred = $branch->preferred;
      $branch_url = "api/$project/$name";

      $projects[$key] = array(
        'project' => $branch->project,
        'title' => $branch->title,
        'url' => $branch_url,
        'default_url' => $branch_url,
        'api_default_project' => FALSE,
      );

      $default_project = $project == $api_default_project;
      $default_core_compatibility = $core_compatibility == $api_default_core_compatibility;
      if ($default_project && $default_core_compatibility && $preferred) {
        $projects[$key]['default_url'] = "api/$project";
        $projects[$key]['api_default_project'] = TRUE;
      }
    }

    return $projects;
  }

}