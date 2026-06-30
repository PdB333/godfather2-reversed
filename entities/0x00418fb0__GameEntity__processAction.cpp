// FUNC_NAME: GameEntity::processAction
// Function at 0x00418fb0 - Processes an action/command for a game entity.
// Handles setting action data from a global table, playing sounds, and spawning effects.
// Calls base class processing at the end.

#include <cstdint>

// Global singleton pointer to the main GameSim instance
GameSim* gGameSim; // DAT_012058e8

// Forward declarations for engine functions
void playSound();                    // FUN_006063b0
int  getCurrentTime();               // FUN_00414aa0
void spawnEffect(int param1, int param2, int time); // FUN_0060ad20 (likely effect spawn)
void GameEntity::baseProcessAction(Command* cmd, int param3, int param4); // FUN_00418540 (base class virtual call)

// Inline function to retrieve a value from a global table via TLS
// Uses FS:0x2C (thread-local storage) to access a per-thread pointer,
// then follows a double indirection to reach a global data array.
inline int* getGlobalTableEntry(int index) {
    // Retrieve thread-local pointer at FS:0x2C
    void** tlsBase = *(void***)(__readfsdword(0x2C));
    // Double indirection + offset 8 gets a pointer to the table base
    int* tableBase = *(int**)((char*)(*tlsBase) + 8);
    // Return entry at offset 0x94 + index*4
    return (int*)((char*)tableBase + 0x94 + index * 4);
}

void __thiscall GameEntity::processAction(Command* cmd, int param3, int param4) {
    // 'this' is the GameEntity object.
    // +0x04: pointer to the owning GameSim (simulation/world)
    GameSim* sim = *(GameSim**)((char*)this + 4);

    // +0x18 in cmd: action type index (e.g., weapon ID, power-up type)
    int actionIndex = *(int*)((char*)cmd + 0x18);

    // Store the global table entry value into the sim's field at +0x224
    // This value might be a damage/hit value or a reference to a particle system, etc.
    *(int*)((char*)sim + 0x224) = *getGlobalTableEntry(actionIndex);

    // Check if this sim is the global singleton (usually the main world)
    // and if the flag at sim+0x220 is set (e.g., "isPlayerControlled")
    if (gGameSim == sim && *(int*)((char*)sim + 0x220) != 0) {
        playSound();  // Trigger a sound effect (e.g., weapon fire)
    }

    int currentTime = getCurrentTime();  // Get current game time in ms

    // Check another flag at sim+0x200 (e.g., "hasVisualEffect")
    if (gGameSim == sim && *(int*)((char*)sim + 0x200) != 0) {
        // Spawn a visual effect (e.g., muzzle flash, blood spatter)
        // Uses sim's field at +0x14 and the effect handle at +0x200
        spawnEffect(*(int*)((char*)sim + 0x14), *(int*)((char*)sim + 0x200), currentTime);
    }

    // Call base class virtual function to finish processing
    baseProcessAction(cmd, param3, param4);
}