// FUNC_NAME: FollowPathStateMachine::processMovement
// Function at 0x005ffc10: Updates movement towards a target, calling collision checks and managing state transitions.
// Uses a context object (pContext), a target position (pTarget), a movement accumulator/state (pMoveState), and a flag (pParam4).
// Returns 1 for ongoing movement, 2 for path segment completed.

#include <cmath>

// Global constants (likely from data)
extern const float kTimeStep = 0.0166667f; // DAT_00e448bc (approx 1/60)
extern const float kCloseEnoughSq = 0.01f; // DAT_00e2b1a4 (squared distance threshold)

// Forward declarations of internal functions
int FUN_005f6ee0(void* pContext, float* pos, int unknown1, int unknown2, float delta); // Likely collision/ground query
void FUN_004daf90(int* ptr); // Likely linked list removal
bool FUN_005ff960(void* pContext, float* pTarget, float* pMoveState, float* pParam3, float* pCurrentPos, int unknown, int unknown2, int param4); // Movement processing

int __thiscall FollowPathStateMachine::processMovement(void* pContext, float* pTarget, float* pMoveState, int pParam4) {
    float dx, dy, dz, distSq;
    int otherObject;

    // Increment time accumulator in moveState (index 1)
    pMoveState[1] += kTimeStep;

    // Save current desired target position from object (at offsets 0x20,0x28)
    float localTargetX = *(float*)(this + 0x20); // +0x20: target position X
    float localTargetZ = *(float*)(this + 0x28); // +0x28: target position Z

    // Check if the internal target is zero (unset) or close to the external target
    bool targetChanged = false;
    if ( ( (localTargetX == 0.0f) && (*(float*)(this + 0x24) == 0.0f) && (localTargetZ == 0.0f) && (*(float*)(this + 0x2c) == 0.0f) ) ||
         ( (*pTarget - localTargetX) * (*pTarget - localTargetX) + (pTarget[1] - localTargetZ) * (pTarget[1] - localTargetZ) < kCloseEnoughSq ) ) {
        // Copy external target to internal target
        float* internalTarget = (float*)(this + 0x20); // +0x20: start of 4-float vector (x,y,z,w)
        internalTarget[0] = pMoveState[0];
        internalTarget[1] = pMoveState[1];
        internalTarget[2] = pMoveState[2];
        internalTarget[3] = pMoveState[3];
        targetChanged = true;
    }

    // Query collision/ground at external target position
    otherObject = FUN_005f6ee0(pContext, pTarget, 0, pParam4, pMoveState[1]);

    // If no collision object found, or target was changed and distance to collision object is large, clear flag
    if ( (otherObject == 0) || (!targetChanged) ||
         ( *(float*)(otherObject + 0x18) * *(float*)(otherObject + 0x18) <= 
           (*pTarget - *(float*)(otherObject + 0x10)) * (*pTarget - *(float*)(otherObject + 0x10)) +
           (pTarget[1] - *(float*)(otherObject + 0x14)) * (pTarget[1] - *(float*)(otherObject + 0x14)) ) ) {
        *(unsigned int*)(this + 0xb4) &= 0xffffefff; // Clear bit 12 (0x1000)
    } else {
        *(unsigned int*)(this + 0xb4) |= 0x1000; // Set bit 12
    }

    if (otherObject != 0) {
        if (!targetChanged) {
            // Check collision at old internal target
            int oldOther = FUN_005f6ee0(pContext, &localTargetX, 0, pParam4, pMoveState[1]);
            if (oldOther == 0) {
                // No collision at old target; revert to old target
                *pTarget = localTargetX;
                pTarget[1] = localTargetZ;
                *(float*)(this + 0x10) = *pTarget; // +0x10: current position X
                *(float*)(this + 0x18) = pTarget[1]; // +0x18: current position Z (note: no Y)
                otherObject = 0;
                // Call virtual function at +0xa8 (likely progress callback)
                int (*func)() = *(int (**)())(this + 0xa8);
                if (func() == 0) {
                    return 1; // Movement not finished, but reverted
                }
            }
        }

        // Set active flag
        *(unsigned char*)(this + 0x40) = 1; // +0x40: active flag

        // Replace the path segment pointer (+0x44) with the new collision object
        int* segmentPtr = (int*)(this + 0x44); // +0x44: linked list pointer to path segment
        if (*segmentPtr != otherObject) {
            if (*segmentPtr != 0) {
                FUN_004daf90(segmentPtr); // Remove old segment from list
            }
            *segmentPtr = otherObject;
            if (otherObject != 0) {
                *(int*)(this + 0x48) = *(int*)(otherObject + 4); // +0x48: next pointer (linked list)
                *(int**)(otherObject + 4) = segmentPtr; // Insert this object into list
            }
        }

        // Process movement with current target (from internal target at +0x20)
        float* currentPos = (float*)(this + 0x20); // +0x20: internal target position (used as current for movement)
        bool movementResult = FUN_005ff960(pContext, pTarget, pMoveState, pParam3, currentPos, 4, 0, pParam4);

        if (!movementResult) {
            // Movement failed; clear internal target to zero
            *(float*)(this + 0x2c) = 0.0f; // Z component?
            *(float*)(this + 0x28) = 0.0f;
            *(float*)(this + 0x24) = 0.0f;
            *(float*)(this + 0x20) = 0.0f;
            return 2; // Path segment finished
        }

        // Update current position from processed result
        *(float*)(this + 0x10) = *(float*)(this + 0x20); // +0x10: current pos X = target X
        *(float*)(this + 0x18) = *(float*)(this + 0x28); // +0x18: current pos Z = target Z

        // Subtract the fixed time step from accumulator (moveState[1])
        pMoveState[1] -= kTimeStep;

        // Copy moveState (which now holds end position) to object's movement end data
        *(int*)(this + 0x60) = *(int*)pMoveState;        // +0x60: end position X (start of 4-float)
        *(int*)(this + 0x64) = *(int*)(pMoveState + 1);   // +0x64: end position Y (or second component)
        *(int*)(this + 0x68) = *(int*)(pMoveState + 2);   // +0x68: end position Z
        *(int*)(this + 0x6c) = *(int*)(pMoveState + 3);   // +0x6c: end position W

        // Compute distance vector from current pos to end pos
        float deltaX = *(float*)(this + 0x68) - *(float*)(this + 0x18); // endZ - currentZ
        float deltaY = *(float*)(this + 0x64) - *(float*)(this + 0x14); // endY - currentY (offset 0x14 is Y)
        float deltaZ = *(float*)(this + 0x60) - *(float*)(this + 0x10); // endX - currentX
        *(float*)(this + 0xc4) = sqrtf(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ); // +0xc4: remaining distance
        *(float*)(this + 0xc0) = 0.0f; // +0xc0: elapsed time for this segment? reset
        *(float*)(this + 0xe0) = 0.0f; // +0xe0: unknown reset
    }
    return 1; // Movement still in progress
}