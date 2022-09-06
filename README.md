# Dialog101

This very simple "dialog box app" was built for the purposes of introducing new (sighted) users of screen reader technologies  (e.g. Freedom Scientific's [JAWS](https://www.freedomscientific.com/products/software/jaws/), [NVDA](https://www.nvaccess.org)) to interacting with common Windows dialog box controls.

This also served as a bit of a playground/exercise in using Qt layouts (rather than building everything in the UI designer).

## Build Environment

- Microsoft Visual Studio 2022 (Community Edition)
- Qt 6.4.0

A translation file is provided, but is not automatically rebuilt as a part of the project in VS.  Run `lupdate` from Qt (or by right clicking on the language file in the VS solution explorer) to generate a `.qm` file containing the French translations.
