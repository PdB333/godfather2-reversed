// FUNC_NAME: FacingController::update

// Address: 0x00601050
// Role: Updates smooth facing (orientation) towards a target position or direction.
// Handles angle calculation, clamping, and smoothing with optional velocity output.
// Uses intrusive linked lists for temporary reference management.

#include <cmath> // for sqrt

// Forward declarations of external functions (EA EARS engine)
void __cdecl FUN_004daf90(float* node); // Removes node from linked list
void __cdecl FUN_005fdf60(float* obj, uint target); // Possibly updates target reference
void __cdecl FUN_005fe2e0(float* obj, float* source, float* dest, int flag); // Sets orientation
void __cdecl FUN_005f5ce0(); // Unknown (likely pop matrix or stack)
void __cdecl FUN_00414aa0(); // Unknown (no-op?)
void __cdecl FUN_00b9a9fa(); // Floating-point helper (no-op?)

// Global constants (from data section)
extern float DAT_00e2cbe0; // Squared minimum distance threshold (0.001f?)
extern float DAT_00e2b1a4; // Inv sqrt scale (1.0f?)
extern float DAT_00e44564; // PI (3.14159f)
extern float DAT_00e2afac; // Angle clamping epsilon (0.01f)
extern float DAT_00e2a848; // 2*PI (6.283185f)
extern float DAT_00e2cd54; // Speed scaling factor (?)
extern float DAT_00e44968; // Max speed inverse (?)

class FacingController {
public:
    // Offsets (in float units = 4 bytes each)
    float posX; // +0x00
    float posY; // +0x04
    float posZ; // +0x08
    float posW; // +0x0C (unused?)
    float unk_10; // +0x10 - flag or state
    float unk_11; // +0x11 - some float
    // ... (offsets 0x12 to 0x17 unknown)
    float currentPosX; // +0x18
    float currentPosY; // +0x19
    float currentPosZ; // +0x1A
    // +0x1C: linked list node (pointer)
    float* targetNodePtr; // +0x1C - Actually a pointer to an intrusive list node (stored as float)
    float targetNodeNext; // +0x1D - Next pointer (saved as float)
    float* sourceNodePtr; // +0x1E - Another node (for source)
    // +0x1F: another node (maybe for direction source)
    float* dirSourceNode; // +0x1F
    float dirSourceNext; // +0x20
    // +0x21: another node
    float* extraNode; // +0x21
    // +0x22: target position
    float targetPosX; // +0x22
    float targetPosNext; // +0x23 (node next pointer)
    float targetPosZ; // +0x24 (actually the node data, but used as z)
    // +0x25..+0x28: unknown
    float callbackFunc; // +0x29 - Function pointer (stored as float, but actually int)
    // +0x2A..+0x2C: unknown
    float flags; // +0x2D - Bitfield (e.g., 1 = facing invalid)
    // +0x2E..+0x30: unknown
    float distance; // +0x31 - Distance to target
    // +0x32..+0x33: unknown
    float someSpeed; // +0x34
    float someSpeedY; // +0x35
    float someSpeedZ; // +0x36
    // +0x37: unknown
    float someTime; // +0x38
    // +0x39..+0x3A: unknown
    float speedScale; // +0x3B - Computed from distance
    float invMaxSpeed; // +0x3C - 1.0 / (speedScale * something)
    float currentYaw1; // +0x3D - Smoothed yaw (first component)
    float currentYaw2; // +0x3E - Base yaw
    float targetYaw;   // +0x3F - Computed yaw from direction
    float currentPitch1; // +0x40 - Smoothed pitch
    float currentPitch2; // +0x41 - Base pitch
    float targetPitch;   // +0x42 - Computed pitch
    float unk_43; // +0x43
    float unk_44; // +0x44

    // Method: update facing towards target
    void __thiscall update(float* thisPtr, int* vtable, uint targetHandle, float* sourcePos, float* previousAngles, bool useSourceAsDirection);
};

