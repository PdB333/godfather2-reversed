// FUNC_NAME: Entity::testMovementAllowance
// Address: 0x00550d30
// Role: Checks if movement from current position towards target is allowed, considering velocity thresholds and dot product criteria.

#include <cmath> // for sqrtf

// Global constants (from Ghidra data)
extern float gTimeStep;               // DAT_00e2afb8
extern float gSomeConstant;           // DAT_00e2b1a4
extern float gEpsilon;                // DAT_00e44598
extern uint32 gAbsMask;               // DAT_00e44680 (e.g., 0x7FFFFFFF)
extern float gSmallSquared;           // DAT_00e2cbe0
extern float gMinRatio;               // DAT_00e2e780
extern uint32 _gDebugFlag;            // _DAT_0122705c (bit0)
extern float gDebugFloat;            // DAT_01227058
extern float gInitDebugFloat;        // DAT_00e32850
extern uint32 gTlsIndex;             // DAT_01139810

// External functions (from Ghidra)
void FUN_0054bae0(); // some utility push/pop?
void FUN_00552930(void* stackBuf, void* otherBuf); // init stack debug struct
void FUN_00aa26e0(void* ptr, uint32 size, uint32 tag); // debug alloc/free
void FUN_009f1820(float* vec, int flag); // some transform

// Global pointer arrays for debug allocator
extern void* PTR_LAB_00e397fc;
extern void* PTR_LAB_00dc4710;
extern void* PTR_LAB_00e39f08;

// Function to fetch thread-local value
inline void* TlsGetValue(uint32 index) {
    // placeholder – actual implementation would use Windows TlsGetValue
    return 0;
}

