// FUNC_NAME: Character::getCurrentActionDuration
// Address: 0x00442cc0
// Returns the duration of the currently active action from the action list.
// The object has a pointer at +0x6c to an action array container.
// At offset 0x10 in that container is an array of ActionData structures (each 0x14 bytes).
// The current action index is obtained via a global helper (FUN_00443d40).
// The ActionData at that index contains a pointer to another structure whose +0x18 holds the duration.

#include <cstdint>

class Character {
    // Offsets:
    // +0x6c: Pointer to ActionList (unknown type)
    // Within ActionList:
    //   +0x10: Array of ActionData entries (each 0x14 bytes)
    //   ActionData:
    //     +0x00: Pointer to ActionInfo structure
    //     ActionInfo:
    //       +0x18: Duration (float)

    int32_t* getActionList() const {
        return *(int32_t**)((uint8_t*)this + 0x6c);
    }

    // Forward declaration of global index getter
    friend int32_t getCurrentActionIndex();

public:
    // Returns the duration of the current action, or 0 if none.
    float getCurrentActionDuration() const {
        int32_t index = getCurrentActionIndex();
        if (index < 0) {
            return 0.0f;
        }

        int32_t* actionList = getActionList();
        if (actionList == nullptr) {
            return 0.0f;
        }

        // Array of ActionData starts at offset 0x10 in the action list container.
        int32_t* actionDataArray = (int32_t*)((uint8_t*)actionList + 0x10);
        // Each ActionData entry is 0x14 bytes. The first DWORD of each entry is a pointer to ActionInfo.
        int32_t* actionDataEntry = (int32_t*)((uint8_t*)actionDataArray + index * 0x14);
        // ActionInfo pointer is the first DWORD.
        int32_t* actionInfo = (int32_t*)*actionDataEntry;
        if (actionInfo == nullptr) {
            return 0.0f;
        }

        // Duration is a float at offset 0x18 in ActionInfo.
        return *(float*)((uint8_t*)actionInfo + 0x18);
    }
};

// Global helper: returns the index of the current action (-1 if none).
// Defined elsewhere at 0x00443d40.
int32_t getCurrentActionIndex();