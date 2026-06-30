// FUNC_NAME: ActionManager::processPendingActions
#include <cstdint>

// Global command data pool: array of 4096 entries (0x1000) of size 0x38 (56 bytes)
// Each entry:
//   +0x00: int refCount;     // reference / use count
//   +0x04: int actionId;     // e.g. script action ID
//   +0x08: int subType;      // subtype for state machine
//   ... rest unknown
#define COMMAND_POOL_SIZE 0x1000
#define COMMAND_ENTRY_SIZE 0x38

// Command slot (32 bytes) in the processing queue
//   +0x00: unknown
//   ...
//   +0x0C: uint8_t state;    // 0x06 = pending, 0x05 = processing? (set to 5)
//   +0x10: uint32_t commandIndex;  // index into command pool

extern void* __fastcall getCommandManager();     // returns pointer to CommandManager singleton
extern void executeCallback(uint32_t actionId, int param2);  // FUN_006065a0
extern void finalizeActionCompletion();          // FUN_004d24f0

void ActionManager::processPendingActions(uint32_t* flags) {
    // Get the singleton command manager
    uint32_t* cmdMgr = (uint32_t*)getCommandManager();
    
    // cmdMgr[0x12] (offset 0x48) = number of command slots (max? count?)
    // cmdMgr[0x13] (offset 0x4C) = first slot index (iterator start)
    uint32_t currentSlot = cmdMgr[0x13];
    uint32_t slotCount = cmdMgr[0x12] * 0x20; // each slot is 32 bytes
    uint32_t endSlot = currentSlot + slotCount;
    
    for (; currentSlot < endSlot; currentSlot += 0x20) {
        // Check the state byte at slot+0x0C
        uint8_t* slotData = (uint8_t*)currentSlot;
        if (slotData[0x0C] == 0x06) {  // pending state
            uint32_t cmdIdx = *(uint32_t*)(slotData + 0x10);
            // Mark as processing (state=5)
            slotData[0x0C] = 5;
            
            if (cmdIdx != 0) {
                // Validate command index
                if ((cmdIdx != 0xFFFFFFFF) && (cmdIdx < COMMAND_POOL_SIZE)) {
                    // Global pool base address (DAT_011a0f38)
                    int* basePool = (int*)(&DAT_011a0f38);
                    int* entry = (int*)((uint8_t*)basePool + cmdIdx * COMMAND_ENTRY_SIZE);
                    if (entry != nullptr) {
                        int refCount = entry[0];  // +0x00
                        if (refCount == 1) {
                            // If subtype == 3, execute callback
                            if (entry[2] == 3) {   // +0x08
                                executeCallback(entry[1], 0); // entry[1] = actionId
                            } else {
                                // Otherwise set refCount to 2 (keep alive?)
                                entry[0] = 2;
                            }
                        } else {
                            // Decrement reference count
                            entry[0] = refCount - 1;
                        }
                    }
                }
                // Clear command index in slot
                *(uint32_t*)(slotData + 0x10) = 0;
            }
        }
        // Note: puVar3 reset is not needed after loop, but we use flags from param_1
    }
    
    // Check the flags passed by the caller (param_1)
    if ((*flags & 0x40000) != 0) {
        finalizeActionCompletion();
    }
}