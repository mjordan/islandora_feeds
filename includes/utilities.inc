<?php

/**
 * @file
 * Helper functions used by this module.
 */

/**
 * Query the resource index to get a list of collections or content
 * models.
 *
 * @param $type string
 *  Either 'collections' or 'cmodels'.
 *
 * @return array
 *   List of PIDs corresponding to the collections or content models.
 */
function islandora_feeds_get_collections_or_content_models($type) {
  $types = array(
    'collections' => 'islandora:collectionCModel',
    'cmodels' => 'fedora-system:ContentModel-3.0'
  );
  $type_for_query = '<info:fedora/' . $types[$type] . '>';
  // Query the rindex to get all collections.
  $tuque = islandora_get_tuque_connection();
  $ri_query = "select \$object \$label from <#ri>
     where \$object <fedora-model:hasModel> $type_for_query
      and \$object <fedora-model:label> \$label";
  $results = $tuque->repository->ri->itqlQuery($ri_query, 'unlimited');
  $ret = array();
  foreach ($results as $member) {
    $pid = preg_replace('/info:fedora\//', '', $member['object']['value']);
    $label = $member['label']['value'];
    // We don't want the root collection.
    if ($pid == 'islandora:root') {
      $label = 'Islandora Root Collection';
    }
    $ret[$pid] = $label;
  }
  return $ret;
}

/**
 * Ingest an Islandora object.
 *
 * @param object $entity
 *   The entity as it is passed into islandora_feeds_feeds_after_save().
 * @param string $namespace
 *   The Fedora namespace to use for this object.
 * @param string $dsid
 *   The datastream ID to use. This corresponds to the machine name of
 *   the content type bundle from which the object is created.
 * @param string $ds_label
 *   The datastream label to use,
 * @param string $cmodel
 *   The content model to use.
 * @param string $collection
 *   The collection to add the object to.
 * @return bool
 *   TRUE if the object was successfuly ingested, FALSE if not.
 */
function islandora_feeds_ingest_object($entity, $namespace, $cmodel, $collection, $owner) {
  // @todo: Add more granular error catching.
  try {
    $xml_ds = theme('islandora_feeds_item_ingest', array('node' => $entity));
    $tuque = new IslandoraTuque();
    $repository = $tuque->repository;
    $fedora_object = $repository->constructObject($namespace);
    $fedora_object->label = $entity->title;
    $fedora_object->owner = $owner;
    // Add the field data datastream
    // @todo: Use the label defined in the feed importer settings.
    $field_data_datastream = $fedora_object->constructDatastream('OBJ', 'M');
    $field_data_datastream->label = 'Field data';
    $field_data_datastream->mimetype = 'text/xml';
    $field_data_datastream->setContentFromString($xml_ds);
    $fedora_object->ingestDatastream($field_data_datastream);
    // Add the TN datastream
    if (isset($entity->field_tn['und'][0]['uri'])) {
      $tn_datastream = $fedora_object->constructDatastream('TN', 'M');
      $tn_datastream->label = 'TN';
      $tn_datastream->mimetype = $entity->field_tn['und'][0]['filemime'];
      $tn_datastream->setContentFromFile($entity->field_tn['und'][0]['uri']);
      $fedora_object->ingestDatastream($tn_datastream);
    }
    $fedora_object->relationships->add(FEDORA_MODEL_URI, 'hasModel', $cmodel);
    $fedora_object->relationships->add(FEDORA_RELS_EXT_URI, 'isMemberOfCollection', $collection);
    $repository->ingestObject($fedora_object);
  }
  catch (Exception $e) {
    drupal_set_message(t('Error ingesting Islandora object corresponding to node %n (title: %t): %m', array('%n' => $entity->nid, '%t' => $entity->title, '%m' => $e->getMessage())), 'error', FALSE);
  }
}

