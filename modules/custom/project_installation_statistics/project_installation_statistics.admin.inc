<?php

function project_installation_statistics_list() {
  $page = array();

  $header = array(
    array(
      'data' => t('Project name'),
      'field' => 'pis.project',
      'sort' => 'asc',
    ),
    t('Project URL'),
    array('data' => t('Operations'), 'colspan' => 2),
  );
  $rows = array();

  $projects = db_select('project_installation_statistics', 'pis')
    ->fields('pis')
    ->extend('TableSort')
    ->orderByHeader($header)
    ->execute()
    ->fetchAllAssoc('project', PDO::FETCH_ASSOC);

  foreach ($projects as $project) {
    $row = array();

    // Define various links.
    $project_url = 'admin/config/system/project-installation-statistics/' . $project['project'];
    $project_delete_url = 'admin/config/system/project-installation-statistics/' . $project['project'] . '/delete';
    $project_drupal_url = 'https://www.drupal.org/project/' . $project['project'];

    // Theme inline links for operations row.
    $links = array();
    $links[] = array(
      'title' => t('View project'),
      'href' => $project_url,
      'attributes' => array(
        'title' => t('View @project weekly statistics.', array('@project' => $project['title'])),
      ),
    );
    $links[] = array(
      'title' => t('Delete project'),
      'href' => $project_delete_url,
      'attributes' => array(
        'title' => t('Delete the project @project and associated weekly statistics.', array('@project' => $project['title'])),
      ),
    );
    $operations = theme('links', array(
      'links' => $links,
      'attributes' => array('class' => array('links', 'inline')),
    ));

    $project_url_attributes = array(
      'attributes' => array(
        'title' => t('View @project weekly statistics.', array('@project' => $project['title'])),
      ),
    );
    $project_drupal_url_attributes = array(
      'attributes' => array(
        'target' => '_blank',
        'title' => t('View @project on drupal.org.', array('@project' => $project['title'])),
      ),
    );

    // Create the rows.
    $row[] = l($project['title'], $project_url, $project_url_attributes);
    $row[] = l($project_drupal_url, $project_drupal_url, $project_drupal_url_attributes);
    $row[] = $operations;
    $rows[] = $row;
  }

  if (empty($rows)) {
    $rows[] = array(array(
      'colspan' => 4,
      'data' => t('There are currently no projects. <a href="!url">Add a new one</a>.', array('!url' => url('admin/config/system/project-installation-statistics/add'))),
    ));
  }

  $page['project_installation_statistics_list'] = array(
    '#markup' => theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array(
        'class' => array('project-statistics-list'),
      ),
    )),
  );

  return $page;
}

function project_installation_statistics_add_form($form, &$form_state) {
  $form['project'] = array(
    '#type' => 'textfield',
    '#title' => t('Project name'),
    '#default_value' => '',
    '#required' => TRUE,
    '#description' => t('Enter the project machine-name for a project hosted on drupal.org. The machine name is found at the end of the project URL, i.e. <em class="placeholder">uikit</em> is the machine-name for the UIkit project found at https://www.drupal.org/project/uikit'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create new project'),
  );

  return $form;
}

function project_installation_statistics_add_form_submit($form, &$form_state) {
  $project = $form_state['values']['project'];
  $success = project_installation_statistics_save_project($project);
  if ($success) {
    project_installation_statistics_generate_statistics($project);
    $form_state['redirect'] = 'admin/config/system/project-installation-statistics/' . $project;
  }
  else {
    $form_state['redirect'] = 'admin/config/system/project-installation-statistics';
  }
}
