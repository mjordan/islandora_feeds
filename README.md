# Islandora Feeds Importer

## Introduction

This module allows users to create Islandora objects using the Feeds contrib module.

## Requirements

[Feeds](https://drupal.org/project/feeds)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Usage

### Creating objects

This module provides a Feeds processor that creates Islandora objects. Currently, the only datastream that is created is a managed XML datastream that contains elements mirroring the column headings in CSV files (or equivalent in other input formats) you are loading using Feeds, with element values that correspond to the values in the columns.

The Processor provided by this module is similar to other Feeds processors. It uses a version of Feeds' Node processor to create a node for each item you are importing. Each node then serves as the source of the Islandora object that is created. You have the option of saving these nodes (for quality assurance) or deleting them immediately after the Islandora object is created. You also have the option of importing the data into nodes but creating the corresponding Islandora objects later, using Views Bulk Operations.

For each type of data that you are importing into each object's XML datastream, you need to create a Drupal content type that contains all the fields corresponding to the data in your incoming Feed source and then map the incoming data to those fields using the standard tools provided by Feeds. The nodes created during the import are instances of this content type, and each node generates a corresponding Islandora object. All objects created by this module share a single Islandora content model, but within a given Islandora collection, all the objects will generally share the same field definition. The important thing to remember is that the content model defined by this module can accommodate arbitrary field definitions (although currently it only produces datastreams that contain flat XML datastructures).

After you have created your content type, configure your Feed importer by going to Structure > Feeds importers > Add importer and create a new importer. Attach your content type to the importer. Then edit the importer. The only settings you need to configure are the Processor settings. Under the Processor settings, select the Islandora Feeds node processor, and save. Then in the Processor Mappings, map the fields in your CSV (or similar) source to fields in your target content type.

Be sure to select the correct Islandora content model (which should be "Islandora Feeds Content Model"), collection, and datastream label. The datastream ID will correspond to the machine name of the bundle you attach the feed to. Also choose whether you want to create the objects during the import or later, and whether you want to delete the nodes. Note that these nodes do not have any relationship to the objects ingested into Fedora after the objects are created - they are only used as the source of the ingest and are not synchronized with the objects after the import. 

You should map one of the fields in your source to Title in your target. The only other columns in your source you need to map are the ones you have defined in your target content type - you do not need to map any of the node properties unless you want to.

Once you have configured the importer, you're ready to import your source content like you would using any other Feeds importer.

### Generating a schema from your content type

If you want to create add/edit forms for your objects using the Islandora XML Forms Builder, you will need to generate a schema. You can do this by going to Structure > your content type > edit > Islandora Feeds Schema. Simply copy the schema into a file (ending in .xsd) in the module's 'xml' directory so the Forms Builder can access it. Every time you add or remove a field from your content type, you should update the .xsd file.

## Notes

* Mapping a source field that is a number to the title won’t work. Islandora defaults to sequential numbering as a label when you attempt it. 
* When deleting nodes, the error message suggests you’ve deleted Islandora objects. This is not correct - only the Drupal content is deleted. 

## To do

* Improve and generalize the theming of the XML when viewed.
* Add the ability to inspect/edit/etc. nodes before ingesting the objects into Fedora (mostly done; requires [Views Bulk Operations](https://drupal.org/project/views_bulk_operations))
* Filter out content models in the config settings form that don't make sense.
* Figure out how to import handle thumbnails and additional datastreams.
* Figure out how to support deleting content loaded via this module.

## Troubleshooting/issues/feedback

Use cases are welcome. The goal of this module is to leverage as much of Feeds' built-in functionality as possible while providing the ability to load a wide range of Islandora content types as possible. If you have any questions or comments, please post them to:

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

