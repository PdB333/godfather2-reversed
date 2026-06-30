// FUNC_NAME: CounterManager::modifyCounter
#include <cstddef>

// Global pointer to the counter manager singleton (DAT_01223428)
static void* gCounterManager = reinterpret_cast<void*>(0x01223428); // Address of the global variable

// Forward declarations of called functions (unknown names, guessed based on context)
void updateCounterAtIndex(void* manager, int index); // FUN_00442240
void onCounterCheck(); // FUN_00442220

// This function modifies a counter value associated with an index (passed in EAX).
// param_1 (unused) – likely a this pointer from __fastcall, but ignored.
// param_2 – operation code: 0=Add, 1=Subtract, 2=Set, 3=Check
// param_3 – value to use for the operation
// The index is passed in the EAX register (in_EAX) – assumed to be valid.
void __fastcall CounterManager::modifyCounter(void* /*unused*/, int operation, int value) {
    // in_EAX is the implicit index (from register)
    // For reconstruction, we treat it as an explicit argument.
    // In the actual binary, it is passed via EAX.
    int index; // will be set externally (e.g., from a loop)

    // Bounds check using the manager's data
    int maxCount = *reinterpret_cast<int*>(static_cast<char*>(gCounterManager) + 0x20);
    if (index < 0 || index >= maxCount) {
        return; // out of bounds
    }

    // Get the pointer to the array of elements (size 0x14 each)
    char* arrayBase = *reinterpret_cast<char**>(static_cast<char*>(gCounterManager) + 0x24);
    // Access the value at offset +0x08 within the element at index
    int* valuePtr = reinterpret_cast<int*>(arrayBase + 8 + index * 0x14);

    switch (operation) {
    case 0: // Add
        *valuePtr += value;
        updateCounterAtIndex(gCounterManager, index); // update display/state
        break;
    case 1: // Subtract
        *valuePtr -= value;
        updateCounterAtIndex(gCounterManager, index);
        break;
    case 2: // Set
        *valuePtr = value;
        updateCounterAtIndex(gCounterManager, index);
        break;
    case 3: // Check (trigger if non-zero or zero)
        if (*valuePtr != 0) {
            onCounterCheck(); // trigger some event
            return;
        }
        // Fall through: always calls onCounterCheck regardless (bug? or intentional)
        onCounterCheck();
        break;
    }
}