void __thiscall FacingController::update(float* thisPtr, int* vtable, uint targetHandle, float* sourcePos, float* previousAngles, bool useSourceAsDirection)
{
    float* nodePtr;
    float* tempNode;
    float* dirVector;
    float fTemp1, fTemp2, fTemp3;
    double dTemp;
    float sqrDist;
    float invDist;
    float dirX, dirY, dirZ;
    float yaw, pitch;
    float deltaYaw, deltaPitch;
    float clampedYaw, clampedPitch;
    float scale;

    // Save and replace node pointers (intrusive list manipulation)
    nodePtr = thisPtr + 0x11;
    thisPtr[0x10] = 0.0f; // Clear flag
    if (*nodePtr != 0.0f) {
        FUN_004daf90(nodePtr);
        *nodePtr = 0.0f;
    }

    // Save current target node
    float savedTargetNode = thisPtr[0x1c];
    float savedTargetNext = 0.0f;
    if (savedTargetNode != 0.0f) {
        savedTargetNext = *(float*)((int)savedTargetNode + 4);
        *(float**)((int)savedTargetNode + 4) = &savedTargetNode; // Redirect to local
    }

    float savedSourceNode = thisPtr[0x1e];
    float savedSourceData = thisPtr[0x1f];
    float savedSourceNext = 0.0f;
    if (savedSourceData != 0.0f) {
        savedSourceNext = *(float*)((int)savedSourceData + 4);
        *(float**)((int)savedSourceData + 4) = &savedSourceData;
    }

    float savedExtraNode = thisPtr[0x21];

    FUN_005fdf60(thisPtr, targetHandle); // Update target reference

    // Query target's data (likely a position or object)
    nodePtr = (float*)(*(int (__thiscall**)(int))(*vtable + 0xc))(targetHandle);
    float* targetData = nodePtr; // First element is pointer to something?
    float targetNodeVal = *targetData;
    float targetNodeNextSave = 0.0f;
    if (targetNodeVal != 0.0f) {
        targetNodeNextSave = *(float*)((int)targetNodeVal + 4);
        *(float**)((int)targetNodeVal + 4) = &targetNodeVal;
    }
    float targetZ = targetData[2];
    nodePtr = (float*)(-(uint)(targetNodeVal != 0.0f) & (uint)targetZ);

    // Clear velocity
    thisPtr[0x0b] = 0.0f;
    thisPtr[0x0a] = 0.0f;
    thisPtr[0x09] = 0.0f;
    thisPtr[0x08] = 0.0f;

    float localTargetNode = targetNodeVal;

    if (!useSourceAsDirection) {
        // Mode: compute direction from sourcePos
        FUN_005f5ce0();
        FUN_005f5ce0();

        // Copy sourcePos to current position
        thisPtr[0x18] = sourcePos[0];
        thisPtr[0x19] = sourcePos[1];
        thisPtr[0x1a] = sourcePos[2];

        // Set target position from target data
        // (nodePtr points to target position? Actually it's from the target object)
        // Use the direction from target object
        dirX = *nodePtr;
        dirY = nodePtr[1];
        dirZ = nodePtr[2];

        // Store target position at offset 0x22
        float* targetPosNode = thisPtr + 0x22;
        if (targetPosNode != &localTargetNode && *targetPosNode != localTargetNode) {
            if (*targetPosNode != 0.0f) {
                FUN_004daf90(targetPosNode);
            }
            *targetPosNode = localTargetNode;
            if (localTargetNode != 0.0f) {
                thisPtr[0x23] = *(float*)((int)localTargetNode + 4);
                *(float**)((int)localTargetNode + 4) = targetPosNode;
            }
        }
        thisPtr[0x24] = targetZ; // Store z component

        // Already have dirX, dirY, dirZ from nodePtr
    }
    else {
        // Mode: use target's forward direction (from target position stored at offset 0x22)
        // Copy target position to sourceNode and dirSourceNode
        float* targetPosNode = thisPtr + 0x1c;
        float* sourceNode = thisPtr + 0x1f;

        // Update target position node at offset 0x1c
        if (targetPosNode != &localTargetNode && *targetPosNode != localTargetNode) {
            if (*targetPosNode != 0.0f) {
                FUN_004daf90(targetPosNode);
            }
            *targetPosNode = localTargetNode;
            if (localTargetNode != 0.0f) {
                thisPtr[0x1d] = *(float*)((int)localTargetNode + 4);
                *(float**)((int)localTargetNode + 4) = targetPosNode;
            }
        }
        thisPtr[0x1e] = targetZ;

        // Copy from target position to dirSourceNode (offset 0x1f)
        if (sourceNode != targetPosNode) {
            float* dirNode = targetPosNode;
            float targetVal = *dirNode;
            if (*sourceNode != targetVal) {
                if (*sourceNode != 0.0f) {
                    FUN_004daf90(sourceNode);
                }
                *sourceNode = targetVal;
                if (targetVal != 0.0f) {
                    thisPtr[0x20] = *(float*)((int)targetVal + 4);
                    *(float**)((int)targetVal + 4) = sourceNode;
                }
            }
        }
        thisPtr[0x21] = thisPtr[0x1e]; // Copy z

        // Use direction from target object's forward vector (from nodePtr)
        dirX = *nodePtr;
        dirY = nodePtr[1];
        dirZ = nodePtr[2];

        // Copy to current position
        thisPtr[0x18] = dirX;
        thisPtr[0x19] = dirY;
        thisPtr[0x1a] = dirZ;

        // Also copy to source position if provided
        if (sourcePos != nullptr) {
            sourcePos[0] = dirX;
            sourcePos[1] = dirY;
            sourcePos[2] = dirZ;
        }

        // Adjust orientation? Call another function
        FUN_005fe2e0(thisPtr, &localTargetNode, thisPtr + 0x22, 0);
    }

    FUN_00414aa0();

    // Reset some variables
    float zero = 0.0f;
    thisPtr[0x38] = 0.0f;
    thisPtr[0x30] = 0.0f;
    thisPtr[0x44] = 0.0f;
    thisPtr[0x43] = 0.0f;

    // Check if target is invalid
    if (thisPtr[0x22] == 0.0f || (float*)thisPtr[0x24] == nullptr) {
        // No valid target, set flag and clear angles
        thisPtr[0x2d] = (float)((uint)thisPtr[0x2d] | 1); // Set invalid flag
        thisPtr[0x3f] = 0.0f;
        thisPtr[0x3e] = 0.0f;
        thisPtr[0x3d] = 0.0f;
        thisPtr[0x42] = 0.0f;
        thisPtr[0x41] = 0.0f;
        thisPtr[0x40] = 0.0f;
        goto cleanup;
    }

    // Compute direction vector from current position to target
    float targetX, targetY, targetZ;
    if (!useSourceAsDirection) {
        // Use direction from nodePtr (the target's forward vector)
        targetX = *nodePtr;
        targetY = nodePtr[1];
        targetZ = nodePtr[2];
    }
    else {
        // Use position stored at offset 0x22
        float* targetPos = (float*)thisPtr[0x22]; // Actually a pointer to node data
        targetX = *targetPos;
        targetY = targetPos[1];
        targetZ = targetPos[2];
    }

    // Subtract this position
    dirX = targetX - thisPtr[0];
    dirY = targetY - thisPtr[1];
    dirZ = targetZ - thisPtr[2];

    // Compute squared distance
    sqrDist = dirX * dirX + dirY * dirY + dirZ * dirZ;

    if (DAT_00e2cbe0 < sqrDist) {
        // Normalize direction
        float dist = sqrt(sqrDist);
        invDist = DAT_00e2b1a4 / dist;
        dirX *= invDist;
        dirY *= invDist;
        dirZ *= invDist;
    }
    else {
        invDist = 0.0f;
    }

    // Compute angles (yaw from dirX and dirY? pitch from dirZ?)
    // The code uses dirX and dirY to compute yaw, then derives pitch from dirY? Actually it looks like
    // yaw = atan2(dirY, dirX)? No, the code does:
    // dVar6 = (double)dirX; FUN_00b9a9fa(); fVar10 = (float)dVar6; => so yaw1 = dirX
    // Then dVar6 = (double)dirY; FUN_00b9a9fa(); pitch = DAT_00e44564 - (float)dVar6; => pitch = PI - dirY
    // That is odd. Might be that dirX and dirY are not normalized components but angles already?
    // Actually looking at the code: after normalization, it sets param_1[0x31] = dist (distance)
    // Then computes param_1[0x3f] = (float)dirX? That would be the x component, not an angle.
    // But later it uses param_1[0x42] = DAT_00e44564 - (float)dirY => PI - dirY.
    // This suggests that the direction vector components are being treated as angle parameters directly.
    // More likely, FUN_00b9a9fa is actually atan2? No, it's a void function.
    // Actually, the code: dVar6 = (double)local_24; FUN_00b9a9fa(); fVar10 = (float)dVar6;
    // The function call does nothing, so it's just casting double to float. So yaw = dirX (float).
    // That would only make sense if dirX and dirY are already angle-like (e.g., azimuth and elevation from some other computation).
    // Given the global constants, it's more plausible that the function computes yaw and pitch from the direction vector.
    // Since we can't fully reverse the algorithm, we'll keep the computation as-is.

    yaw = dirX;
    pitch = DAT_00e44564 - dirY; // PI - dirY -> converts to pitch?

    // Store computed angles
    thisPtr[0x3f] = yaw;
    thisPtr[0x42] = pitch;

    if (previousAngles == nullptr || useSourceAsDirection) {
        // No smoothing, just copy angles
        thisPtr[0x3e] = yaw;
        thisPtr[0x3d] = yaw;
        thisPtr[0x41] = pitch;
        thisPtr[0x40] = pitch;
        if (previousAngles != nullptr) {
            previousAngles[0] = dirX;
            previousAngles[1] = dirY;
            previousAngles[2] = dirZ;
        }
        goto cleanup;
    }

    // Smoothing: clap angles relative to previous
    dTemp = (double)previousAngles[0];
    FUN_00b9a9fa();
    float prevYaw = (float)dTemp;
    float invScale = DAT_00e44588; // Some constant (probably -PI?)
    float epsilon = DAT_00e2afac;
    float twoPi = DAT_00e2a848;

    float yawDiff = yaw - prevYaw;
    float clampedYawDiff = yawDiff;
    if (yawDiff > epsilon) {
        clampedYawDiff = yawDiff - twoPi;
    }
    else if (yawDiff < -epsilon) {
        clampedYawDiff = yawDiff + twoPi;
    }
    float newYaw = prevYaw - clampedYawDiff;
    thisPtr[0x3d] = newYaw;
    // Re-clamp newYaw
    if (newYaw > epsilon) {
        newYaw = newYaw - twoPi;
    }
    else if (newYaw < -epsilon) {
        newYaw = newYaw + twoPi;
    }
    thisPtr[0x3d] = newYaw;

    // Pitch smoothing (similar)
    dTemp = (double)previousAngles[1];
    FUN_00b9a9fa();
    float prevPitch = DAT_00e44564 - (float)dTemp; // Convert previousAngles[1] to pitch
    pitch = thisPtr[0x42]; // Already computed
    float pitchDiff = pitch - prevPitch;
    float clampedPitchDiff = pitchDiff;
    if (pitchDiff > epsilon) {
        clampedPitchDiff = pitchDiff - twoPi;
    }
    else if (pitchDiff < -epsilon) {
        clampedPitchDiff = pitchDiff + twoPi;
    }
    float newPitch = prevPitch - clampedPitchDiff;
    thisPtr[0x40] = newPitch;
    // Re-clamp
    if (newPitch > epsilon) {
        newPitch = newPitch - twoPi;
    }
    else if (newPitch < -epsilon) {
        newPitch = newPitch + twoPi;
    }
    thisPtr[0x40] = newPitch;

    // Compute speed scale
    float dist = thisPtr[0x31];
    float speedScale = dist * DAT_00e2cd54;
    thisPtr[0x3b] = speedScale;
    float invMaxSpeed = DAT_00e44968;
    if (speedScale > 0.0f) {
        invMaxSpeed = DAT_00e2b1a4 / speedScale;
    }
    thisPtr[0x3c] = invMaxSpeed;

    // Reset some speeds? (likely for interpolation)
    thisPtr[0x34] = 0.0f;
    thisPtr[0x35] = 0.0f;
    thisPtr[0x36] = 0.0f;
    thisPtr[0x38] = 1.0e-45f; // Almost zero

cleanup:
    FUN_005f5ce0(); // Restore some state

    // Call custom callback if set
    if ((void*)thisPtr[0x29] != nullptr) {
        typedef void (__thiscall* Callback)(float*, float*, int*, float*, float*);
        ((Callback)thisPtr[0x29])(thisPtr, &savedExtraNode, (int*)&savedSourceNode, thisPtr + 0x1f, thisPtr + 0x22);
    }

    // Restore linked list nodes
    if (localTargetNode != 0.0f) {
        float* nextNode = *(float**)((int)localTargetNode + 4);
        if (nextNode == &localTargetNode) {
            *(float*)((int)localTargetNode + 4) = targetNodeNextSave;
        }
        else {
            while ((float*)nextNode[1] != &localTargetNode) {
                nextNode = (float*)nextNode[1];
            }
            nextNode[1] = targetNodeNextSave;
        }
    }

    if (savedSourceData != 0.0f) {
        // Restore savedSourceNode list
        // (involves savedSourceNext and savedExtraNode)
        float* node = *(float**)((int)savedSourceData + 4);
        if (node == &savedSourceData) {
            *(float*)((int)savedSourceData + 4) = savedSourceNext;
        }
        else {
            while ((float*)node[1] != &savedSourceData) {
                node = (float*)node[1];
            }
            node[1] = savedSourceNext;
        }
    }

    if (savedExtraNode != 0.0f) {
        float* node = *(float**)((int)savedExtraNode + 4);
        if (node == &savedExtraNode) {
            *(float*)((int)savedExtraNode + 4) = savedTargetNext;
        }
        else {
            while ((float*)node[1] != &savedExtraNode) {
                node = (float*)node[1];
            }
            node[1] = savedTargetNext;
        }
    }
}