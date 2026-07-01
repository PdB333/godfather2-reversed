// FUNC_NAME: CameraSmoother::computeSmoothedOffset
// Function address: 0x007ba7e0
// This function computes a smoothed camera offset using different interpolation modes.
// It reads current camera data from a global structure, applies damping factors, and stores the result.

#include <cmath>

// Forward declaration of the function that returns a pointer to camera data.
void* getCameraData(); // FUN_00471610

// Constants (likely from .data section)
extern float g_targetCenter;    // DAT_00e44564 - Desired center/focus point
extern float g_dampingA;        // DAT_00e52f30 - Damping factor for mode 0
extern float g_dampingB;        // DAT_00e52f2c - Damping factor for mode 1
extern float g_dampingC;        // DAT_00e52f28 - Damping factor for mode 2
extern float g_dampingD;        // DAT_00e52f24 - Damping factor for mode 3

// Structure representing camera data fields
// The pointer from getCameraData points to this.
struct CameraData {
    // ... other fields ...
    float currentX; // +0x30 (low part of 8-byte read)
    float currentY; // +0x34 (high part of 8-byte read)
    float currentZ; // +0x38
    // Possibly more fields at +0x20 and +0x28 for other data?
};

// Main interpolation function
// param_1: output array (float[7]) where:
//   [0] = offsetX, [1] = offsetY, [2] = offsetZ
//   [3] = targetX, [4] = targetY, [5] = targetZ
//   [6] = squared distance from current to new offset
// param_2: interpolation mode (0,1,2,3)
// Returns: pointer to camera data for mode 0, output array for others (or original mode for mode 3)
float* computeSmoothedOffset(float* output, int mode)
{
    // Get current camera data twice (note: both calls return same pointer, but code uses separate locals)
    void* camData0 = getCameraData();
    double packedXY0 = *(double*)((char*)camData0 + 0x30); // reads currentX, currentY as double
    float currentZ0 = *(float*)((char*)camData0 + 0x38);

    void* camData1 = getCameraData();
    double packedXY1 = *(double*)((char*)camData1 + 0x30); // reads again
    float currentZ1 = *(float*)((char*)camData1 + 0x38);

    // Extract current position from the doubles
    float curX0 = (float)packedXY0;               // low 32 bits
    float curY0 = (float)((unsigned long long)packedXY0 >> 32); // high 32 bits
    float curX1 = (float)packedXY1;
    float curY1 = (float)((unsigned long long)packedXY1 >> 32);

    // Local variables that accumulate offset
    float offsetX = curX0;   // local_24
    float offsetY = curY0;   // fStack_20
    float offsetZ = curZ0;   // fVar9

    // Another set (likely from previous frame or target)
    float prevOffsetX = curX1; // local_18
    float prevOffsetY = curY1; // fStack_14
    float prevOffsetZ = curZ1; // fVar8

    // Temporary variables for mode-specific calculations
    float tempX, tempY, tempZ; // local_c, fStack_8, etc.

    switch (mode) {
    case 0:
        {
            // Mode 0: Lerp from current to target using dampingA
            void* camData = getCameraData();
            float desiredX = *(float*)((char*)camData + 0x20); // targetX? (low part)
            float desiredY = *(float*)((char*)camData + 0x24); // targetY? (high part of double at +0x20)
            float desiredZ = *(float*)((char*)camData + 0x28); // targetZ

            // Compute offset from target to desired? Actually code does: targetCenter - desired
            float targetMinusDesiredX = g_targetCenter - desiredX;
            float targetMinusDesiredY = g_targetCenter - desiredY;
            float targetMinusDesiredZ = g_targetCenter - desiredZ;

            // New offset = dampingA * (target - desired) + previous offset
            offsetX = g_dampingA * (targetMinusDesiredX - offsetX) + offsetX; // see code: fVar3*(fVar2 - param_1[3]) + local_24
            offsetY = g_dampingA * (targetMinusDesiredY - offsetY) + offsetY; // similar for Y
            offsetZ = g_dampingA * (targetMinusDesiredZ - offsetZ) + offsetZ; // for Z

            // Also store desired values as output[3..5]
            output[3] = desiredX;
            output[4] = desiredY;
            output[5] = desiredZ;

            // Update prev offset (local_18 etc.) based on offset
            float diffX = prevOffsetX - offsetX; // local_18 = local_18 - local_24
            float diffY = prevOffsetY - offsetY;
            float diffZ = prevOffsetZ - offsetZ;

            // Store final offset and squared distance
            output[0] = offsetX;
            output[1] = offsetY;
            output[2] = offsetZ;
            output[6] = diffX*diffX + diffY*diffY + diffZ*diffZ;

            return (float*)camData; // return camera data pointer (original pfVar6)
        }

    case 1:
        {
            // Mode 1: Lerp using dampingB, and target is g_targetCenter
            void* camData = getCameraData();
            double desiredXY = *(double*)((char*)camData + 0x20); // packed desired X,Y
            float desiredZ = *(float*)((char*)camData + 0x28);

            float desireX = (float)desiredXY;
            float desireY = (float)((unsigned long long)desiredXY >> 32);

            // Compute target - desired (but here code sets output[3..5] = target - desired)
            output[3] = g_targetCenter - desireX; // param_1[3] = DAT_00e44564 - local_c
            output[4] = g_targetCenter - desireY; // param_1[4] = fVar3 - fStack_8
            output[5] = g_targetCenter - desiredZ; // param_1[5] = fVar3 - fVar2

            // New offset = dampingB * desired + accumulated offset
            offsetX = g_dampingB * desireX + offsetX; // fVar4 * local_c + local_24
            offsetY = g_dampingB * desireY + offsetY; // fStack_8 * fVar4 + fStack_20 (note: fStack_8 is desireY)
            offsetZ = g_dampingB * desiredZ + offsetZ; // fVar2 * fVar4 + fVar9

            float diffX = prevOffsetX - offsetX;
            float diffY = prevOffsetY - offsetY;
            float diffZ = prevOffsetZ - offsetZ;

            output[0] = offsetX;
            output[1] = offsetY;
            output[2] = offsetZ;
            output[6] = diffX*diffX + diffY*diffY + diffZ*diffZ;

            return output; // return output array
        }

    case 2:
        {
            // Mode 2: Lerp using dampingC, target is g_targetCenter
            void* camData = getCameraData();
            double desiredXY = *(double*)((char*)camData + 0x20); // packed
            float desiredZ = *(float*)((char*)camData + 0x28);

            float desireX = (float)desiredXY;
            float desireY = (float)((unsigned long long)desiredXY >> 32);

            output[3] = g_targetCenter - desireX;
            output[4] = g_targetCenter - desireY;
            output[5] = g_targetCenter - desiredZ;

            offsetX = g_dampingC * desireX + offsetX;
            offsetY = g_dampingC * desireY + offsetY;
            offsetZ = g_dampingC * desiredZ + offsetZ;

            float diffX = prevOffsetX - offsetX;
            float diffY = prevOffsetY - offsetY;
            float diffZ = prevOffsetZ - offsetZ;

            output[0] = offsetX;
            output[1] = offsetY;
            output[2] = offsetZ;
            output[6] = diffX*diffX + diffY*diffY + diffZ*diffZ;

            return output;
        }

    case 3:
        {
            // Mode 3: Lerp using dampingD, target is g_targetCenter
            void* camData = getCameraData();
            double desiredXY = *(double*)((char*)camData + 0x20); // packed
            float desiredZ = *(float*)((char*)camData + 0x28);

            // Here, output[3..5] are set directly from the data (not target - desired)
            output[3] = (float)desiredXY; // low part
            output[4] = (float)((unsigned long long)desiredXY >> 32); // high part
            output[5] = desiredZ;

            // New offset = dampingD * (target - desired) + accumulated
            offsetX = g_dampingD * (g_targetCenter - output[3]) + offsetX;
            offsetY = g_dampingD * (g_targetCenter - output[4]) + offsetY;
            offsetZ = g_dampingD * (g_targetCenter - output[5]) + offsetZ;

            float diffX = prevOffsetX - offsetX;
            float diffY = prevOffsetY - offsetY;
            float diffZ = prevOffsetZ - offsetZ;

            output[0] = offsetX;
            output[1] = offsetY;
            output[2] = offsetZ;
            output[6] = diffX*diffX + diffY*diffY + diffZ*diffZ;

            return (float*)mode; // returns the mode cast to float* (odd, but matches code)
        }

    default:
        // Unreachable? If param_2 is not 0-3, fall through (code has no default)
        return (float*)mode;
    }
}