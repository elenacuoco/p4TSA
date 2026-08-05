---
mode: ask
description: Review changes in the p4TSA C++/pybind11 library for correctness, build impact, test coverage, and API stability.
---

Review the current change set in this repository as if you were preparing a code review for p4TSA.

Focus on:
- correctness and numerical stability in the C++ core
- pybind11 binding changes and Python compatibility
- build and packaging impact, including native dependencies and CMake changes
- regressions in wavelet, WDF, or persistence-related logic
- missing or weak tests and any risky assumptions

Provide a concise review with findings, severity, and suggested next actions.
