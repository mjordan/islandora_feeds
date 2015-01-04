<?php
/**
 * @file
 * Drush integration for the Islandora Feeds module.
 *
 * PLEASE NOTE: This Drush command currently can only create nodes,
 * not their corresponding Islandora objects. See
 * https://github.com/mjordan/islandora_feeds/issues/10 for more information.
 */

/**
 * Implements hook_drush_command().
 */
function islandora_feeds_drush_command() {
  $items['islandora-feeds-import'] = array(
    'description' => dt('Enable to run a specific feed import'),
    'options' => array(
      'feed-id' => array(
        'description' => dt('Feed ID to import. Please note that an importer must have "Process in background" checked to work with Drush.'),
      ),
    ),
    'examples' => array(
      'drush islandora-feeds-import --feed-id=fooimporter' => "The ID of the feed to load.",
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );
  return $items;
}

/**
 * Import a feed.
 */
function drush_islandora_feeds_import() {
  $feed_id = $repeat = drush_get_option('feed-id', NULL);
  $feed = db_query("SELECT * FROM {feeds_source} WHERE id = :id", array(':id' => $feed_id))->fetchObject();
  if ($feed->id) {
    $feed_obj = feeds_source($feed_id, $feed->feed_nid);
    $feed_config = $feed_obj->importer->getConfig();
    if ($feed_config['process_in_background']) {
      $feed_obj->startImport();
    }
    else {
      drush_log(dt('Feed @id does not have "Process in Background" enabled', array('@id' => $feed_id)), 'error');
    }
  }
  else {
    drush_log(dt('Invalid Feed ID: @id', array('@id' => $feed_id)), 'error');
  }
}
