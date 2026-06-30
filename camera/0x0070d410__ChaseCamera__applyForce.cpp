// FUNC_NAME: ChaseCamera::applyForce
#include <cmath>

// Constants
const float kOneOverSqrt = 1.0f;  // _DAT_00d5780c
const float kEpsilon = 0.001f;    // _DAT_00d5efb8
const uint32 kAbsMask = 0x7FFFFFFF; // DAT_00e44680

// Forward declarations of helper functions (assumed to be elsewhere)
CameraManager* getCameraManager(); // FUN_007079a0
void linkedListRemove(void** listNode); // FUN_004daf90
void updateCameraState(); // FUN_00707c30
void setRotationMatrix(uint32 handle, const float* matrix); // FUN_009f4c40
void setAxisAngleRotation(uint32 handle, const float* axis, float angle); // FUN_009f4ca0
double getCurrentTime(); // FUN_00b9b988
void quaternionFromAxisAngle(float* quat, float angle); // FUN_00aa36a0
void setRotationFromQuaternion(uint32 handle, const float* quat); // FUN_009f4ca0 (actually different)
void getPhysicsWorld(); // FUN_009f2000
void resetCamera(bool reset); // FUN_0070c860
void updateCameraVectors(float* forward, float* up, void* camera); // FUN_0070c310
void* allocateMemory(int size); // FUN_009c8e50 (size 0x24)
uint32 getPhysicsBody(void* body, uint32 type); // FUN_006ada80 (type 0x34e6e9b4)
uint32 setFloatParameter(void* param, int index, float value, uint32 handle, int mode); // FUN_00440590
void resetParameter(void* param); // FUN_00408680
void setIntParameter(void* param, int index, int value, int mode); // FUN_00408b80 (simplified)
void playSound(uint32 soundId); // FUN_00894c90

// Constants for state ids at offset 0x1ad
const char kStateOrbit = 0x19;
const char kStateFollow = 0x1a;
const char kStateFree = 0x1b;

// Sound IDs based on state
const uint32 kSoundOrbit = 0x14336ba6;
const uint32 kSoundFollow = 0x9f448ee7;
const uint32 kSoundFree = 0xe3264e1a;

