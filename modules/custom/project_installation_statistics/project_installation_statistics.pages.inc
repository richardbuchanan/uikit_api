<?php

function project_installation_statistics_view_project($project) {
  $project_info = project_installation_statistics_load_project($project);
  drupal_set_title($project_info->title);

  return project_installation_statistics_show_project($project_info, $project_info->status);
}

function project_installation_statistics_delete_project_confirm($form, &$form_state, $project) {
  $project_info = project_installation_statistics_load_project($project);

  $form['#project'] = $project_info;
  $form['pid'] = array(
    '#type' => 'value',
    '#value' => $project_info->pid,
  );
  $form['project'] = array(
    '#type' => 'value',
    '#value' => $project_info->project,
  );

  return confirm_form($form,
    t('Are you sure you want to delete <em class="placeholder">@project</em>?', array('@project' => $project_info->title)),
    'admin/config/system/project-installation-statistics/' . $project_info->project,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

function project_installation_statistics_delete_project_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $project = project_installation_statistics_load_project($form_state['values']['project']);
    $delete = project_installation_statistics_delete_project($project->pid);

    if ($delete) {
      watchdog('statistics project', 'deleted @project.', array('@project' => $project->title));
      drupal_set_message(t('Project <em class="placeholder">@project</em> has been deleted.', array('@project' => $project->title)));
    }
  }

  $form_state['redirect'] = 'admin/config/system/project-installation-statistics';
}
