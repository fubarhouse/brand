# Brand

![stability-experimental](https://img.shields.io/badge/stability-experimental-orange.svg)

A developer-centric experience in creating and managing Drupal 7 sub-sites through the use of theme management.

These sub-sites share everything with the parent website (such as the database), however the pages selected via logic will show a selected theme based upon a range of options.

This is essentially a very fancy version of [ThemeKey](https://www.drupal.org/project/themekey)

Please note this project is experimental. Though mature, it's still possible that schema changes may happen. Tagged releases will include database updates as necessary however the master branch may not.

## Introduction

This module serves as a practical, managed solution to organisations needing to handle 'snowflakes' and 'unicorns'.

It is well-known that many Drupal developers create a variation of ThemeKey at some point. This module is a feature-rich solution to that scenario but tailored to a maintainable and flexible configuration management system and released to the public via a GNU license.

The ideas that went into this module are pretty simplistic:
* It needs to control the templates, scripts and styles.
* It needs to be manageable through an idempotent build system.
* It needs to be able to expire and return to normal after a given date.
* It needs to be able to change as needed, without the use of source control.

## Requirements

None.

## Installation

Installation is standard for Drupal 7 modules.

See https://drupal.org/documentation/install/modules-themes/modules-7 for more information.

Be sure to clear site caches and rebuild any registries after enabling the module and as code becomes available for use by the module.

## Configuration

* Under the administrative options for User Interface, find the link to the Brand module.
* If there are no brands, you can add a new brand using the link above the table, or at the top of the page.
* Follow the prompts, filling out the fields as required.
  Detailed information is available next to the form fields.
* After submitting the form, it's recommended to clear caches - especially if you're expecting anonymous traffic.

## Troubleshooting

* Issues and PR's are more than welcome, but please do so if you can produce replicable results.

## Maintainers

* Karl Hepworth ([@fubarhouse](https://twitter.com/fubarhouse))