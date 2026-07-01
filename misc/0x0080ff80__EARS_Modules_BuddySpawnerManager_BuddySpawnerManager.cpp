// Xbox PDB: EARS_Modules_BuddySpawnerManager_BuddySpawnerManager
// FUNC_NAME: BuddySpawnManager::initialize
// Role: Constructs the singleton BuddySpawnManager, registers for "iMsgBuddySpawn" messages.
// Address: 0x0080ff80
// Called by: 0x0067fd50
// Based on Ghidra decompilation. Uses __thiscall (this in ECX).

#include <cstdint>

// External pointers from the game's data section
extern uint32_t* PTR_FUN_00d72e60;   // Primary vtable for BuddySpawnManager
extern uint32_t* PTR_LAB_00d72e48;   // Temporary second vtable pointer
extern uint32_t* PTR_LAB_00d72e5c;   // Final second vtable pointer

extern uint32_t DAT_0112da38;         // Message ID storage for "iMsgBuddySpawn"

extern void FUN_00408240(uint32_t* outId, const char* string);  // String-to-ID conversion (hash lookup?)
extern void FUN_00408900(void* obj, uint32_t* msgId, uint32_t flags); // Register message handler (0x8000 = receive flag)

class BuddySpawnManager {
public:
    // Offsets (each 4 bytes):
    // +0x00: vtable (PTR_FUN_00d72e60)
    // +0x04: uint32_t field1 (initialized to 1)
    // +0x08: uint32_t field2 (initialized to 0)
    // +0x0C: vtable2 (PTR_LAB_00d72e5c) – possibly second interface
    // +0x10: uint32_t field3 (initialized to 0)
    // +0x14: uint32_t field4 (initialized to 0)
    // +0x18: uint32_t field5 (initialized to 0)

    void initialize() {
        // Initialize data fields
        this->field1 = 1;              // param_1[1] = 1
        this->field2 = 0;              // param_1[2] = 0
        this->vtable2 = &PTR_LAB_00d72e48; // param_1[3] = &PTR_LAB_00d72e48 (temporary)

        // Store singleton pointer globally
        gBuddySpawnManager = this;     // DAT_01129918 = param_1

        // Set primary vtable
        this->vtable = &PTR_FUN_00d72e60; // *param_1 = &PTR_FUN_00d72e60

        // Override second vtable to final value
        this->vtable2 = &PTR_LAB_00d72e5c; // param_1[3] = &PTR_LAB_00d72e5c

        // Zero remaining fields
        this->field3 = 0;              // param_1[4] = 0
        this->field4 = 0;              // param_1[5] = 0
        this->field5 = 0;              // param_1[6] = 0

        // Register for "iMsgBuddySpawn" message
        uint32_t msgId = 0;
        FUN_00408240(&msgId, "iMsgBuddySpawn");
        if (msgId != 0) {
            FUN_00408900(this, &msgId, 0x8000);
        }
    }

private:
    // Actual layout corresponds to the offsets above
    uint32_t* vtable;       // +0x00
    uint32_t field1;        // +0x04
    uint32_t field2;        // +0x08
    uint32_t* vtable2;      // +0x0C
    uint32_t field3;        // +0x10
    uint32_t field4;        // +0x14
    uint32_t field5;        // +0x18
};

// Global instance pointer (DAT_01129918)
BuddySpawnManager* gBuddySpawnManager = nullptr;