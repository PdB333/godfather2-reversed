// FUNC_NAME: EntityStateMachine::updateFromInput

// Address: 0x004e79d0
// Role: Main update function for entity state machine. Processes incoming input (param_2) and determines whether to send an action event or handle the current state via a state machine switch.

#include <cstdint>

// Forward declarations of helper functions
extern bool parseInput(void* inputStruct, float* outPosition, void* outUnknown); // FUN_004e62a0
extern void handleStateIdle(EntityStateMachine* self, float* position); // FUN_004e56c0 (cases 0,1,6,7,0xd,0x10)
extern void handleStateWalking(EntityStateMachine* self, float* position); // FUN_004e55c0 (case 5)
extern void handleStateRunning(EntityStateMachine* self, float* position); // FUN_004e5890 (case 0xb)
extern void handleStateCrouching(EntityStateMachine* self, float* position, void* unknown); // FUN_004e5790 (cases 8,10,0xc)
extern void handleStateDiving(EntityStateMachine* self, float* position); // FUN_004e56c0? Actually mapped elsewhere but reused
extern void handleStateClimbing(EntityStateMachine* self, float* position); // FUN_004e56c0?
extern void handleStateSpecial1(EntityStateMachine* self, float* position); // case 2
extern void handleStateSpecial2(EntityStateMachine* self, float* position); // case 3
extern void handleStateSpecial3(EntityStateMachine* self, float* position); // case 4
extern void handleStateSpecial4(EntityStateMachine* self, float* position); // case 0xe
extern void handleStateSpecial5(EntityStateMachine* self, float* position); // case 0xf

// Known global variables
extern uint32_t g_actionAllowTable[16]; // DAT_01194738 - allows action sending based on state index
extern uint8_t g_globalFlag; // DAT_011947e4
extern int* g_eventManager; // DAT_01206880 - pointer to some event manager, used at offset +0x14 for message queue

// Struct representing the inner state info
struct StateInfo {
    uint8_t stateIndex; // +0x10: current state (0-16)
    uint8_t unknownByte; // +0x11: used in flag check
    uint16_t pad[1]; // alignment
    uint32_t flags; // +0x14: bitfield flags (0x40, 0x200, etc.)
    float posX; // +0x40
    float posY; // +0x44
    float posZ; // +0x48
    float scalar; // +0x4c: often used as a parameter
    // possibly more fields...
};

// Struct representing the entity state machine
struct EntityStateMachine {
    uint32_t vtable; // +0x00
    void* worldObject; // +0x04: pointer to some world object (e.g., a character)
    int32_t animIndex; // +0x10: index used for animation blending
    StateInfo* stateInfo; // +0x24: pointer to current state data
    float speedScaling; // +0x2c: speed multiplier
    uint8_t sendFlag; // +0x5c: flag indicating we are sending an event (0 or 1)
};

// Helper: send an event message to the global event manager
void sendEvent(uint32_t eventId, void* object) {
    int* queuePtr = *(int**)(g_eventManager + 0x14); // get current write pointer
    **(uint32_t**)queuePtr = eventId; // write event ID
    queuePtr++;
    *queuePtr = (int)object; // write object pointer
    queuePtr++;
    // update global write pointer (not shown, but implied by pointer increment)
}

void __thiscall EntityStateMachine::updateFromInput(void* inputStruct) {
    bool canSend = true;

    StateInfo* state = this->stateInfo;

    // First check: if flag & 0x40 is set, verify that the world object's target is valid
    if (state->flags & 0x40) {
        void* target = *(void**)((uint8_t*)this->worldObject + 0x20);
        if (target) {
            target = (void*)((intptr_t)target + 4); // increase ref count?
        }
        target = (void*)checkTargetValid(target); // FUN_004e8550
        if (target != nullptr && !isActionBlocked()) { // FUN_004e4230 returns false -> action not blocked
            canSend = false;
        }
    }
    else {
        // Flag & 0x40 not set: check flag & 0x200 and a byte from state
        if (state->flags & 0x200) {
            uint8_t byte11 = state->unknownByte;
            if (byte11 != 0 && g_globalFlag != 0 && (g_globalFlag & byte11) == 0) {
                canSend = false;
            }
        }
    }

    // Parse input into a position and some extra data
    float position[4]; // + local_a0 (x,y,z,w)
    uint8_t extraData[28]; // local_20
    if (!parseInput(inputStruct, position, extraData)) {
        canSend = false;
    }

    // Decide whether to send a "stopped" event or continue with state processing
    if ((state->stateIndex < 0x11 && g_actionAllowTable[state->stateIndex] != 0) || !canSend) {
        // Stop sending event if we were
        if (this->sendFlag) {
            this->sendFlag = 0;
            // Send event to event manager
            uint32_t eventId;
            if (state->stateIndex == 11) { // 0x0b
                eventId = (uint32_t)&PTR_LAB_01124b1c; // event ID for "stopped"?
            } else {
                eventId = (uint32_t)&PTR_LAB_01124b6c; // generic event?
            }
            sendEvent(eventId, this);
        }
    } else {
        // Set send flag to 1 so we can send event next time we stop
        this->sendFlag = 1;

        // Process current state via a state machine switch
        switch (state->stateIndex) {
            case 0: case 1: case 6: case 7: case 13: case 16:
                handleStateIdle(this, position);
                break;
            case 2:
                handleStateSpecial1(this, position);
                break;
            case 3:
                if (this->worldObject != nullptr && *(int*)((uint8_t*)this->worldObject + 0xc4) != 0x48) {
                    // some preparation and call special handler
                    doSomething(); // FUN_004e6720
                    handleStateSpecial2(this, position, someParam);
                }
                break;
            case 4:
                handleStateSpecial3(this, position);
                break;
            case 5:
                handleStateWalking(this, position);
                break;
            case 8: case 10: case 12:
                handleStateCrouching(this, position, extraData);
                break;
            case 11:
                handleStateRunning(this, position);
                break;
            case 14:
                handleStateSpecial4(this, position);
                break;
            case 15:
                handleStateSpecial5(this, position);
                break;
            default:
                break;
        }
    }
}