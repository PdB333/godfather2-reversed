// FUNC_NAME: DebugManager::debugPrintf
// Address: 0x00609810
// Role: Central debug logging function that formats and outputs debug messages with conditional flags based on stream type.
// This is likely part of the EARS engine's debug/logging subsystem.

// Globals - defined elsewhere
extern uint32_t g_debugStreamCount; // 0x011f3910 - number of active debug stream entries
extern uint8_t g_debugStreamArray[]; // 0x011a0f28 - array of 0x38-byte entries
extern void* g_pDebugManager; // 0x01205750 - pointer to DebugManager singleton
extern const char* g_debugFormatString; // 0x011d91d8 - format string for output
extern void* g_debugArg1; // 0x01205748
extern void* g_debugArg2; // 0x00f15a68
extern void* g_debugArg3; // 0x0120574c

// Struct for a debug stream entry (0x38 bytes)
struct DebugStreamEntry {
    uint8_t unknown[8];  // +0x00
    int32_t type;        // +0x08 - stream type identifier (e.g., 0x1a, 0x1d)
    uint8_t data[0x30];  // +0x0C to +0x38
};

// DebugManager vtable layout (assumed)
class DebugManager {
public:
    virtual void log(int level, const char* format, uint32_t flags, void* arg1, void* arg2, void* arg3) = 0; // vtable+0xAC
};

void DebugManager::debugPrintf(uint fieldId)
{
    uint32_t uVar2 = (fieldId >> 3) & 2 | (uint32_t)((fieldId & 0xf) != 0);

    DebugStreamEntry* entry = nullptr;
    if (g_debugStreamCount < 0x1000) {
        entry = (DebugStreamEntry*)(g_debugStreamArray + g_debugStreamCount * 0x38);
    }

    // If entry is valid and type is one of the special stream types, add an extra flag
    if (entry && (entry->type == 0x1a || entry->type == 0x1d)) {
        uVar2 |= (fieldId >> 3) & 4;
    }

    // Call the virtual log method on the DebugManager
    // (*(code **)(*g_pDebugManager + 0xAC))(g_pDebugManager, 1, g_debugFormatString, uVar2, g_debugArg1, g_debugArg2, g_debugArg3);
    DebugManager* mgr = reinterpret_cast<DebugManager*>(g_pDebugManager);
    mgr->log(1, g_debugFormatString, uVar2, g_debugArg1, g_debugArg2, g_debugArg3);
}