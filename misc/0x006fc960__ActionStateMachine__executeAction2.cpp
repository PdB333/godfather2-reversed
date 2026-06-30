// FUNC_NAME: ActionStateMachine::executeAction2
// Address: 0x006fc960
// Reconstructed C++ for x86 __thiscall function in Godfather 2 (EA EARS engine)
// This function is part of a state machine for player/mission actions, handling state 2 transition to state 3 or 6.

#include <cstdint>

// Forward declarations for called functions (addresses from Ghidra)
bool __cdecl lockMutex(void* mutex);                // 0x00ab4db0
void __cdecl unlockMutex(void* mutex);              // 0x00ab4e70
void* __cdecl findEntityByHashId(void* entityList, uint32_t hashId); // 0x006b1c70
void __cdecl playAudio(int id);                     // 0x007f97a0
bool __cdecl createActionNode(int* actionData, int param3, uint32_t someValue, bool flag1, bool flag2, bool flag3, bool flag4); // 0x0045f0c0
void __cdecl setupActionNode(int param3, int actionId); // 0x00460340
void __cdecl processAction(int* param1);            // 0x0046bae0
void __cdecl stopAudio();                           // 0x007f58b0

// External mutex for thread safety
extern void* gActionMutex; // DAT_00d60c08

// Class representing the state machine
class ActionStateMachine {
public:
    // State offsets:
    // +0x00: currentState (int)
    // +0x04: subState (int)
    // +0x08: reserved
    // +0x0C: reserved
    // +0x10: someData1 (int)  // param1[4]
    // +0x14: someData2 (int)  // param1[5]
    // +0x18: reserved
    // +0x1C: reserved
    // +0x20: actionId (int)   // param1[9]? Actually param1[9] is at offset 0x24 if int array. Let's assume offset 0x24.
    // We'll access via array indexing: this[0] = state, this[1] = subState, this[4] = someData1, this[5] = someData2, this[9] = actionId
    // Struct reconstruction:
    // int mState;            // offset 0x00
    // int mSubState;         // offset 0x04
    // int unknown[2];        // offset 0x08-0x0C
    // int mSomeData1;        // offset 0x10
    // int mSomeData2;        // offset 0x14
    // int unknown2[3];       // offset 0x18-0x20
    // int mActionId;         // offset 0x24 (index 9)

    int mState;             // +0x00
    int mSubState;          // +0x04
    int pad1[2];            // +0x08
    int mSomeData1;         // +0x10
    int mSomeData2;         // +0x14
    int pad2[3];            // +0x18
    int mActionId;          // +0x24
};

// Parameter: param2 is a pointer to a game entity (or action target)
// Parameter: param3 is an integer parameter (e.g., a context ID)
int8_t __thiscall ActionStateMachine::executeAction2(int* param2, int param3) {
    int8_t result = 0;
    lockMutex(gActionMutex);
    int* entity = param2;
    if (mState == 2) {
        if (entity != nullptr) {
            int* vtable = (int*)*entity; // entity's vtable pointer
            int* temp = nullptr;
            // Call virtual function at offset 0x10 (likely "getActionTarget")
            // Hash ID 0xae986323 identifies the action type
            bool success = ((bool (*)(int, int**))vtable[4])(0xae986323, &temp); // vtable[4] because offset 0x10 in bytes = 4 entries
            if (success && temp != nullptr && *(char*)((int)temp + 0x162) == '\0') { // some flag at +0x162
                uint32_t someValue = 0xFFFFFFFF;
                int* actionTargetList = (int*)findEntityByHashId(entity, 0x55859efa); // find entity by hash
                if (actionTargetList != nullptr) {
                    someValue = *(uint32_t*)(actionTargetList + 0x6dc) >> 2; // some count or index shifted
                    playAudio(1); // start action audio
                }
                int actionData = param3;
                bool canCreateNode = createActionNode(mSomeData1, param3, someValue, 1, 1, 0, actionTargetList == nullptr);
                if (canCreateNode) {
                    setupActionNode(param3, mActionId);
                    processAction(entity);
                    mSomeData2 = param3;
                    mState = 3;
                    mSubState = 0;
                    result = 1;
                    if (actionTargetList != nullptr) {
                        stopAudio(); // stop action audio
                    }
                }
                goto end;
            }
        }
        mSubState = 0;
        mState = 6; // failure state
    }
end:
    unlockMutex(gActionMutex);
    return result;
}