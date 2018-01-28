# Brand

An experience in creating and managing Drupal 7 subsites focused on the developer.

## Introduction

This module serves as a practical, managed solution to organisations needing to handle 'snowflakes' and 'unicorns'.

It is well-known that many Drupal developers create a variation of themekey at some point. This module is a feature-rich solution to that scenario but tailored to a maintainable and flexible configuration management system and released to the public via a GNU license.

This module is a bi-product of the work being done for pay by their employer, and the product was so well-built it was unfortunate something of this quality is not openly available when needed.

**Note**: This module was rewritten from scratch to get release here, however development on this module was done simultaneously to the module which inspired this one.

The ideas that went into this module are pretty simplistic:
* I need to control the templates, scripts and styles.
* I need it to be managed through an idempotent build system.
* I need it to expire and return to normal after a given date.
* I need to be able to change it as needed, without the use of source control.

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
  Detailed information is contained in here.
* After submitting the form, it's recommended to clear caches - especially if you're expecting anonymous traffic.

## Troubleshooting

* Issues and PR's are more than welcome, but it's recommended to produce replicatable results with the use of a debugger before opening an issue.

## Maintainers

* Karl Hepworth (@fubarhouse)