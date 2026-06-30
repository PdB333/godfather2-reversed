// FUNC_NAME: MovementController::applyVelocityLimits
// Function address: 0x006ca770
// Role: Limits and smooths velocity components based on a max speed from a global (_DAT_00d5780c) and an object's internal speed target (+0x14). 
// Called from vehicle/physics update loops. Modifies two float components (param_1, param_2) representing velocity.

// Assumes:
// - param_1: pointer to velocity x component
// - param_2: pointer to velocity y component
// - param_3: pointer to object (likely vehicle/player) with fields:
//   +0x14: float currentSpeed? or targetSpeed?
//   +0x1c: int/float some value passed to underlying set function
// - _DAT_00d5780c: global maximum allowable speed (float)
// - FUN_00410d80() returns nonzero if system is active (e.g., game not paused)
// - FUN_006c9eb0() sets velocity to a given value (1 = axis? or mode)
// - FUN_006c8b50() normalizes/clamps the resulting vector

#include <cmath>

void MovementController::applyVelocityLimits(float* velocityX, float* velocityY, void* object) {
    int uVar1 = *(int*)((char*)object + 0x1c);   // +0x1c: some mode/target value
    bool isActive = FUN_00410d80();                // check if system is active
    if (isActive) {
        FUN_006c9eb0(1, velocityX, velocityY, 0, 0);  // reset or stop velocity
        return;
    }

    // Normal path: use object's internal speed and the velocity magnitude
    FUN_006c9eb0(1, velocityX, velocityY, uVar1, uVar1);  // set velocity to uVar1-scaled direction?

    float currentSpeed = *(float*)((char*)object + 0x14);  // +0x14: current speed (or friction?)
    float yOrig = *velocityY;                               // store original y component
    float x = *velocityX;
    float len = sqrtf(yOrig * yOrig + x * x);               // magnitude of velocity

    if (len > 0.0f) {
        if (_DAT_00d5780c <= len) {
            len = _DAT_00d5780c;                            // clamp to global max speed
        }
    } else {
        len = 0.0f;
    }

    double dVar6 = (double)yOrig;                           // promote to double
    double dVar7 = (double)len;                             // promoted length
    // Note: the following two calls are likely math library functions (e.g., sin/cos or float->double conversions)
    FUN_00b9a9fa();                                         // unknown
    FUN_00b9af10();                                         // unknown

    // Compute a new factor that blends between currentSpeed and maxSpeed based on len
    // The decompiler shows: fVar5 = (float)dVar7 * (_DAT_00d5780c - currentSpeed) + (float)len * currentSpeed;
    // Which simplifies to: fVar5 = len * _DAT_00d5780c   (since len = (float)dVar7)
    // That suggests the factor is simply len * maxSpeed. But that would scale both components equally,
    // likely a mistake in decompilation; possibly the original had different variables.
    // We'll retain the literal expression for fidelity:
    float fVar5 = (float)dVar7 * (_DAT_00d5780c - currentSpeed) + (float)len * currentSpeed;

    dVar7 = (double)(float)dVar6;                           // double of original y
    FUN_00b99e20();                                         // unknown math
    *velocityX = (float)dVar7 * fVar5;                      // new x component = yOrig * fVar5   (likely bug: should be x?)
    dVar6 = (double)(float)dVar6;                           // double of original y again
    FUN_00b99fcb();                                         // unknown math
    *velocityY = (float)dVar6 * fVar5;                      // new y component = yOrig * fVar5   (both use y? corrupts x?)

    FUN_006c8b50(velocityX, velocityY);                     // normalize or clamp final vector
    return;
}