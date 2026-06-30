// FUNC_NAME: processProfileEntries
// Function at 0x006944a0: Processes an array of profile entries (type 0/1), 
// formats them into a log string, and initializes a configuration object.
// Uses global g_entryCount (DAT_01129d24), g_initializedFlag (DAT_01129d28),
// and g_entryArray (starting at DAT_01129d34 with stride 5 ints per entry).

#include <cstdint>

// Forward declarations of engine functions (reconstructed names)
void debugPrintf(int context, char* outBuf, const char* fmt, uint32_t a, uint32_t b);
void beginLogGroup();
void logString(uint32_t tagId, const char* str);
void logInteger(uint32_t tagId, int val);
void formatString(int context, char* buf, int* outLen, const char* fmt, uint32_t hash);
void outputString(int len, int unk, int buf);
void endLogGroup();
void* allocateMemory(uint32_t size);  // FUN_009c8e50
int getProfileObject(int index);      // FUN_00982280
void setProfileName(void* obj, const char* name); // FUN_00981eb0
void finalizeProfileConfig();         // FUN_00982e10

extern int g_entryCount;      // DAT_01129d24
extern char g_initializedFlag; // DAT_01129d28

// Entry structure: 5 ints (20 bytes)
struct ProfileEntry {
    int type;          // 0 or 1
    const char* name;  // pointer at offset 4
    int pad[3];        // remaining 12 bytes
};

extern ProfileEntry g_entryArray[]; // array at DAT_01129d34, bounded by 0x1129d84

void processProfileEntries() {
    if (g_entryCount == 0 || g_initializedFlag != 0) {
        return;
    }

    char* resultString = nullptr;
    int resultLen = 0;
    int resultCapacity = 0;
    int resultUnk = 0;
    void (*resultDeleter)(char*) = nullptr;

    // First formatted string: two numbers with unknown meaning
    debugPrintf(0x12234a4, &resultString, "{#%u}\n\n{#%u}\n\n", 0x76cd4f26, 0x76cd4f27);

    int count = 0; // tracks how many entries of current type found
    int currentType = 0;
    while (currentType < 2 && count < g_entryCount) {
        // Iterate through the entry array (5-element stride)
        ProfileEntry* entry = g_entryArray; // starting at DAT_01129d34
        while ((intptr_t)entry < 0x1129d84) { // end address magic
            if (entry->type == currentType) {
                uint32_t hash;
                if (currentType == 0) {
                    hash = 0xcb339725;
                } else if (currentType == 1) {
                    hash = 0xfde88b79;
                } else {
                    goto skipEntry;
                }

                // Log this entry
                int logBuf[4] = {0, 0, 0, 0};
                beginLogGroup();
                const char* name = entry->name;
                if (name == nullptr) {
                    name = ""; // DAT_0120546e
                }
                logString(101, name);
                count++;
                logInteger(110, count);
                formatString(0x12234a4, (char*)logBuf, logBuf, "{#%u}\n", hash);
                outputString(logBuf[0], 0, logBuf[1]);
                endLogGroup();
                if (logBuf[0] != 0) {
                    ((void(*)(int))logBuf[3])(logBuf[0]); // call destructor
                }
            }
skipEntry:
            if (count == 4 || count == g_entryCount) {
                break;
            }
            entry++; // advance by 5 ints
        }
        currentType++;
    }

    // Final summary line
    int finalBuf[4] = {0, 0, 0, 0};
    beginLogGroup();
    logInteger(100, count);
    logInteger(101, g_entryCount);
    formatString(0x12234a4, (char*)finalBuf, finalBuf, "\n{#%u}", 0xe4c9f9d9);
    outputString(finalBuf[0], 0, finalBuf[1]);

    // Allocate a configuration object
    void* obj = allocateMemory(0xf0);
    int profileIndex = 0;
    if (obj != nullptr) {
        profileIndex = getProfileObject(0);
    }

    const char* nameForObj = resultString;
    if (resultString == nullptr) {
        nameForObj = "";
    }
    setProfileName((void*)(intptr_t)profileIndex, nameForObj);
    *(int*)((intptr_t)profileIndex + 0xc) = 7; // magic number

    finalizeProfileConfig();

    // Reset globals
    g_entryCount = 0;
    g_initializedFlag = 1;

    endLogGroup();

    if (finalBuf[0] != 0) {
        ((void(*)(int))finalBuf[3])(finalBuf[0]);
    }
    if (resultString != nullptr) {
        ((void(*)(char*))resultDeleter)(resultString);
    }
}