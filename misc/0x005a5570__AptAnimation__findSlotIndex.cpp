// FUNC_NAME: AptAnimation::findSlotIndex
// Function at 0x005a5570: Searches an animation slot array for a given ID. Returns index or -1. Triggers assert if not found in debug builds.
// Struct AnimationSlotList:
//   +0x0C: int slotCount
//   +0x10: int* slotIDs (array of animation IDs)

struct AnimationSlotList {
    int slotCount;       // +0x0C
    int* slotIDs;        // +0x10
};

// Static helper: find index of slotID in the list. Returns -1 if not found.
int __fastcall AptAnimation::findSlotIndex(int slotID, AnimationSlotList* pList) {
    // First, search the array linearly
    for (int i = 0; i < pList->slotCount; ++i) {
        if (pList->slotIDs[i] == slotID) {
            return i;            // Found, return index
        }
    }

    // Not found: trigger debug assert (only in debug build with global flag)
    static char assertMsg[] = ""; // DAT_00e36da0
    static const char* sourceFile = "..\\source\\Apt\\AptAnimation.cpp";
    const int sourceLine = 0xB6; // 182
    static bool assertEnabled = DAT_01128f8c; // global debug flag (0 if disabled)

    if (assertEnabled) {
        // Access thread-local storage for assertion handler
        // FS:0x2C points to thread info block, offset +0x30 contains function table
        int* fsBase = *(int**)(__readfsdword(0x2C) + 0x30); // unaff_FS_OFFSET+0x2c => read FS segment
        if (fsBase != nullptr) {
            // Call assert function from the table (offset 8)
            typedef void (*AssertFunc)(char*, const char*, int, int);
            AssertFunc assertFunc = *(AssertFunc*)(*fsBase + 8);
            assertFunc(&assertMsg, sourceFile, sourceLine, 0); // local_14, local_10, local_c, local_8
        }
        // Trigger a breakpoint if assertion fails
        __asm { int 3 }
    }

    return -1; // Not found
}