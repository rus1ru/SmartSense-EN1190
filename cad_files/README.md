# SmartSense CAD Files

This folder contains the mechanical design assets for the SmartSense enclosure and integration.

## Design Intent

The CAD package covers:

- Plug-side enclosure geometry.
- Encoder-side front/back housings.
- Assembly-level fit verification.
- Manufacturing-ready STL exports.
- PCB-mechanical integration via STEP references.

## Current Directory Contents

### Assemblies

SolidWorks assembly files (`.SLDASM`):

- `Assembly_Back.SLDASM`
- `Assembly_Front.SLDASM`
- `Assembly_Full.SLDASM`
- `Assembly_Knob.SLDASM`

Use these to validate part mating, clearances, and overall stack-up before print/export.

### Parts

SolidWorks part files (`.SLDPRT`):

- `Encoder_Back.SLDPRT`
- `Encoder_Front.SLDPRT`
- `Plug_back.SLDPRT`
- `Plug_cover.SLDPRT`
- `Plug_front.SLDPRT`
- `Plug_In.SLDPRT`

These are the editable source models for dimensional changes, mounting updates, and tolerance adjustments.

### Drawings

DXF exports:

- `Assem2.DXF`
- `Assem3.DXF`
- `Assem4.DXF`

DXF files are suitable for 2D review and downstream fabrication workflows that require planar profiles.

### Manufacturing

Printable manufacturing files (`.STL`):

- `Encoder_Back.STL`
- `Encoder_Front.STL`
- `Plug_Back.STL`
- `Plug_Cover.STL`
- `Plug_Front.STL`

These are triangulated meshes intended for slicing and 3D printing.

### PCB Step Files

PCB integration geometry (`.step`):

- `encoder_lcd_pcb_5.step`
- `power_unit_board_pcb_new.step`
- `Power_Unit_ESP_PCB.step`

STEP files are used to check board-to-enclosure fit and connector alignment in assemblies.

### Sketches

- `Assem3.png`

### Vizualize

- `Encoder.png`
- `Plug_Unit_Front.png`
- `Plug_Unit_Front.svpj`

## Notes

- Naming currently uses mixed capitalization in some files (`Plug_Back` vs `Plug_back`).
- Keep assembly-to-part naming aligned when adding new revisions.
- Recommended workflow: edit `.SLDPRT` -> validate in `.SLDASM` -> export updated `.STL` and `.DXF` as needed.

Copyright (c) 2025 AuraPlus.
All rights reserved.
