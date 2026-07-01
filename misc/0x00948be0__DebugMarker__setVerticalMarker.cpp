// FUNC_NAME: DebugMarker::setVerticalMarker
// Address: 0x00948be0
// Role: Sets a vertical marker debug display for an object, printing its ID and marker type (above/below/unknown).

#include <cstdio>

class DebugMarker {
public:
    // +0x00: unsigned int markerId (printed as %u)
    // +0x08: unknown field at offset 2 (param_1+2)
    // +0x78: int markerType (1=above, 2=unknown, 3=below, else=unknown)
    unsigned int markerId;
    int unknownField2; // offset 0x08
    int markerType;    // offset 0x78

    int setVerticalMarker();
};

// External debug/log function (FUN_005a04a0)
// Parameters: command string, unknown, constant, count, data pointer, formatted string, marker type string
extern void debugOutput(const char* command, int arg1, const void* constant, int count, void* data, const char* formatted, const char* markerType);

// Global string pointers for marker types
extern const char* g_markerAbove;   // PTR_s_above_00e56a5c
extern const char* g_markerUnknown; // PTR_DAT_00e56a70
extern const char* g_markerBelow;   // PTR_s_below_00e56a74
extern const char* g_markerDefault; // PTR_DAT_00e56a58

int DebugMarker::setVerticalMarker() {
    const char* markerTypeStr;
    char buffer[12]; // local_c

    // Select marker type string based on markerType field
    if (markerType == 1) {
        markerTypeStr = g_markerAbove;
    } else if (markerType == 2) {
        markerTypeStr = g_markerUnknown;
    } else if (markerType == 3) {
        markerTypeStr = g_markerBelow;
    } else {
        markerTypeStr = g_markerDefault;
    }

    // Format the marker ID as unsigned integer
    snprintf(buffer, 10, "%u", markerId);

    // Call debug output with "SetVertMarker" command
    // Parameters: command, 0, some constant (DAT_00d8b2cc), 3, pointer to unknownField2, formatted ID, marker type string
    debugOutput("SetVertMarker", 0, &DAT_00d8b2cc, 3, &unknownField2, buffer, markerTypeStr);

    return 2; // Return status code (likely success)
}