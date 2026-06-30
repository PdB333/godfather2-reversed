// FUNC_NAME: TrackingManager::findAndUpdateEntry
// Address: 0x004c9040
// Role: Finds a tracking slot in a 32-slot array by matching two keys (objectId and typeId), then updates the last 3 fields with status data.
// - typeId == 1: calls a function to get pointer to something and copies its first two ints into fields 7 and 8.
// - typeId == 2: calls a prepare function, then a buffer-filling function, and copies local fields into fields 7 and 8.
// The array is 32 entries of 5 ints each (20 bytes per entry). The keys are at offsets +16 and +20 (indices 4 and 5 of the flat array, i.e., across entry boundaries).
// Writing to fields+6,+7,+8 (indices 6,7,8 relative to entry start) accesses the next entry's first three ints.

#include <cstdint>

// Global constant set into field6
extern int g_TrackStatusInitial; // DAT_01205224

// Forward declarations of called functions
int* __fastcall getSomethingPointer();                                        // FUN_005e68f0: returns pointer to 2-int structure
void __fastcall prepareSomething();                                          // FUN_005e30c0
bool __fastcall getStatusFromBuffer(char buffer[96], int* outX, int* outY);  // FUN_005e2180: fills buffer and possibly sets outX/outY

void __fastcall TrackingManager::findAndUpdateEntry(int objectId, int typeId, int* trackArray)
{
    int index = 0;
    int* currentEntry = trackArray;

    // Search for a slot where entry[4] == objectId and entry[5] == typeId
    while (currentEntry[4] != objectId || currentEntry[5] != typeId) {
        index++;
        currentEntry += 5; // advance by one entry (5 ints)
        if (index > 31) {
            return; // no matching slot found
        }
    }

    // Found a matching slot at index
    if (index != -1) {
        // Update fields at offset 6,7,8 relative to the start of this entry
        // Note: these offsets go into the following entry (since entry size is 5)
        trackArray[index * 5 + 6] = g_TrackStatusInitial;
        trackArray[index * 5 + 7] = 0;
        trackArray[index * 5 + 8] = -1;

        if (typeId == 1) {
            int* ptr = getSomethingPointer();
            if (ptr != nullptr) {
                trackArray[index * 5 + 7] = ptr[0];
                trackArray[index * 5 + 8] = ptr[1];
                return;
            }
        }
        else if (typeId == 2) {
            char buffer[96];
            prepareSomething();
            bool success = getStatusFromBuffer(buffer, &trackArray[index * 5 + 7], &trackArray[index * 5 + 8]);
            // Note: the decompiler shows local variables iStack_c and iStack_8 being assigned,
            // but they are likely the fields set by getStatusFromBuffer via pointer parameters.
            // This reconstruction passes pointers directly.
            if (success) {
                // Already set above via pointers
            }
        }
    }
}