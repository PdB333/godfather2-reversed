// FUNC_NAME: PlayerGroundSM::enterLandingState
#include <cstdint>
#include "GameHeaders.h" // hypothetical include for known types and globals
// Based on Ghidra decompile of address 0x8AC450. Function appears to transition player movement to state 5 (landing state).

class PlayerGroundSM { // inherited from PlayerSM with movement states: idle=0,..., air=4, land=5, run=6 etc.
public:
    // vtable pointer at offset 0x0, size uint32_t* or void* vtblPtr; skipped for brevity
    // Field offsets (in bytes from this):
    // +0xD8: int32_t state;          // current state index
    // +0x9C: int32_t maxLandCount;   // possibly maximum number of landing effects allowed
    // +0x10C: int32_t curLandCount;  // current landing effect count

    // Also a member pointer to a landing effect object at some offset (set by FUN_00481690)
    // Not explicitly shown but inferred from allocation pattern.
};

// Forward declarations for called functions (with guessed names)
bool IsInputActive();                                             // 0x481660
void* AllocateMemory(uint32_t size);                             // 0x9C8E50
void* ConstructLandingEffect(PlayerGroundSM* this);               // 0x8A9460
void StoreAllocatedEffect(void* effect);                         // 0x481690
bool IsLandingConditionActive();                                  // 0x481640
void PlayLandingEffect();                                        // 0x92E2E0
void UpdateAnimationCommon();                                    // 0x8AB6A0
void SetVectorToZero(Vec3& vec);                                 // 0x408A00

// Global data (from DAT_0112ee7c, possibly a zero vector constant or some reference)
extern Vec3 gDefaultZeroVector; // declared somewhere

void __thiscall PlayerGroundSM::enterLandingState(PlayerGroundSM* this)
{
    // Step 1: Possibly check input context and allocate a landing effect object
    if (IsInputActive())
    {
        int32_t* newEffect = (int32_t*)AllocateMemory(0x38); // size 56 bytes
        int32_t* initializedEffect = nullptr;
        if (newEffect != nullptr)
        {
            initializedEffect = (int32_t*)ConstructLandingEffect(this);
        }
        StoreAllocatedEffect(initializedEffect);
    }

    // Step 2: Check whether we should spawn more landing effects (like dust)
    // Condition: state is still in air (4) and current land count < max land count
    if (IsLandingConditionActive() &&
        (this->state == 4) &&
        ((uint32_t)this->curLandCount < (uint32_t)this->maxLandCount))
    {
        PlayLandingEffect();
    }

    // Step 3: Perform common update (animation, physics base)
    UpdateAnimationCommon();

    // Step 4: Change state to 5 (landing) and invoke vtable callback for state enter
    this->state = 5;

    // Vtable function at index 0xF8 / 4 = 62 (0x3E, assuming 4‑byte pointer)
    // Usually onStateEnter(int newState) or onLandingBegin()
    void (*onStateEnter)(PlayerGroundSM*) = *(void (**)(PlayerGroundSM*))(*reinterpret_cast<uint32_t*>(this) + 0xF8);
    (*onStateEnter)(this);

    // Step 5: Reset a velocity or float vector to zero (likely to stop movement)
    // The stack variables correspond to a temporary Vec3 constructed from global zero and a zero integer
    Vec3 velocityVector;
    velocityVector.x = gDefaultZeroVector.x;
    velocityVector.y = gDefaultZeroVector.y;
    velocityVector.z = gDefaultZeroVector.z;
    SetVectorToZero(velocityVector);
}