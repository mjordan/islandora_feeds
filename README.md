# Islandora Feeds Importer

## Introduction

This module allows users to create Islandora objects using the Feeds contrib module. This is still a very early proof-of-concept module.

## Requirements

Feeds

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Usage

This module provides a Feeds processor that creates Islandora objects. Currently, the only datastream that is created is an XML file that contains elements mirroring the column headings in the CSV file (or equivalent in other input formats) you are loading using Feeds, with element values that correspond to the values in the columns.

The Processor provided by this module is similar to other Feeds processors. It uses a version of Feeds' Node processor to create a node for each item you are importing. Each node then serves as the source of the Islandora object that is created. You have the option of saving these nodes (for quality assurance) or deleting them immediately after the Islandora object is created.

For each content model you are importing objects into, you need to create a Drupal content type that contains all the fields corresponding to the data in your incoming Feed source. The nodes created during the import are instances of this content type.

## Troubleshooting/issues/feedback

Use cases are welcome. The goal of this module is to leverage as much of Feeds' built-in functionality as possible while providing the ability to load a wide range of Islandora content types as possible. If you have any questions or comments, please post them to:

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

