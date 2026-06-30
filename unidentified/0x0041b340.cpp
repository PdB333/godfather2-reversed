// FUN_0041b340: CharacterAnimationController::updateBlendWeights

#include <cstdint>
#include <cmath>

// External global references (from EARS engine)
extern float DAT_00e2b1a4;          // e.g., time step or speed scale
extern float DAT_00e2cbe0;          // minimum clamp value
extern int* DAT_012058e8;           // pointer to current player character object

// Forward declarations of called functions
void FUN_00491090();                // likely a profiler/timer begin
uint32_t FUN_00414aa0();            // returns some ID or handle
void FUN_0060ad20(uint32_t objectId, int param1, uint32_t handle); // UI update?
void FUN_00418540(void* animState, uint32_t param, uint32_t param2); // animation update
void FUN_0060add0(uint32_t objectId, uint32_t dataPtr, float* weights); // send weights to UI

void __thiscall CharacterAnimationController::updateBlendWeights(
    void* thisPtr,                  // param_1: AnimationController instance
    void* characterObj,             // param_2: character state/object
    uint32_t param3,                // additional parameter (e.g., animation ID)
    uint32_t param4)                // additional parameter (e.g., blend speed)
{
    // Retrieve per-thread data from TLS (FS segment base)
    // FS:[0x2c] usually points to the Thread Local Storage array or a self pointer.
    int* threadData = **(int***)(__readfsdword(0x2c) + 0x2c); 
    // threadData is a pointer to per-thread data structure

    // Get the character object pointer (stored at offset +4 of this)
    // This likely holds the current character being controlled.
    int* character = *(int**)(thisPtr + 4);  // +0x04: pointer to active character

    FUN_00491090(); // Begin profiling/timing

    uint32_t unknownHandle = FUN_00414aa0(); // get some system handle

    // If the character is the player character and has a valid animation state at +0x200
    if (DAT_012058e8 == character && *(int*)(character + 0x200) != 0) {
        FUN_0060ad20(
            *(uint32_t*)(character + 0x14), // object ID
            *(int*)(character + 0x200),      // animation state pointer
            unknownHandle
        );
    }

    FUN_00491090(); // End profiling/timing or next begin

    // Update animation state with parameters
    FUN_00418540(characterObj, param3, param4);

    float globalSpeed = DAT_00e2b1a4; // e.g., animation blend speed factor
    int* somePerThread = (int*)(threadData + 2); // threadData +8 (since int* steps 4 bytes)
                                                  // Actually threadData is int*, so threadData[2] = *(threadData+2)
    int* animData = *(int**)(characterObj + 0x18); // +0x18: pointer to animation data array

    // Index into animation data using somePerThread value
    int index = *somePerThread; // threadData[2] gives an index
    float weightA = *(float*)((char*)animData + 0x6c + index * 4); // Not exactly: index is added as byte offset? 
    // Actually in code: *(float *)(iVar4 + 0x6c + iVar2) where iVar2 is threadData[2] (int), so it's byte offset.
    // So we treat index as byte offset already. Likely index is a byte offset into a per-thread buffer.
    float weightB = *(float*)((char*)animData + 0x78 + index);
    float weightC = *(float*)((char*)animData + 0x70 + index);

    // Clamp weightA
    if (weightA > 0.0f) {
        if (weightA > globalSpeed) {
            weightA = globalSpeed;
        }
    } else {
        weightA = 0.0f;
    }

    // weightB is from 0x78, weightC from 0x70
    float diff = weightC - weightB; // potentially negative

    // Clamp diff to minimum value
    if (diff < DAT_00e2cbe0) {
        diff = DAT_00e2cbe0;
    }

    // Store computed blend weights into character structure
    *(float*)(character + 0xf0) = weightB;            // +0xf0: blend weight 0
    *(float*)(character + 0xf4) = globalSpeed / diff; // +0xf4: blend weight 1
    *(float*)(character + 0xf8) = weightA - globalSpeed; // +0xf8: blend weight 2

    // If this is the player character, send weights to UI system
    if (DAT_012058e8 == character) {
        FUN_0060add0(
            *(uint32_t*)(character + 0x14), // object ID
            *(uint32_t*)(character + 0xe0), // some data pointer (UI handle?)
            (float*)(character + 0xf0)       // pointer to the three weights
        );
    }

    return;
}