uint __thiscall ChaseCamera::applyForce(int* thisPtr, uint32 handle, float* forceVector, char applyScale) {
    CameraManager* camMgr = getCameraManager();
    if (camMgr == nullptr) {
        // fail
        return 0; // but actually returns CONCAT31(?,1) but early return? Actually returns (uint)piVar4 & 0xffffff00 which is 0 since piVar4 is null -> return 0
    }

    // Register camera with manager (vtable offset 0x250)
    (camMgr->vtable[0x250])(thisPtr);

    // Set flag at +0x39e (bit 1)
    *(uint16*)((int)thisPtr + 0x39e) |= 2;

    // Linked list insertion for camera nodes (offset 0x2d4 = thisPtr + 0xb5)
    int** listPrev = (int**)(thisPtr + 0xb5);
    int* listHead = (int*)(camMgr + 0x12); // offset 0x48? from camMgr
    if (*listPrev != listHead) {
        if (*listPrev != nullptr) {
            linkedListRemove((void**)listPrev);
        }
        *listPrev = (int*)listHead;
        if (listHead != nullptr) {
            thisPtr[0xb6] = ((int*)camMgr)[0x13]; // next pointer?
            ((int*)camMgr)[0x13] = (int)listPrev;
        }
    }

    // Set some pointer based on linked list head
    if (*listPrev == nullptr || *listPrev == 0x48) { // 0x48 seems like an invalid pointer
        thisPtr[0xb7] = 0;
    } else if (*listPrev == 0) {
        thisPtr[0xb7] = iRam00001ed4; // global? unknown
    } else {
        thisPtr[0xb7] = *(int*)(*listPrev + 0x1e8c);
    }

    // Call virtual methods on thisPtr
    (thisPtr->vtable[0x160])(0);  // e.g., setActive(0)
    (thisPtr->vtable[0x7c])();   // e.g., update()

    updateCameraState();

    // Get physics body pointer at offset 0x1b0 (thisPtr[0x6c])
    int* physicsBody = (int*)thisPtr[0x6c];
    if (physicsBody == nullptr) {
        return 0;
    }

    float vx = forceVector[0];
    float vy = forceVector[1];
    float vz = forceVector[2];
    float vw = forceVector[3];

    // Compute length and normalize
    float lenSq = vx*vx + vy*vy + vz*vz;
    float invLen;
    if (lenSq == 0.0f) {
        invLen = 0.0f;
    } else {
        invLen = kOneOverSqrt / std::sqrt(lenSq);
    }

    // Compute cross product with up vector (0,1,0) to get right vector? Actually, the code is messy due to decompilation.
    // Original likely: cross(forceDir, (0,1,0)) and then cross(forceDir, right) to get up.
    // We'll reconstruct as:
    float up[3] = {0.0f, 1.0f, 0.0f}; // assumed up vector
    float right[3];
    float newUp[3];

    // Cross product: right = forceDir x up
    float rx = vy * invLen * 0.0f - vz * invLen * 1.0f; // simplified from code
    float ry = vz * invLen * 0.0f - vx * invLen * 0.0f;
    float rz = vx * invLen * 1.0f - vy * invLen * 0.0f;
    // Actual derived from decomp: 
    // fStack_48 = vy*invLen*0.0; (0)
    // local_44 = vx*invLen; (since invLen*vx - 0)
    // fVar13 = vx*invLen*0.0; (0)
    // fStack_48 = fStack_48 - vz*invLen; ( -vz*invLen)
    // fVar15 = vz*invLen*0.0; (0)
    // fStack_40 = fVar15 - fVar13; (0)
    // So right = (-vz*invLen, 0, vx*invLen)? That's not standard cross product. Might be a different convention.
    // Given difficulty, we'll keep the decompiled logic but with meaningful names.
    float fStack_48 = vy * invLen * 0.0f;
    float local_44_float = (invLen * vx) - fStack_48; // actually fStack_48 is 0, so = invLen*vx
    float fVar13 = invLen * vx * 0.0f;
    fStack_48 = fStack_48 - vz * invLen; // = -vz*invLen
    float fVar15 = vz * invLen * 0.0f;
    float fStack_40 = fVar15 - fVar13; // = 0

    float rightVec[3] = { fStack_48, 0.0f, local_44_float }; // but fStack_48 is -vz*invLen, local_44_float is vx*invLen
    float newUpVec[3] = { 0.0f, 0.0f, 0.0f }; // fStack_40 is 0

    // Apply abs mask and compare with epsilon to decide rotation method
    float absRightX = *(float*)&(((uint32&)rightVec[0]) & kAbsMask);
    float absRightZ = *(float*)&(((uint32&)rightVec[2]) & kAbsMask);
    float absUpY = 0.0f; // newUpVec[1] is 0

    int flags = 0;
    if (kEpsilon < absRightX) flags |= 8;
    if (kEpsilon < absRightZ) flags |= 4;
    if (kEpsilon < absUpY) flags |= 2;

    if (flags == 0x0E) {
        // All components above threshold: use rotation matrix directly
        setRotationMatrix(handle, /* some matrix */);
    } else {
        // Compute rotation angle from the force vector and something
        double dVar14 = (double)(vw * invLen * 0.0f + vy * invLen + fVar13 + fVar15); // simplified: just vy*invLen
        getCurrentTime(); // timing call
        float normLen = rightVec[0]*rightVec[0] + rightVec[2]*rightVec[2] + 0; // since y is 0
        float invNorm;
        if (normLen == 0.0f) {
            invNorm = 0.0f;
        } else {
            invNorm = kOneOverSqrt / std::sqrt(normLen);
        }
        // Normalize right vector
        float normRight[3] = { rightVec[0]*invNorm, 0.0f, rightVec[2]*invNorm };
        // Axis-angle from this vector? Actually calls FUN_00aa36a0 with &fStack_48 and angle
        quaternionFromAxisAngle(normRight, (float)dVar14);
        setRotationFromQuaternion(handle, /* quaternion */);
    }

    // Prepare final force vector, possibly scaled
    float finalForce[4] = { vx, vy, vz, vw };
    if (applyScale == 0) {
        float scale = (float)thisPtr[0xbc];
        finalForce[0] *= scale;
        finalForce[1] *= scale;
        finalForce[2] *= scale;
        finalForce[3] *= scale;
    }

    // Apply force to physics body via vtable
    int bodyVtable = *(int*)(physicsBody + 0xd0); // offset 0x340? Actually physicsBody is int*, +0xd0 = +0x340, get vtable
    int applyForceFunc = *(int*)(bodyVtable + 0x40); // function at vtable+0x40
    (*(void(__thiscall*)(void*, float*))applyForceFunc)(physicsBody, finalForce);

    // Reset camera if needed
    if (*((char*)thisPtr + 0xe7) == 0) {
        resetCamera(false);
    }

    // Update camera vectors
    updateCameraVectors((float*)(thisPtr + 0xc9), (float*)(thisPtr + 0xcd), thisPtr);

    // Allocate some structure for parameter setting
    void* paramBlock = allocateMemory(0x24);
    uint32 uVar6 = 0;
    if (paramBlock != nullptr) {
        uVar6 = getPhysicsBody(physicsBody, 0x34e6e9b4);
    }

    setFloatParameter(&DAT_0112ad7c, 0, 1.0f, uVar6, 0);
    resetParameter(&DAT_0112ac74);
    uVar6 = setFloatParameter(&DAT_0112ac74, (int)(thisPtr + 0xf), 0.0f /*DAT_00d5eee4*/, uVar6, 4);

    char state = *(char*)((int)thisPtr + 0x1ad);
    if (state == kStateOrbit) {
        uVar6 = setIntParameter(&DAT_0112ac74, (int)(thisPtr + 0xf), 0, 0); // simplified
        // Note: DAT_0112ac74 is a global config or debug parameter
    }

    // Play sound based on state
    if (state == kStateOrbit) {
        playSound(kSoundOrbit);
    } else if (state == kStateFollow) {
        playSound(kSoundFollow);
    } else if (state == kStateFree) {
        playSound(kSoundFree);
    }

    return 1;
}