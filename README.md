# ecotone-labs-ui

Shared JUCE design system — color tokens, embedded fonts, and LookAndFeel overrides used across Ecotone Labs projects.

## What's in here

- **17 color tokens** (`bg`, `surface`, `accent`, `textHi`, `hairline`, …) as static `juce::Colour` methods
- **3 embedded fonts**: JetBrains Mono Regular, JetBrains Mono Medium, Instrument Serif Italic
- **Font helpers**: `serifFont(size)`, `monoFont(size, medium)` — static, lazy-loaded
- **JUCE LookAndFeel_V4 overrides**: buttons, sliders (linear + rotary), tabs, toggle buttons, scrollbars, dialogs

## Consuming via CMake FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(
    EcotoneLabsUI
    GIT_REPOSITORY https://github.com/esoterydactyl/ecotone-labs-ui.git
    GIT_TAG        v2.0.0   # ← bump this line to update
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(EcotoneLabsUI)

target_link_libraries(MyApp PRIVATE EcotoneLabsUI)
```

Then in any source file:

```cpp
#include "EcotoneLookAndFeel.h"

// Color tokens
g.setColour(EcotoneLookAndFeel::accent());

// Fonts
g.setFont(EcotoneLookAndFeel::serifFont(20.0f));
g.setFont(EcotoneLookAndFeel::monoFont(11.0f, /*medium=*/true));

// Apply as the app LookAndFeel
EcotoneLookAndFeel laf;
juce::LookAndFeel::setDefaultLookAndFeel(&laf);
```

## Updating

Change the `GIT_TAG` line to the new version, then clear the FetchContent cache and reconfigure:

```bash
rm -rf build/_deps/ecotonelab*
cmake -B build
```

## Requirements

- CMake 3.22+
- C++17
- JUCE 8.x (fetched automatically if not already provided by the parent project)