// Main function
uint32 __thiscall Entity::testMovementAllowance(void* thisPtr, const float* targetPos, float* outPos, float maxDot) {
    // Constants
    const float scale = gTimeStep; // local_3b4

    // Override maxDot if negative with stored value at +0xA8
    if (maxDot < 0.0f) {
        maxDot = *(float*)((uint8*)thisPtr + 0xA8); // +0xA8: maxSpeed or similar
    }

    // Get sub-object pointer at +0x14 (e.g., motion state)
    int* motionState = *(int**)((uint8*)thisPtr + 0x14); // iVar1

    // Save state from thisPtr and motionState
    uint64 savedPosition = *(uint64*)((uint8*)thisPtr + 100); // +100: position (8 bytes)
    float savedSomething = *(float*)((uint8*)thisPtr + 0x6C); // +0x6C: unknown
    float savedVx = *(float*)((uint8*)motionState + 0x10);
    float savedVy = *(float*)((uint8*)motionState + 0x14);
    float savedVz = *(float*)((uint8*)motionState + 0x18);
    float savedVw = *(float*)((uint8*)motionState + 0x1C); // probably w component

    // Get reference position from nested pointer chain
    // motionState+0x30 -> pointer -> +0x18 -> address of reference point
    float* refPos = (float*)*(int*)(*(int*)((uint8*)motionState + 0x30) + 0x18); // iVar2
    float refX = refPos[0]; // +0x30? Actually iVar2+0x30 is refPos
    float refY = refPos[1]; // +0x34
    float refZ = refPos[2]; // +0x38

    // Target position components
    float tarX = targetPos[0];
    float tarY = targetPos[1];
    float tarZ = targetPos[2];

    // Initialize global static if needed
    if ((_gDebugFlag & 1) == 0) {
        _gDebugFlag |= 1;
        gDebugFloat = gInitDebugFloat;
    }

    // Compute scaled displacement from ref to target
    float dispX = (tarX - refX) * scale;
    float dispY = (tarY - refY) * scale;
    float dispZ = (tarZ - refZ) * scale;

    // Store displacement into motion state (temporary)
    *(float*)((uint8*)motionState + 0x10) = dispX;
    *(float*)((uint8*)motionState + 0x1C) = gSomeConstant;
    *(float*)((uint8*)motionState + 0x14) = dispY;
    *(float*)((uint8*)motionState + 0x18) = dispZ;

    // Local copy of debug float (used in allocator)
    float localDebugFloat = gDebugFloat;

    // Debug path: based on bit 10 of thisPtr+0xE4
    uint32 debugFlag = *(uint32*)((uint8*)thisPtr + 0xE4); // +0xE4: debug flags
    if ((debugFlag & (1 << 10)) == 0) {
        // Non-debug path: allocate/free using global pointer table
        FUN_0054bae0();
        FUN_0054bae0();
        // Setup stack buffers
        char stackBuf8[8]; // local_3c0
        void* stackPtrArray[4]; // local_1e0
        FUN_00552930(stackBuf8, stackPtrArray);
        // local_3b0 becomes &PTR_LAB_00e397fc
        void** debugAlloc = &PTR_LAB_00e397fc;
        uint32 allocCount = (uint32)stackPtrArray[2]; // local_398 from stack? Might be structured.
        if ((int32)allocCount >= 0) {
            TlsGetValue(gTlsIndex);
            // Allocate or free with tag 0x17
            FUN_00aa26e0(stackPtrArray[0], (allocCount & 0x3FFFFFFF) * 0x30, 0x17);
        }
        debugAlloc[0] = PTR_LAB_00dc4710;
        stackPtrArray[0] = PTR_LAB_00e397fc;
        if ((int32)stackPtrArray[3] >= 0) { // local_1c8? Actually from heap struct
            TlsGetValue(gTlsIndex);
            // Copy data
            stackPtrArray[0] = *(void**)&stackBuf8[0]; // reconstruct
            // local_398 updated
        }
        goto AFTER_DEBUG;
    } else {
        // Debug path: use different pointer
        FUN_0054bae0();
        void** debugAlloc = &PTR_LAB_00e39f08; // local_3b0
        *(uint32*)((uint8*)debugAlloc + 0x34) = 0; // local_1f0 (part of struct)
        FUN_0054bae0();
        void* tempPtr = debugAlloc; // local_20
        FUN_00552930(stackBuf8, tempPtr);
        // ... similar logic with different pointers
        // Omitted for brevity as it mirrors the non-debug path
    }

AFTER_DEBUG:
    // Common cleanup/allocation
    FUN_00aa26e0(/* ... */);

    // Re-read motion state values (should be same as dispX, etc.)
    float curVx = *(float*)((uint8*)motionState + 0x10);
    float curVy = *(float*)((uint8*)motionState + 0x14);
    float curVz = *(float*)((uint8*)motionState + 0x18);

    // Check if any component changed significantly (by bitwise absolute value)
    uint32 diffX = (uint32)(curVx - dispX) & gAbsMask;
    uint32 diffY = (uint32)(curVy - dispY) & gAbsMask;
    uint32 diffZ = (uint32)(curVz - dispZ) & gAbsMask;
    float fDiffX = *(float*)&diffX; // reinterpret as float
    float fDiffY = *(float*)&diffY;
    float fDiffZ = *(float*)&diffZ;

    if (gEpsilon < fDiffX || gEpsilon < fDiffY || gEpsilon < fDiffZ) {
        // Compute length of displacement vector
        float lenDispSq = dispX * dispX + dispY * dispY + dispZ * dispZ;
        float lenDisp;
        float invLenDisp;
        if (lenDispSq <= gSmallSquared) {
            lenDisp = 0.0f;
            invLenDisp = 0.0f;
        } else {
            lenDisp = sqrtf(lenDispSq);
            invLenDisp = gSomeConstant / lenDisp;
        }

        // Compute length of current velocity vector (should be same)
        float lenCurSq = curVx * curVx + curVy * curVy + curVz * curVz;
        float lenCur;
        float invLenCur;
        if (lenCurSq <= gSmallSquared) {
            lenCur = 0.0f;
            invLenCur = 0.0f;
        } else {
            lenCur = sqrtf(lenCurSq);
            invLenCur = gSomeConstant / lenCur;
        }

        // Dot product of normalized vectors
        float dot = (curVx * invLenCur) * (dispX * invLenDisp) +
                    (curVy * invLenCur) * (dispY * invLenDisp) +
                    (curVz * invLenCur) * (dispZ * invLenDisp);

        // Ratio of lengths
        float ratio = lenCur / lenDisp; // Note: if lenDisp==0, ratio becomes inf, but handled?

        if (dot < maxDot || ratio < gMinRatio) {
            uVar3 = 0; // movement not allowed
        } else {
            uVar3 = 1; // movement allowed
        }
    } else {
        uVar3 = 2; // no significant change -> always allowed? (or error)
    }

    // Restore saved state
    float restoreVec[4]; // local_410, etc.
    restoreVec[0] = refX;
    restoreVec[1] = refY;
    restoreVec[2] = refZ;
    restoreVec[3] = gSomeConstant;
    FUN_009f1820(restoreVec, 0); // transform or validate

    // Write back saved values
    *(uint64*)((uint8*)thisPtr + 100) = savedPosition;
    *(float*)((uint8*)thisPtr + 0x6C) = savedSomething;
    *(float*)((uint8*)motionState + 0x10) = savedVx;
    *(float*)((uint8*)motionState + 0x14) = savedVy;
    *(float*)((uint8*)motionState + 0x18) = savedVz;
    *(float*)((uint8*)motionState + 0x1C) = savedVw;

    // Optionally output the candidate position
    if (outPos != nullptr) {
        outPos[0] = curVx + refX;
        outPos[1] = curVy + refY;
        outPos[2] = curVz + refZ;
    }

    return uVar3;
}