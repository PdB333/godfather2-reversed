// FUNC_NAME: ControllerSlot::update
// Function address: 0x005861c0
// Reconstructed C++ for The Godfather 2 (EARS engine)
// Handles controller input processing and transform update

#include <cstdint>

// Forward declarations
class InputManager;
struct InputState; // 12 bytes: 8 bytes timestamp + 4 bytes buttons

// Action map structure (pointed by this+0x34)
struct ActionMap {
    uint8_t pad_0x00[0x10]; // +0x00
    uint8_t m_useLocalCopy; // +0x10: if non-zero, always use original input
    uint8_t m_actionTypes[]; // +0x14: array of action type bytes (0x02 = analog)
};

// Action map info structure (pointed by this+0x38)
struct ActionMapInfo {
    uint8_t pad_0x00[0x0C]; // +0x00
    int32_t m_actionCount;   // +0x0C: number of actions to process
};

// Controller slot class (size unknown, but offsets used)
class ControllerSlot {
public:
    // +0x00: vtable? (not used here)
    // +0x10: transform data (8 int32s, e.g., position + orientation)
    int32_t m_transform[8]; // +0x10 to +0x2C
    uint8_t m_state;        // +0x30: state flag (2 = active/updated)
    uint8_t pad_0x31[3];    // padding
    ActionMap* m_actionMap; // +0x34: pointer to action mapping
    ActionMapInfo* m_actionMapInfo; // +0x38: pointer to action count info

    // Member function: update this controller slot with input data
    // param_2: pointer to input state (12 bytes)
    // param_3: flags (bit 2 = skip input processing, bit 3 = skip transform copy)
    int32_t update(InputState* inputState, uint8_t flags);
};

// External functions (from other modules)
extern InputManager* getInputManager(); // FUN_0056fdd0
extern void beginInputUpdate();         // FUN_0056f620
extern void processControllerInput(ControllerSlot* slot); // FUN_0056f800
extern void applyInput(InputState* state); // FUN_00583640

int32_t ControllerSlot::update(InputState* inputState, uint8_t flags) {
    InputManager* manager = getInputManager();
    if (this == nullptr || manager == nullptr) {
        return 0;
    }

    // Process input if flag bit 2 is not set
    if ((flags & 4) == 0) {
        beginInputUpdate();
        processControllerInput(this);

        int32_t actionCount = m_actionMapInfo->m_actionCount;
        ActionMap* actionMap = m_actionMap;

        if (manager->m_useDirectInput == 0) { // manager+0x3c
            // Per-action type processing
            uint8_t* actionTypePtr = &actionMap->m_actionTypes[0];
            if (actionMap->m_useLocalCopy == 0) {
                // Use local copy for analog actions (type 0x02)
                for (int32_t i = 0; i < actionCount; i++) {
                    InputState localState;
                    localState.timestamp = inputState->timestamp; // 8 bytes
                    localState.buttons = inputState->buttons;     // 4 bytes
                    if (*actionTypePtr == 0x02) {
                        applyInput(&localState);
                    }
                    actionTypePtr++;
                }
            } else {
                // Always use original input
                for (int32_t i = 0; i < actionCount; i++) {
                    applyInput(inputState);
                }
            }
        } else {
            // Direct mode: always use original input for all actions
            uint8_t* actionTypePtr = &actionMap->m_actionTypes[0];
            if (actionMap->m_useLocalCopy == 0) {
                for (int32_t i = 0; i < actionCount; i++) {
                    InputState localState;
                    localState.timestamp = inputState->timestamp;
                    localState.buttons = inputState->buttons;
                    if (*actionTypePtr == 0x02) {
                        applyInput(&localState);
                    }
                    actionTypePtr++;
                }
            } else {
                for (int32_t i = 0; i < actionCount; i++) {
                    applyInput(inputState);
                }
            }
        }
    }

    // Copy transform to manager if flag bit 3 is not set and state is active
    if ((flags & 8) == 0 && m_state == 2) {
        // Copy 8 int32s from this->m_transform to manager's transform buffer
        manager->m_transform[0] = m_transform[0];
        manager->m_transform[1] = m_transform[1];
        manager->m_transform[2] = m_transform[2];
        manager->m_transform[3] = m_transform[3];
        manager->m_transform[4] = m_transform[4];
        manager->m_transform[5] = m_transform[5];
        manager->m_transform[6] = m_transform[6];
        manager->m_transform[7] = m_transform[7];
        manager->m_state = 2; // Set manager state to active
    }

    return reinterpret_cast<int32_t>(manager);
}