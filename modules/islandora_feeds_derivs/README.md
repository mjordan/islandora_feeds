# Islandora Feeds Derivs

## Requirements

[Islandora Feeds](https://github.com/mjordan/islandora_feeds)

## Installation

Islandora Feeds Derivs is included with Islandora Feeds, but it must be enabled separately.

## Overview

This module allows generating a MODS (or other XML) datastream from an OBJ datastream created by the Islandora Feeds module.

Given a OBJ datastream like this:

```xml
<fielddata>
  <title label="Title">Object's witty title</title>
  <field_1 label="Field 1">Object's field 1 value</field_1>
  <field_2 label="Field 2">Object's field 2 value</field_2>
</fielddata>
```
this module creates a MODS datastream like this and adds it to the object:

```xml
<!-- Your MODS markup that precedes titleInfo goes here -->
<titleInfo>
  <title>Object's witty title</title>
  <subTitle/>
</titleInfo>
<!-- Your MODS markup that follows titleInfo goes here -->
```

## Configuration

In addition to configuring some settings using the form at admin/islandora/tools/feeds/derivs, all you need to do to create XML derivatives for objects you are ingesting via Islandora Feeds is to is write an XSL stylesheet to transform the OBJ datastream created by that solution pack into your desired derivative. You can create multiple datastreams at once if you provide multiple XSL files. The admin settings (which are also linked to from within the admin settings of the Islandora Feeds, if the module is enabled) look like this:

![Islandora Feeds Derivs](https://dl.dropboxusercontent.com/u/1015702/linked_to/islandora_feeds_derivs_admin.png)

Not only can this module generate deriviate XML datastreams from the OBJ, it can:

* share objects that are imported by Islandora Feeds with specific collections
* change the objects' content model on the fly
* delete the OBJ datastream
* replace the the OBJ datastream with a derivitive datastream

The first three options are useful if your ultimate goal is to create objects (of any content model, in any  collection) by converting CSV data into MODS datastreams. In other words, if you have CSV data that describes still images, you can import it using Islandora Feeds, write a stylesheet that transforms the resulting OBJ datastreams into MODS, configure Islandora Feeds Derivs to create the MODS datastreams, and to clean up, tell Islandora Feeds Derivs to delete the OBJ datastream, change the content model to islandora:sp_basic_image, and share the objects with the collection that contains still images.

The last option, replace the the OBJ datastream with a derivitive datastream, lets you create OBJ datastreams with arbitrarily complex XML content. Essentially, your Feeds data is first imported into the flat OBJ XML produced by Islandora Feeds, then a derivitive is created via an XSL transformation, then the original OBJ datastream is deleted and recreated with the content from the derivative. Note that the original OBJ content is not retained as an earlier version of the datastream.

## Usage

Islandora Feeds Derivs creates derivatives of the OBJ datastream at the time that datastream is created. For example, if you create your Islandora objects during the Feeds import, that's when the derivatives are created; if you create your Islandora objects later (using Views Bulk Operations, as descrived in the README for Islandora Feeds), the derivatives are created then.

### An example

Since Islandora Feeds Derivs can create any XML datastream from the flat XML created by Islandora Feeds, you can use it to import MODS datastreams. The XSL stylesheet provided with the module is a good place to start; it only copies the OBJ's 'title' element into the MODS template, but you can modify it, or copy it and create another stylesheet, to suite your specific needs.

A typical workflow for using Islandora Feeds and Islandora Feeds Derivs to import data that will end up in MODS datastreams would be:

1. Create a Drupal content type that has a text field for each element in the MODS records you want to populate (this is required by Islandora Feeds).
2. Test the content type by importing some data from a CSV file using Islandora Feeds. Once you have imported some test objects, download several of the OBJ datastreams and start writing your stylesheet to use with the Islandora Feeds Derivs module. You can use your favorite XML/XSL authoring tools to do this writing and testing.
3. When you are satisfied with your offline tests, upload your stylesheet into the Islandora Feeds Derivs /xml directory and configure Islandora Feeds Derivs to use your stylesheet to create MODS datastreams, to set the preferred target collection and content models for your objects, and to delete the OBJ datastream if you want.
4. Using Islandora Feeds, import your CSV data. During the creation of the corresponding Islandora objects, Islandora Feeds Derivs creates a MODS datastream for each object (and deletes the original OBJ if you have configured it to do so).

## XSL Stylesheets used by this module

They are standard stylesheets, but they need to include two `<xsl:param>` elements that identify the datastream ID and datastream label of the destination datastream. For example, the foo.xsl stylesheet included with the module uses these two parameters to indicate that the destination datastream's ID is 'FOO' and its label is 'FOO record':

``` xml
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:param name="DSID">FOO</xsl:param>
  <xsl:param name="DSLABEL">FOO record</xsl:param>

  <xsl:template match="/">
	<!-- The title is the only element we grab from the OBJ. -->
	<title><xsl:value-of select="fielddata/title"/></title>
        <someelement>Some value</someelement>
  </xsl:template>
</xsl:stylesheet>
```
If your stylesheet doesn't contain these elements, a default DSID of 'NONEPROVIDED' and a default datastream label of 'None provided' will be used. Also, since the OBJ datastream's XML uses 'fielddata' as its document element, your stylesheet's XPath queries should be relative to that element.

Finally, since your stylesheets need to live inside the Feeds Deriv's /xml directory, alway keep backups so they don't get accidently deleted during upgrade.

## Troubleshooting/issues/feedback

Use cases are welcome. If you have any questions or comments, please post them to:

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

