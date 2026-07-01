// FUNC_NAME: ObjectiveManager::SetStatus
// Address: 0x0096bff0
// This function updates the status of the current objective based on an internal state machine.
// It checks if the manager is active (field +0xdc == 1), then computes an index from two counters
// (+0xd4 and +0xc4). It validates against a count at +0x17c and retrieves an element from an array at +0x178.
// Then it uses a linked list (starting at the element's +0x100 offset) via getListHead/updateListStatus helpers
// to determine and set the new status (0=complete, 1=active/running). It also logs via debug functions.

#include <cstdint>

class ObjectiveManager {
public:
    void SetStatus();

    // Fields (inferred offsets from decompilation, not complete)
    // +0x60: some value (e.g., timer or ID)
    // +0xc4: offset counter 1
    // +0xd4: offset counter 2
    // +0xdc: state flag (1 = active)
    // +0x108: current objective status (0/1)
    // +0x10c: current objective index
    // +0x178: pointer to array of element pointers
    // +0x17c: size of array
    // +0x184: status update structure (first 4 bytes pointer, next 4 bytes status)
    // etc.
};

// Forward declarations of helper functions
// These are likely part of an internal list/container utility
void __fastcall getListHead(int* outNode, uint32_t* listPtr);  // FUN_00968e40
void __fastcall updateListStatus(int* statusPtr, uint32_t* listPtr); // FUN_00968ea0
void __fastcall debugPrint(const char* format, int param1, int param2, int param3); // FUN_008b60e0
void __fastcall logSetStatus(const char* name, int zero, const char* statusString, int anotherZero); // FUN_005a04a0

void ObjectiveManager::SetStatus() {
    // Check if objective system is active
    if (*(reinterpret_cast<int*>(this) + 0xdc / 4) != 1) {
        return;
    }

    uint32_t currentIndex = *(reinterpret_cast<int*>(this) + 0xd4 / 4) + *(reinterpret_cast<int*>(this) + 0xc4 / 4);
    uint32_t arrayCount = *(reinterpret_cast<uint32_t*>(this) + 0x17c / 4);

    // Validate index against array bounds
    if (arrayCount == 0 || currentIndex >= arrayCount) {
        return;
    }

    // Get pointer to the element at currentIndex from the array
    int* elementPtr = reinterpret_cast<int*>(
        *(reinterpret_cast<int*>(this) + 0x178 / 4) + currentIndex * 4
    );

    // Pointer to list head inside the element (offset +0x100)
    uint32_t* listHead = reinterpret_cast<uint32_t*>(elementPtr + 0x100 / 4);

    // Output structure for status update (at this+0x184)
    int* statusOutput = reinterpret_cast<int*>(this) + 0x184 / 4;

    int nodePtr;  // Will hold a node from the list
    getListHead(&nodePtr, listHead);

    if (nodePtr != 0) {
        int statusValue;
        // Check node's type field at offset +4
        if (*reinterpret_cast<int*>(nodePtr + 4) == 1) {
            statusValue = 0;  // objective complete
        } else {
            statusValue = 1;  // objective active/running
            if (*reinterpret_cast<int*>(nodePtr + 4) != 0) {
                // Prepare debug values from element (offsets +0xf0 and +0xf4)
                int debugVal1 = *reinterpret_cast<int*>(elementPtr + 0xf0 / 4);
                int debugVal2 = *reinterpret_cast<int*>(elementPtr + 0xf4 / 4);
                debugPrint(reinterpret_cast<const char*>(0x00962f40), &debugVal1, *listHead, *(reinterpret_cast<int*>(this) + 0x60 / 4), 10000);
            }
        }

        // Update objective status and index
        *(reinterpret_cast<int*>(this) + 0x108 / 4) = statusValue;
        *(reinterpret_cast<int*>(this) + 0x10c / 4) = currentIndex;

        // Log the status change
        logSetStatus("SetStatus", 0, reinterpret_cast<const char*>(0x00d8cdec), 0);

        // Update the list node status via helper
        updateListStatus(statusOutput, listHead);
        *(statusOutput + 1) = statusValue; // set statusOutput[1] (offset +4 from statusOutput start)
    }
}