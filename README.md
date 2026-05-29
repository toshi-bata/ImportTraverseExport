# ImportTraverseExport

This is the completed implementation accompanying the forum article:

> **How-to: Traverse a PRC model file using Visitor pattern for rapid prototyping**
> https://forum.techsoft3d.com/t/how-to-traverse-a-prc-model-file-using-visitor-pattern-for-rapid-prototyping/1456

The project serves as a portable workbench for prototyping with [HOOPS Exchange](https://learn.techsoft3d.com/exchange/latest/prog_guide/overview.html). It is extracted and adapted from the HOOPS Exchange SDK samples (prior to version 2026.3.0), providing a minimal, self-contained environment to quickly experiment with the Visitor pattern and other traversal techniques for PRC model files.

## Purpose

- Rapid prototyping of HOOPS Exchange traversal logic
- Experimenting with the Visitor pattern (`A3DTreeVisitor`, `A3DVisitorTransfo`, `A3DVisitorColorMaterials`, etc.)
- Learning how to extract geometry, transformation, visibility, and other attributes from a model hierarchy

## What It Does

1. **Import** — Loads a CAD model file via `A3DSDKHOOPSExchangeLoader`
2. **Traverse** — Walks the assembly tree using a custom `MyTreeVisitor` derived from `A3DTreeVisitor`, printing component names, visibility, and world-space positions
3. **Export** — Saves the model as PRC (or another format based on the output file extension)

## Project Structure

| File / Folder | Description |
|---|---|
| `ImportExport.cpp` | Entry point: initialize SDK, import, traverse, export |
| `MyTreeVisitor.h/.cpp` | Custom visitor — extend this for your own prototyping |
| `visitor/` | Visitor framework extracted from the HOOPS Exchange SDK samples |
| `common.hpp` | Utility macros and helpers |
| `HOOPSExchangeSamples.props` | Visual Studio property sheet for SDK paths |
| `_VS2022.bat` | Sets `HEXCHANGE_INSTALL_DIR` and launches VS2022 with the solution |

## Requirements

- HOOPS Exchange SDK (tested with 2026.4.0)
- Visual Studio 2022

## Getting Started

1. Edit `_VS2022.bat` to point `HEXCHANGE_INSTALL_DIR` to your SDK installation:
   ```bat
   SET HEXCHANGE_INSTALL_DIR=C:\SDK\Exchange\HOOPS_Exchange_2026.4.0
   ```
2. Run `_VS2022.bat` to open the solution in Visual Studio 2022.
3. Build and run. By default the input file path is defined by `DEFAULT_INPUT_CAD` in `common.hpp`.

## Usage

```
ImportExport.exe <input_file> [output_file] [log_file]
```

| Argument | Default |
|---|---|
| `input_file` | `DEFAULT_INPUT_CAD` (defined in `common.hpp`) |
| `output_file` | `<input_file>.prc` |
| `log_file` | `<output_file>_Log.txt` |

## Extending

Add your own traversal logic by overriding visit methods in `MyTreeVisitor`:

```cpp
virtual A3DStatus visitEnter(const A3DProductOccurrenceConnector& sConnector) override;
virtual A3DStatus visitEnter(const A3DPartConnector& sConnector) override;
virtual A3DStatus visitLeave(const A3DProductOccurrenceConnector& sConnector) override;
```
