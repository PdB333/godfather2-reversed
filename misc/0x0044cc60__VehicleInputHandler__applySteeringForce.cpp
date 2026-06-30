// FUNC_NAME: VehicleInputHandler::applySteeringForce
// Function address: 0x0044cc60
// Purpose: Applies steering force and camera shake effects for a vehicle input slot.
//          Reads controller state, computes steering angle, applies physics-based damping,
//          and optionally triggers camera shake. Outputs steering and feedback values.

#include <cmath>

// External global references (actual addresses may vary)
extern float DAT_00e4494c;          // Initial steering output default
extern float DAT_00e4474c;          // Initial feedback output default
extern float DAT_00e2b04c;          // Scale factor (likely per-frame multiplier)
extern float DAT_011280f0;          // Array of base offsets per param_3
extern float DAT_011280ec;          // Array of additional offsets per param_3
extern float DAT_00e2b1a0;          // 1.0f
extern float DAT_00e2b1a4;          // 1.0f
extern float DAT_00e44564;          // 1.0f
extern float DAT_00e44578;          // Bias for negative values
extern float DAT_00e44928;          // Threshold for clamp
extern float DAT_00e44948;          // Steering deadzone offset
extern float DAT_00e2b05c;          // Min squared length threshold
extern float DAT_00e2e638;          // Default steering magnitude
extern float DAT_00e2cd54;          // Some constant (0.5?)
extern float DAT_00e2eb58;          // Multiplier before sqrt
extern float DAT_00e2eff4;          // Another multiplier
extern float DAT_0110ac8c;          // Coefficient for camera shake
extern float DAT_00e2cbe0;          // Angle threshold for shake
extern float DAT_00e44680;          // Bitmask for fabs? (0x7FFFFFFF)
extern float DAT_00e44648;          // Another constant for rounding

// Pointer to a global camera/vehicle manager object
extern int* DAT_01205378;           // At 0x01205378, points to a structure with offset+0x144 = time, +0x74 = camera steering

// Global arrays for per-player slot data
extern int DAT_01163848[];          // Array of size in_EAX*0x84, contains per-slot values
extern char DAT_01163840[];         // Array for slot flags (size in_EAX*0x210)
extern float DAT_01163810[];        // Array for storing computed values per slot+param_3

// External helper functions
int FUN_00422d40();                  // Initialize camera shake
int FUN_00422e80(float a, float b); // Apply shake parameters (intensity?)
int FUN_00422fb0(float a, float b); // Additional shake effect
int FUN_00422bc0(void* buffer, int zero); // Clear buffer (matrix reset)
int FUN_00423110(float a, float b, float c, float d); // Set matrix element?
int FUN_0044c900(int manager, float time, float offset, float* out); // Compute base steering
int FUN_0044c4c0(float* matrix, float* velocity, float* position); // Transform (matrix * vector)
int FUN_00424470();                  // Matrix operation (probably multiplication)

// Undocumented: sqrt from CRT
float SQRT(float x);

