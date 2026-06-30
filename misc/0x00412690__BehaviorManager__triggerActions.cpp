// FUNC_NAME: BehaviorManager::triggerActions

#include <cstdint>

// DAT_0122337c appears to be the game engine singleton (EARS engine)
extern uint32_t gGameEngine; // placeholder for global

// Forward declarations for called functions
void __cdecl prepareContext(void* context); // FUN_004d3bc0
void __cdecl createActionEvent(uint32_t engine, uint32_t param1, int* outputArray, uint32_t param2, uint32_t flags, int zero); // FUN_00406380

struct BehaviorNode {
    int32_t someValue;       // +0x10
    uint8_t activeFlag;      // +0x15 (cleared to 0 during processing)
    void* behaviorContext;   // +0x18 (pointer to a behavior context object)
    uint32_t* actionArray;   // +0x1c (array of 8‑byte entries: two uint32s per action)
    uint32_t actionCount;    // +0x20 (number of actions in the array)
};

void __thiscall BehaviorManager::triggerActions(void* targetContext) {
    // +0x20c: pointer to start of a dynamic array of BehaviorNode pointers
    BehaviorNode** nodeIter = *(BehaviorNode***)(this + 0x20C);
    // +0x210: element count or end pointer offset?  
    // The decompiler shows "piVar4 + (int)(this+0x210)" – treat as absolute end pointer.
    BehaviorNode** nodeEnd = nodeIter + *(int*)(this + 0x210);

    if (nodeIter == nodeEnd)
        return;

    while (true) {
        BehaviorNode* currentNode = *nodeIter;
        if (currentNode->behaviorContext == targetContext) {
            currentNode->activeFlag = 0; // reset active flag

            uint32_t actionCount = currentNode->actionCount;
            if (actionCount != 0) {
                uint32_t* actionEntry = currentNode->actionArray;
                uint32_t idx = 0;
                do {
                    // Each action entry is two 32‑bit values
                    uint32_t actionData0 = actionEntry[idx * 2];
                    uint32_t actionData1 = actionEntry[idx * 2 + 1];

                    // The function at 0x004d3bc0 takes an address inside the behavior context
                    // (behaviorContext + 8) – likely a sub‑field used as an input.
                    prepareContext((uint8_t*)currentNode->behaviorContext + 8);

                    // outputBuffer receives the result of createActionEvent
                    int outputBuffer[3];
                    
                    // local_c should be a function pointer, but its origin is unclear.
                    // It may be stored somewhere in the manager object (e.g., offset 0x214)
                    // or could be a member of BehaviorNode itself. Here we assume it is
                    // taken from a hidden register/stack location not fully visible in decomp.
                    auto callback = reinterpret_cast<void(*)(void*)>(local_c); // unknown

                    createActionEvent(gGameEngine, actionData0, outputBuffer, actionData1,
                                      currentNode->someValue, 0);
                    if (outputBuffer[0] != 0) {
                        callback((void*)outputBuffer[0]);
                    }

                    idx++;
                } while (idx < actionCount);
            }
            break; // processing complete – exit the search loop
        }

        nodeIter++;
        if (nodeIter == nodeEnd)
            return;
    }
}