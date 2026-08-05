# AGENTS instructions for p4TSA

## Project snapshot
- p4TSA is a C++ time-series analysis library with a Python interface exposed as the pytsa module through pybind11.
- The core implementation lives in the C++ headers under [include](include) and the corresponding sources under [src](src).
- The Python-facing binding entry point is [python-wrapper/pytsa.cpp](python-wrapper/pytsa.cpp), and regression tests live under [python-wrapper/tests](python-wrapper/tests).
- The packaging/build flow is defined by [CMakeLists.txt](CMakeLists.txt), [pyproject.toml](pyproject.toml), and the installation guidance in [README.md](README.md).

## Working conventions
- Keep changes compatible with the repository’s existing C++14 style and the current pybind11 binding patterns.
- Prefer small, focused changes and preserve the current API shape unless the task explicitly requires a breaking change.
- For numerical and wavelet-related code, be conservative: these components are sensitive to regression and should be tested rather than “fixed” by intuition alone.
- When adding or changing behavior, update or add tests under [python-wrapper/tests](python-wrapper/tests) when practical.

## Build and test commands
- Configure and build the native extension:
  - `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$CONDA_PREFIX"`
  - `cmake --build build -j"$(nproc)"`
  - `cmake --install build`
- Run the Python regression tests:
  - `pytest python-wrapper/tests/ -v`
- Smoke-test the installed module:
  - `python -c "import pytsa; print(pytsa.__file__)"`

## Review priorities
- For review-oriented work, focus on correctness, build impact, test coverage, and API stability rather than style-only changes.
- Pay special attention to the C++/Python boundary, memory ownership, and any change touching wavelet transforms, WDF classification/reconstruction, or persistence logic.
- Call out missing tests, risky assumptions, and any changes that would be hard to validate without native-library availability.

## References
- Start with [README.md](README.md) for installation and dependency notes.
- Use [CMakeLists.txt](CMakeLists.txt) and [pyproject.toml](pyproject.toml) when evaluating packaging or build changes.
- Use [python-wrapper/tests](python-wrapper/tests) as the baseline for expected behavior.
