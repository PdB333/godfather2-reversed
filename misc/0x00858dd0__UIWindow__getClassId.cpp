// FUNC_NAME: UIWindow::getClassId
// Address: 0x00858dd0
// This function takes a UIWindow object (assumed __thiscall) and returns an index into a static table of window class names.
// The window's class name is stored at offset +0x70 (as a char*). The table is an array of 8-byte structures (name pointer + unknown int).
// Returns 0-7 on match, 0xFFFFFFFF if not found or null pointer.

#include <string.h>  // for __stricmp

// Structure for entries in the window class name table (size 8 bytes)
struct WindowClassEntry {
    char* name;      // +0x00
    int   unknown;   // +0x04 (unused in this function)
};

// External reference to the static table (located at 0x00e54078 in the binary)
extern WindowClassEntry g_windowClassTable[8];  // at least 8 entries

uint __thiscall getClassId(int this) {
    if (this == 0) {
        return 0xFFFFFFFF;
    }

    char* className = *(char**)(this + 0x70);  // +0x70: pointer to the class name string
    uint index = 0;

    do {
        char* tableName = g_windowClassTable[index].name;
        // Compare strings: if both non-null use case-insensitive compare, else use address order
        if (className == 0 || tableName == 0) {
            // Pointer comparison (address ordering) when one is null
            if (className <= tableName) {
                if (className < tableName)
                    continue; // Actually this logic is flawed; but keep as original
                else
                    goto found;
            }
        } else {
            int cmp = __stricmp(className, tableName);
            if (cmp == 0) {
found:
                return index;
            }
        }
        index++;
        if (index > 7) {
            return 0xFFFFFFFF;
        }
    } while (true);
}