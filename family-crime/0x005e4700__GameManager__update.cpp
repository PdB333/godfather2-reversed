// FUNC_NAME: GameManager::update
// Address: 0x005e4700
// Role: Main game loop update tick; processes registered callbacks, updates entity/controller states, adjusts timing globals, checks for continue.

#include <types.h>

// Forward declarations of internal functions
void FUN_005e45d0(undefined* buffer);
void FUN_005e5f10(void* unknown);
void FUN_005e61a0(void* unknown, undefined* buffer);
void FUN_005f1d60(uint param);
void FUN_005f0ee0(uint* a, uint* b);

// Extern globals (inferred from data)
extern uint DAT_012056c4;          // frame time accumulator or similar
extern uint DAT_011a0ee4;          // frame delta
extern ushort DAT_0120569e;        // some flag/counter
extern uint DAT_011a0ed8;          // some timer
extern uint DAT_011a0ec0;          // some timer
extern void* DAT_01223510;         // pointer to main game object (GameManager? or Application?); has vtable

// Structure of an entity/device entry (0xc bytes each)
struct EntityEntry {
    int* pointer;      // +0x00: pointer to some resource (e.g., controller state, entity data)
    int field_4;       // +0x04: unknown
    int type;          // +0x08: type identifier (2 for devices/entities to update?)
};

// Structure of the manager object (param_1)
struct GameManager {
    undefined field_0;
    // ... many fields
    EntityEntry entryArray[0x200]; // +0x20: array of 512 entries, each 0xc bytes
    // +0x6020: list of callback function pointers
    int* callbackList;             // +0x6020: array of pointers
    int callbackCount;             // +0x6024: number of callbacks
};

// Main update function
uint __thiscall GameManager::update(GameManager* this, uint deltaTime) {
    uint i;
    EntityEntry* entry;
    undefined local_d0[32];        // 32-byte buffer for controller/input state
    // Additional 16-byte blocks (unused but present on stack)
    uint local_b0, local_ac, local_a8, local_a4;
    uint local_80, local_7c, local_78, local_74;
    uint local_50, local_4c, local_48, local_44;
    uint local_20, local_1c, uStack_18, uStack_14;

    // 1. Update all registered callbacks (likely from other managers)
    for (i = 0; i < this->callbackCount; i++) {
        int* callbackPtr = this->callbackList[i];
        if (callbackPtr != NULL) {
            // Call vtable+4 (some method on the callback object)
            (**(code**)*callbackPtr + 4)();
        }
    }

    // 2. Initialize stack buffers to zero
    local_b0 = 0;
    local_ac = 0;
    local_a8 = 0;
    local_a4 = 0;
    local_80 = 0;
    local_7c = 0;
    local_78 = 0;
    local_74 = 0;
    local_50 = 0;
    local_4c = 0;
    local_48 = 0;
    local_44 = 0;
    local_20 = 0;
    local_1c = 0;
    uStack_18 = 0;
    uStack_14 = 0;

    // 3. Build an input/entity state buffer
    FUN_005e45d0(local_d0);

    // 4. Iterate over all 512 entity/device entries
    entry = this->entryArray;
    for (int j = 0; j < 0x200; j++) {
        if (entry->type == 2) {   // active device/entity
            FUN_005e5f10(entry);  // pre-process
            FUN_005e61a0(entry, local_d0); // apply state
            if (entry->pointer != NULL) {
                // Reset some fields in the pointed-to structure
                *(short*)(entry->pointer + 0x5a) = 0; // +0x5a: word
                *(byte*)(entry->pointer + 0x58) = 0xFF; // +0x58: byte
            }
        }
        entry++;                  // increment by 0xc bytes (since sizeof(EntityEntry)=12)
    }

    // 5. Adjust timing/acumulator globals
    FUN_005f1d60(deltaTime);      // likely accumulates frame time
    global_DAT_012056c4 = 0x80;   // set to some fixed value
    FUN_005f0ee0(&DAT_011a0ed8, &DAT_011a0ec0); // update some timers
    global_DAT_012056c4 -= DAT_011a0ee4;         // subtract frame delta
    DAT_0120569e = 0;             // reset frame flag

    // 6. Check if game should continue (e.g., not quitting)
    char continueFlag = (**(code**)(*(int*)DAT_01223510 + 0x44))(); // vtable+0x44 = IsRunning?
    if (continueFlag != '\0') {
        return 1;   // return 1 means continue
    }
    return 0;       // return 0 means stop
}