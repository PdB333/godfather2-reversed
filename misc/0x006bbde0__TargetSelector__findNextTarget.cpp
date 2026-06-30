// FUNC_NAME: TargetSelector::findNextTarget
// Function address: 0x006bbde0
// Role: Iterates over a list of entity IDs, checks validity, and selects the next target based on flags and a remaining selection budget.

#include <cstdint>

// Forward declarations of helper functions (addresses from callee list)
bool isEntityValid();                        // 0x007912e0 – returns true if entity can be considered
void* getEntityContextFromCurrent();         // 0x00791540 – returns a context/owner pointer
bool isEntityInteractable(int entityId);     // 0x006bbcf0 – checks whether the entity is interactable
void onTargetSelected(int entityId, int selectionFlags); // 0x00791250 – called when target is chosen

// State structure held by this->param_1 (derived from param_1 fields)
struct TargetIteratorState {
    int*     containerPtr;      // +0x00: pointer to the container's data array (array of entity IDs)
    int*     containerHeader;   // +0x04: pointer to container header (contains count at +0x04)
    uint32_t maxSelections;     // +0x08: maximum number of selections allowed in this batch
    uint32_t currentIndex;      // +0x0C: current index into the container array
    uint32_t processedCount;    // +0x10: how many entities have been processed so far
};

// Main function
char __thiscall TargetSelector::findNextTarget(void* thisPtr, int* ioRemainingSelections) {
    TargetIteratorState* state = static_cast<TargetIteratorState*>(thisPtr);
    int* remaining = ioRemainingSelections;
    char found = 0x00; // bool: whether a valid target was selected

    // Loop while there are still items in the container
    while (state->currentIndex < *(uint32_t*)(state->containerHeader + 1)) {
        // If we've already reached the maximum number of selections, abort
        if (state->processedCount >= state->maxSelections) {
            return found;
        }
        // If a target was previously found in this call, return it immediately
        if (found != 0x00) {
            return found;
        }

        // Grab the entity ID from the container array
        int entityId = *(int*)(*(int*)state->containerPtr + state->currentIndex * 4);
        state->currentIndex++; // advance index

        // Pre‑validity checks (FUN_007912e0 returns 0 if entity is valid? We assume return 0 means valid)
        if (isEntityValid() != 0) { // If not valid, skip
            continue;
        }

        // Check entity flags at offset 0x5C
        uint32_t flags = *(uint32_t*)(entityId + 0x5C);
        if ((flags & 0x60000) != 0) {          // Bit 17 or 18 set?
            continue;
        }
        if ((flags >> 0x14) & 1) {             // Bit 20 set?
            continue;
        }
        if ((flags >> 0x1A) & 1) {             // Bit 26 set?
            continue;
        }

        // Get current context/owner (FUN_00791540 returns a pointer or NULL)
        void* context = getEntityContextFromCurrent();
        if (context == nullptr) {
            continue;
        }

        // Check a second flag set at context offset 0x84
        uint32_t contextFlags = *(uint32_t*)((int)context + 0x84);
        if ((~(contextFlags >> 5) & 1) != 0) { // Bit 5 inverted?
            continue;
        }

        // Now perform the per‑entity interactability check
        bool entityInteractable = isEntityInteractable(entityId);
        if (!entityInteractable) {
            // Not interactable – but still count it if there are remaining selections
            if (*remaining != 0) {
                state->processedCount++;
                (*remaining)--;
                found = 0x01;
                onTargetSelected(*(int*)state->containerPtr, -1); // what does -1 mean?
            }
        } else {
            // Interactable – always count it
            state->processedCount++;
            found = 0x01;
        }
    }
    return found;
}