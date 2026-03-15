# SmartSense PCB Files

This directory contains the editable PCB and schematic source files.

## EDA Stack

- Tool format indicates Altium Designer source projects (`.SchDoc`, `.PcbDoc`).
- Three boards are maintained in parallel: encoder unit, ESP unit, and PSU.

## Current Directory Contents

### `PCBs/`

Altium PCB layout files (`.PcbDoc`):

- `Encoder Unit.PcbDoc`
- `ESP unit.PcbDoc`
- `PSU.PcbDoc`

These files contain board-level implementation details such as footprint placement, copper routing, and rule-driven physical layout.

### `Schematics/`

Altium schematic files (`.SchDoc`):

- `Encoder Unit.SchDoc`
- `ESP unit.SchDoc`
- `PSU.SchDoc`

These files define logical connectivity, component values, and net naming used as the source for board updates.

## Notes

- This folder currently stores source design files only.
- Manufacturing exports (Gerbers, drill files, and BOM exports) are not currently committed in this directory.

## Recommended Workflow

1. Update circuit intent in `.SchDoc` files.
2. Synchronize to corresponding `.PcbDoc` files.
3. Run ERC/DRC in Altium before export.
4. Generate fabrication outputs (Gerber, NC drill, pick-and-place, BOM) into a versioned export folder.

Copyright (c) 2025 AuraPlus.
All rights reserved.
