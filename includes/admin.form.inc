<?php

/**
 * @file
 * Admin form for the islandora_scholar.module
 */

/**
 * Created a system form element that defaults to a textfield.
 *
 * @param string $name
 *   The name of the form element/variable.
 * @param mixed $default
 *   The default value for the given form element/variable.
 * @param array $form_controls
 *   Form controls for the form element.
 *
 * @return array
 *   A system form element definition.
 */
function _islandora_scholar_add_variable($name, $default = '', $form_controls = array()) {
  $form_controls += array(
    '#type' => 'textfield',
    '#title' => $name,
  );
  $form_controls['#default_value'] = variable_get($name, $default);
  return array(
    $name => $form_controls,
  );
}

/**
 * Defines the admin settings form.
 *
 * @return array
 *   Drupal form definition.
 */
function islandora_scholar_admin_form() {
  $form = array(
    'romeo' => array(
      '#type' => 'fieldset',
      '#title' => t('RoMEO configuration'),
      '#description' => t('Various parameters used by RoMEO'),
      '#collapsible' => TRUE,
    ),
    'google_scholar_search' => array(
      '#type' => 'fieldset',
      '#title' => t('Google Scholar Search configuration'),
      '#description' => t('Various parameters used by Google Scholar Search'),
      '#collapsible' => TRUE,
    ),
  );

  $form += _islandora_scholar_add_variable('islandora_scholar_google_direct_to_fedora', FALSE, array(
    '#type' => 'checkbox',
    '#title' => t('Provide Google PDF viewer with direct URL.'),
    '#description' => t('Normally, we would have all calls go through Drupal get the relevant PDF. This option tries to make the call go directly to your associated Fedora instance.  (Note:  This will not work if you use "localhost" or a non-public IP address in the Islandora\'s base Fedora URL.)'),
  ));
  $form['google_scholar_search'] += _islandora_scholar_add_variable('islandora_scholar_google_scholar_search_enabled', FALSE, array(
    '#type' => 'checkbox',
    '#title' => t('Render Google Scholar Search link'),
    '#description' => t('Enable Searching in Google Scholar.'),
  ));
  $form['google_scholar_search'] += _islandora_scholar_add_variable('islandora_scholar_google_scholar_primary_search_xpath', "//mods:identifier[@type=\"doi\"]", array(
    '#type' => 'textfield',
    '#title' => t('Google Scholar Primary Search XPath'),
    '#description' => t('The primary xpath you want to use to search.'),
    '#states' => array(
      'visible' => array(
        ':input[name="islandora_scholar_google_scholar_search_enabled"]' => array('checked' => TRUE),
      ),
    ),
  ));
  $form['google_scholar_search'] += _islandora_scholar_add_variable('islandora_scholar_google_scholar_default_search_xpath', "//mods:title", array(
    '#type' => 'textfield',
    '#title' => t('Google Scholar Default Search XPath'),
    '#description' => t('The default xpath you want to use to search'),
    '#states' => array(
      'visible' => array(
        ':input[name="islandora_scholar_google_scholar_search_enabled"]' => array('checked' => TRUE),
      ),
    ),
  ));
  $form['romeo'] += _islandora_scholar_add_variable('islandora_scholar_romeo_enable', FALSE, array(
    '#type' => 'checkbox',
    '#title' => t('Enable RoMEO attempts.'),
    '#description' => t('Whether or not we should even try getting information from RoMEO.'),
  ));
  $form['romeo'] += _islandora_scholar_add_variable('islandora_scholar_romeo_url', 'http://www.sherpa.ac.uk/romeo/api29.php', array(
    '#title' => t('Sherpa/RoMEO URL'),
    '#description' => t('The URL to which to make requests.'),
  ));
  $form['romeo'] += _islandora_scholar_add_variable('islandora_scholar_romeo_key', '', array(
    '#title' => t('Sherpa/RoMEO API Key'),
    '#description' => t("Your institution's key to access RoMEO."),
  ));
  $form['romeo'] += _islandora_scholar_add_variable('islandora_scholar_issn_cache_time', 2, array(
    '#title' => t('ISSN cache time'),
    '#description' => t('The amount of time in days for which to maintain an ISSN value obtained by scanning an object.'),
  ));
  $form['romeo'] += _islandora_scholar_add_variable('islandora_scholar_romeo_cache_time', 2, array(
    '#title' => t('RoMEO cache time'),
    '#description' => t('The amount of time in days for which to maintain a copy of the markup for a given ISSN.'),
  ));

  return system_settings_form($form);
}
