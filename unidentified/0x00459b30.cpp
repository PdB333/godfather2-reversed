// FUN_NAME: StateMachine::setState

#include <cstdint>

// Constants for state values (reversed from DAT_0110ab30 and DAT_0110ab2c)
const int NEW_STATE = 0x0110ab30;
const int OLD_STATE = 0x0110ab2c;

// Internal helper forward declarations
void resetSubObject();        // FUN_00417560
int notifyStateChange();      // FUN_00459a10
void playSound(int addr);     // FUN_00459280

// Sub-object structure (size 0xB0)
struct SubObject {
    char unknown[6];
    char aliveFlag;            // +0x06
    char pad[0xB0 - 7];
};

// State data structure (pointed to by this + 0x50)
struct StateData {
    uint32_t flags;                // +0x24 (bit 0x80 = hierarchical parenting)
    uint8_t toggleByte;            // +0x2D
    uint8_t padding2E;             // +0x2E
    uint8_t wasOldState;           // +0x2F (bool)
    int32_t currentState;          // +0x30
    int32_t subCount;              // +0x34
    SubObject* subArray;           // +0x50 (pointer to array of SubObject)
    void* parentObject;            // +0x98 (pointer to another state data for hierarchy)
    void* hasSubObjects;           // +0x74 (non-zero indicates sub-objects exist)
    // rest of fields...
};

// Main object structure (this)
struct StateMachine {
    char unknown6;                 // +0x06 (checked for bool)
    char pad[0x4C - 0x07];
    void* soundHandlePtr;          // +0x4C (pointer to something with +4 offset)
    StateData* stateData;          // +0x50
};

int __thiscall StateMachine::setState(bool param_2) {
    StateData* sd = this->stateData;                        // param_1 + 0x50
    int result = 0;

    if (sd->currentState != NEW_STATE) {
        bool wasOld = (sd->currentState == OLD_STATE);     // bVar5
        sd->currentState = NEW_STATE;
        sd->wasOldState = (uint8_t)wasOld;
        sd->toggleByte ^= 1;                               // flip bit

        if (sd->flags & 0x80) {
            // Parented object: sync toggle with parent
            uint8_t* parentToggle = (uint8_t*)((uint8_t*)sd->parentObject + 0x2D);
            *parentToggle ^= 1;
            sd->toggleByte = *parentToggle;
        }

        sd->padding2E = 0;                                  // clear some byte

        if (sd->hasSubObjects && sd->subCount != 0) {
            for (uint32_t i = 0; i < (uint32_t)sd->subCount; i++) {
                // Stride 0xB0 per sub-object
                SubObject* sub = &sd->subArray[i];
                if (sub->aliveFlag == 0) {
                    resetSubObject();                       // FUN_00417560
                }
            }
        }

        result = notifyStateChange();                       // FUN_00459a10
    }

    if (param_2 && this->unknown6 != 0) {
        // Calculate address from sound handle pointer chain
        int addr = *(int*)(*(int*)(this->soundHandlePtr) + 4) + 0x20;
        playSound(addr);                                    // FUN_00459280
    }

    return result;
}