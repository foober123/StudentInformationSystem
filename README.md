# Shrim/poll/
Desktop App for managing student information built in C++ using SDL and DearIMGUI as the frontend.

## How To Build
On Windows, SDL2 and ImGui's docking branch is bundled with the app. Simply run:
```
make windows
```

On Linux/MacOS, SDL2 must be installed in the machine that is building. Run:
```
make
```

## How to change .csv files
in `settings.h`, there are paths to colleges, programs, and students. Change those relative to data and rebuild.



