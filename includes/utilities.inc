<?php

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

function islandora_feeds_create_xml_datastream($item, $entity) {
  $xml = new XMLWriter();
  $xml->openMemory();
  $xml->setIndent(TRUE);
  $xml->startDocument('1.0', 'utf-8', NULL);
  $xml->startElement('custom');
  foreach ($item as $field => $value) {
    $clean_field = str_replace(' ', '_', $field);
    $xml->writeElement($clean_field, $value);
  }
  $xml->endElement();
  return $xml->outputMemory();
}

/**
 * Ingest an Islandora object. @todo: Can we resuse an existing function
 *  to do this?
 *
 * @param object $entity
 *   The entity as it is passed into islandora_feeds_feeds_after_save().
 * @param array $item
 *   The Feeds item.
 * @param string $namespace
 *   The Fedora namespace to use for this object.
 * @param string $dsid
 *   The datastream ID to use,
 * @param string $ds_label
 *   The datastream label to use,
 * @param string $xml_ds
 *   The serialized XML datastream to add to the object.
 * @param string $cmodel
 *   The content model to use.
 * @param string $collection
 *   The collection to add the object to.
 * @return bool
 *    TRUE if the object was successfuly ingested, FALSE if not.
 */
function islandora_feeds_ingest_object($entity, $item, $namespace, $dsid, $ds_label, $xml_ds, $cmodel, $collection) {
  // @todo: Add more granular error catching.
  try {
    $xml_ds = islandora_feeds_create_xml_datastream($item, $entity);
    $tuque = new IslandoraTuque();
    $repository = $tuque->repository;
    $fedora_object = $repository->constructObject($namespace);
    $fedora_object->label = $entity->title;
    $datastream = $fedora_object->constructDatastream($dsid, 'X');
    $datastream->label = $ds_label;
    $datastream->mimetype = 'text/xml';
    $datastream->setContentFromString($xml_ds);
    $fedora_object->ingestDatastream($datastream);
    $fedora_object->relationships->add(FEDORA_MODEL_URI, 'hasModel', $cmodel);
    $fedora_object->relationships->add(FEDORA_RELS_EXT_URI, 'isMemberOfCollection', $collection);
    $repository->ingestObject($fedora_object);
  }
  catch (Exception $e) {
    drupal_set_message(t('Error ingesting Islandora object corresponding to node %n (title: %t): %m', array('%n' => $entity->nid, '%t' => $entity->title, '%m' => $e->getMessage())), 'error', FALSE);
  }
}