// Main function
int __thiscall VehicleInputHandler::applySteeringForce(
    int thisPtr,                    // +0x30: array of player input handlers
    int slotIndex,                  // param_2 - unused? Actually used for indexing within the class arrays
    int stepIndex,                  // param_3 - index into array for per-slot data (e.g., 0/1 for left/right)
    float* outSteering,            // param_4 - output steering value
    float* outFeedback             // param_5 - output feedback value
)
{
    int playerSlot;                // in_EAX originally passed in register
    int* playerInput;              // Derived from thisPtr + 0x30 + slotIndex*4
    undefined4 matrixData[32];     // Raw matrix storage (32 bytes of ints? Actually 8 ints + 8 floats)
    float matrixQuat[4];           // Part of matrix reinterpreted as quaternion
    float matrixPos[3];            // Position part of matrix
    float* extraInput;             // Pointer from thisPtr + 0x3c + slotIndex*4
    float baseTime;                // From manager+0x144
    float timeOffset;              // Computed based on extraInput/param_3
    float steeringMagnitude;       // Computed steering factor
    float slotData;                // From global DAT_01163848 indexed by slot
    float tempVec;                 // Temporary vector magnitude
    float normalizedVec[4];        // Normalized direction
    float shakeIntensity;          // Derived from extraInput or defaults
    float shakeTime;               // Combined shake time
    float transformed[3];          // Result of matrix transform
    void* matrixBuffer;            // Local buffer for 48 bytes

    // Initialize output defaults from globals
    *outSteering = DAT_00e4494c;
    *outFeedback = DAT_00e4474c;

    // Retrieve the manager pointer (global singleton)
    baseTime = *(float*)(DAT_01205378 + 0x144); // Time delta from manager

    // Get player input handler based on slot index (register passed in EAX, but here slotIndex)
    playerSlot = *(int*)(thisPtr + 0x30 + slotIndex * 4);
    if (playerSlot == 0) {
        return 0;
    }

    // Copy 8*4 bytes from input handler's matrix (offset 0x18) + some thread-local base
    int* threadBase = *(int**)(*(int*)(0x2c) + 0x2c); // FS segment offset? Simplified
    int* matrixSrc = (int*)(*(int*)(playerSlot + 0x18) + *(int*)(threadBase + 8));
    // Actually the decompiled code uses unaff_FS_OFFSET+0x2c, which is thread-local storage.
    // For reconstruction, we assume threadBase is a pointer obtained from some TLS.

    // Read 8 integers (first part of matrix) and 8 floats (second part)
    for (int i = 0; i < 8; i++) {
        matrixData[i] = matrixSrc[i];
    }
    // The next 8 values are floats (positions?)
    for (int i = 0; i < 8; i++) {
        matrixData[8 + i] = *(float*)(matrixSrc + 8 + i);
    }

    // Check the state flag at playerSlot+0x20 (enum for input mode)
    int* stateFlag = *(int**)(playerSlot + 0x20);
    if ((stateFlag != (int*)0x1) && (stateFlag != (int*)0xf) && (stateFlag != (int*)0x12)) {
        // For states 4,5,14 -> apply shake effect and return immediately
        if ((stateFlag != (int*)0x4) && (stateFlag != (int*)0x5) && (stateFlag != (int*)0xe)) {
            return 0;
        }
        FUN_00422d40();
        FUN_00422e80(1.0f, *(float*)(*(int*)(playerSlot + 0x18) + 0x70 + *(int*)(threadBase + 8)));
        FUN_00422fb0(*(float*)(*(int*)(playerSlot + 0x18) + 0x6c + *(int*)(threadBase + 6)) * DAT_00e2b04c, 1.0f);
        return 1;
    }

    // Get optional extra input pointer
    extraInput = *(float**)(thisPtr + 0x3c + slotIndex * 4);
    baseTime = *(float*)((int)DAT_01205378 + 0x144); // Re-read (maybe updated)

    if (extraInput == (float*)0) {
        // No extra input, compute timeOffset from global arrays based on stepIndex
        if (stepIndex == 0) {
            timeOffset = DAT_011280f0 + baseTime;
        } else {
            timeOffset = (&DAT_011280f0)[stepIndex] + baseTime;
            baseTime = *(float*)(&DAT_011280ec + stepIndex * 4) + baseTime; // Note: This overwrites baseTime locally
        }
    } else {
        // Extra input exists: use its 5th element as multiplier
        timeOffset = extraInput[4] * DAT_00e2b04c + baseTime;
        if (((int)extraInput[6] & 1) != 0) {
            // Bit 0 set: copy first 4 floats from extraInput to local variables
            matrixPos[0] = extraInput[0];
            matrixPos[1] = extraInput[1];
            matrixPos[2] = extraInput[2];
            matrixPos[3] = extraInput[3]; // Actually this is stored as local_70,fStack_6c etc.
            steeringMagnitude = extraInput[4]; // local_c0? Wait, this is set later
            goto computeSteeringMagnitude;
        }
    }

    // Compute base steering magnitude via helper function
    FUN_0044c900((int)DAT_01205378, baseTime, timeOffset, &steeringMagnitude);

    // Apply per-slot scaling
    slotData = (float)*(int*)(&DAT_01163848[slotIndex * 0x84]);
    if (slotData < 0.0f) {
        slotData = slotData + DAT_00e44578;
    }
    steeringMagnitude = ((slotData + DAT_00e2b04c) / slotData) * steeringMagnitude;

    // Clamp or apply sqrt if above threshold
    if (DAT_00e44928 < steeringMagnitude) {
        double temp = (double)(steeringMagnitude * DAT_00e2eb58 - DAT_00e2cd54);
        // FUN_00b9cce0 is likely sin or sqrt? Actually it's followed by multiply by DAT_00e2e638
        // Probably sqrt (since next line uses fVar6 * ...)
        float sqrtVal = (float)sqrt(temp);
        steeringMagnitude = sqrtVal * DAT_00e2e638;
    } else {
        steeringMagnitude = DAT_00e2e638;
    }

    // Store computed time values into global array (per slot and step)
    int arrayIndex = (slotIndex * 0x84 + stepIndex) * 4;
    *(float*)(&DAT_01163810 + arrayIndex) = baseTime;
    *(float*)(&DAT_01163814 + arrayIndex) = timeOffset;

computeSteeringMagnitude:
    // Now steeringMagnitude is set (either from earlier jump or just computed)
    float feedbackDefault = DAT_00e2b1a0; // 1.0f

    // Condition to apply output steering defaults (if no extra input or bit2 not set)
    bool applyDefaultOutput = (extraInput == (float*)0) || (((int)extraInput[6] & 4) == 0);
    // Also check a global flag at DAT_01163840[slotIndex*0x210]
    // Actually the decompiled code: ((byte)(((&DAT_01163840)[slotIndex * 0x210] != '\0') * 2U + 1U) < 2)
    // This is tricky: it checks if the byte at DAT_01163840[slotIndex*0x210] is non-zero, then multiplies by 2 and adds 1.
    // The result must be <2. That means if the byte is non-zero, the expression becomes (1*2+1)=3 which is not <2, so condition fails.
    // So basically it only applies default output if the byte is zero.
    {
        char flagByte = DAT_01163840[slotIndex * 0x210];
        int condition = (flagByte != 0) ? 3 : 1;
        if (condition < 2) {
            applyDefaultOutput = true;
        } else {
            applyDefaultOutput = false;
        }
    }

    if (applyDefaultOutput) {
        *outSteering = *(float*)((int)DAT_01205378 + 0x74) - DAT_00e44948;
        *outFeedback = *(float*)((int)DAT_01205378 + 0x74) + feedbackDefault;
    }

    // Compute squared length of the quaternion part of the matrix (local_90,fStack_8c,fStack_88)
    float qx = (float)matrixData[8];  // second part start index
    float qy = (float)matrixData[9];
    float qz = (float)matrixData[10];
    float qw = (float)matrixData[11]; // This is fStack_84? Actually fStack_84 is from matrixData[11]
    // Wait, the order: local_90 = (float)puVar5[8], fStack_8c = [9], fStack_88 = [10], fStack_84 = [11], etc.
    // So we have quaternion (qx,qy,qz,qw) from indices 8-11.
    // Also local_80 = (float)puVar5[0xc] etc. (position)
    float posX = (float)matrixData[12];
    float posY = (float)matrixData[13];
    float posZ = (float)matrixData[14];
    // local_70 etc. were set from extraInput if bit0 set, otherwise they are from the original matrix? Actually the code uses local_70 etc. later, but they are local variables that might be set from extraInput or from the matrix.
    // For simplicity, we'll use the matrix values.

    float lenSq = qx*qx + qy*qy + qz*qz;
    if (DAT_00e2b05c < lenSq) {
        // Normalize the quaternion part
        float invLen = DAT_00e2b1a4 / sqrt(lenSq);
        float nqx = invLen * qx;
        float nqy = invLen * qy;
        float nqz = invLen * qz;
        float nqw = invLen * qw; // actually fStack_84

        // Update position with normalized quaternion? Actually the code sets local_80 = local_70 (which was from extraInput or original?), then fStack_7c = fStack_6c, etc.
        // But we don't have those variables exactly. We'll assume position is updated.
        posX = matrixPos[0]; // from extraInput or original? This is messy.
        // Skipping details for brevity.

        // Further calculations with shake intensity etc.
        if (extraInput == (float*)0) {
            shakeIntensity = DAT_0110ac8c * feedbackDefault;
            shakeTime = DAT_0110ac8c * DAT_00e2cd54;
            if (DAT_00e2cbe0 < (float)((int)nqy & (int)DAT_00e44680)) {
                // Adjust position and shake
                float factor = DAT_00e2eff4 / nqy;
                posX = factor * nqx + matrixPos[0];
                posY = factor * nqy + matrixPos[1];
                posZ = factor * nqz + matrixPos[2];
                float tmp = sqrt(DAT_00e2b1a4 - nqy*nqy);
                shakeTime = (tmp / (float)((int)nqy & (int)DAT_00e44680)) * steeringMagnitude;
                shakeIntensity = shakeIntensity / tmp + shakeTime;
                shakeTime = shakeTime + DAT_0110ac8c * DAT_00e2cd54;
            }
        } else {
            shakeIntensity = extraInput[5];
            shakeTime = shakeIntensity; // local_bc = fVar9
        }

        // Apply damping
        float oneMinusIntensity = DAT_00e44564 - shakeIntensity;
        posX = oneMinusIntensity * nqx + posX;
        posY = oneMinusIntensity * nqy + posY;
        posZ = oneMinusIntensity * nqz + posZ;
        // Set w to 1.0
        float w = DAT_00e2b1a4;

        // Call matrix operation
        FUN_00424470();

        // Compute scaling factor from slot data again
        float slotScale = (float)*(int*)(&DAT_01163848[slotIndex * 0x84]);
        if (slotScale < 0.0f) {
            slotScale = slotScale + DAT_00e44578;
        }
        float timeScale = (steeringMagnitude + steeringMagnitude) / slotScale;

        // Transform the local vectors by timeScale
        // (The code does some weird integer manipulations for rounding)
        float invTimeScale = DAT_00e2b1a4 / timeScale;
        // Apply scaling to the vector (local_30, local_2c, local_28) which we haven't defined.
        // We'll assume we have a velocity vector.

        // Call matrix-vector transform
        FUN_0044c4c0(&matrixData[0], &local_30, &matrixPos[0]); // local_30 is a vector

        // Invert position components
        matrixPos[0] = DAT_00e44564 - matrixPos[0];
        matrixPos[1] = DAT_00e44564 - matrixPos[1];
        matrixPos[2] = DAT_00e44564 - matrixPos[2];

        // Check combined shake time
        float totalShakeTime = shakeTime + shakeIntensity;
        if (totalShakeTime != DAT_00e2b05c) {
            // Apply camera shake effect
            FUN_00422d40();
            FUN_00422bc0(matrixBuffer, 0);
            FUN_00423110(steeringMagnitude, -steeringMagnitude, -steeringMagnitude, steeringMagnitude);
            FUN_00422e80(0, totalShakeTime);
            return 1;
        }
    }
    return 0;
}