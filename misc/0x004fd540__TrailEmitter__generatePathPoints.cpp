// FUNC_NAME: TrailEmitter::generatePathPoints
#include <cmath>

// Class TrailEmitter - generates a sequence of points forming a particle trail with pseudo-random perturbation.
// Layout:
// this+0x20: Vector3 velocity (initial direction, magnitude used for scaling)
// this+0x60: Pointer to buffer for output points (each point: 16 bytes: float x[0], float y[4], float z[8], uint32_t extra[12])
// this+0x68: int32 outputCount (number of points generated)
// this+0x64: int32 maxPoints (expected number of points)
// param_1: some object (likely a random source) with at +0x28 a pointer to a table, +0x6c modulus

// Constants from globals (guessed names, replace with actual ones from data analysis)
extern float g_maxTrailLength; // DAT_00e2b1a4  (e.g., 1.0f)
extern float g_perturbScale;   // DAT_00e2b04c
extern float g_gravityFactor;  // DAT_00e2cd54
extern float g_threshold1;     // DAT_00e2b198
extern float g_minClamp;       // DAT_00e2eff4
extern float g_maxClamp;       // DAT_00e44564
extern float g_derivative;     // DAT_00e2b05c

// Random state globals
extern int32_t g_randomIndex;   // DAT_0119478c
extern float g_randomArray[20]; // DAT_01194790 (0x50 bytes)

// Helper: replaces FUN_004e41b0 - probably advances the random generator
extern void advanceRandomState(); 

void __thiscall TrailEmitter::generatePathPoints(void* thisObj, void* param_1, float param_2)
{
    int32_t maxPoints = *(int32_t*)((char*)thisObj + 0x64);  // +0x64
    if (maxPoints <= 1) maxPoints = 1; // avoid division by zero
    float step = g_maxTrailLength / (float)(maxPoints - 1);
    float perturbationAmount = step * g_perturbScale;
    float gravityAmount = step * g_gravityFactor;

    // Compute velocity magnitude and scale param_2
    float vx = *(float*)((char*)thisObj + 0x20);
    float vy = *(float*)((char*)thisObj + 0x24);
    float vz = *(float*)((char*)thisObj + 0x28);
    float speed = sqrtf(vx*vx + vy*vy + vz*vz);
    param_2 *= speed;

    float accumulatedX = 0.0f;   // local_24
    float accumulatedY = 0.0f;   // local_20
    float accumulatedZ = 0.0f;   // local_2c
    float leftover = 0.0f;       // local_28

    float* buffer = *(float**)((char*)thisObj + 0x60); // +0x60
    int32_t outputCount = 0;     // *(this+0x68)
    *(int32_t*)((char*)thisObj + 0x68) = 0;

    int32_t bufferIndex = 0;      // iVar3 in original (steps by 16)
    int32_t earlyIndex = 0;       // local_1c used for early termination

    while (earlyIndex < maxPoints)
    {
        // Write current accumulated values to buffer
        buffer[bufferIndex + 2] = accumulatedX; // z? Actually layout: offset 8 = x? see below
        buffer[bufferIndex]     = accumulatedY; // offset 0 = y?
        buffer[bufferIndex + 1] = accumulatedZ; // offset 4 = z?
        // Original: *(float *)(iVar3 + 8 + buffer) = accumX; *(float *)(iVar3+0) = accumY; *(float *)(iVar3+4) = accumZ;
        // So index 0: y, index 1: z, index 2: x? That's strange. Possibly axis order different.
        // We'll keep as is: buffer[0]=y, buffer[1]=z, buffer[2]=x. But to be clearer, we assume a Vec3 struct at each point.
        // Let's comment.

        // Pseudo-random number generation: update the LCG state
        int32_t idxPrev = g_randomIndex - 1;
        if (idxPrev < 0) idxPrev = 19; // 0x13
        int32_t idxNext = g_randomIndex + 2;
        if (idxNext > 19) idxNext = g_randomIndex - 18; // 0x13 - 0x12 = 1? Actually original uses 0x13=19, so wrap.
        g_randomArray[idxPrev] = g_randomArray[idxPrev] + g_randomArray[idxNext];
        float randomVal = g_randomArray[idxPrev];
        g_randomIndex = idxPrev;

        // Compute a random integer modulo from param_1's table
        uint32_t* tablePtr = *(uint32_t**)((char*)param_1 + 0x28);
        uint32_t modulus = *(uint32_t*)(tablePtr + 0x6c / 4); // +0x6c (use offset /4 as array)
        uint32_t randomInt = (uint32_t)randomVal % modulus;
        *(uint32_t*)(buffer + bufferIndex + 3) = randomInt; // offset 12 (0xc) in original

        // Check if accumulatedX exceeds max length (early termination)
        if (g_maxTrailLength <= accumulatedX)
        {
            // Terminate early: set the last point at max length and zero others
            earlyIndex = earlyIndex * 16; // *0x10
            buffer[earlyIndex + 2] = g_maxTrailLength; // x
            buffer[earlyIndex]     = 0.0f;             // y
            buffer[earlyIndex + 1] = 0.0f;             // z
            *(int32_t*)((char*)thisObj + 0x68) = outputCount + 1; // increment output count
            return;
        }

        // Second random step
        g_randomIndex = idxPrev - 1;
        if (g_randomIndex < 0) g_randomIndex = 19;
        idxNext = idxPrev + 2;
        if (idxNext > 19) idxNext = idxPrev - 18;
        g_randomArray[g_randomIndex] = g_randomArray[g_randomIndex] + g_randomArray[idxNext];

        // Compute a random value in range [perturbationAmount, perturbationAmount?]
        float rand01 = (g_randomArray[g_randomIndex] & 0x7FFFFF) | 0x3F800000; // reinterpret as float in [1,2) - but careful: it's bitwise.
        // Original: ((stuff) - g_maxTrailLength) * (fVar4 - fVar8) + fVar8
        float fVar5 = (perturbationAmount - gravityAmount) * ((rand01) - g_maxTrailLength) + gravityAmount;
        // Actually: fVar4 - fVar8 and fVar8, but we'll follow the logic.
        if (0.0f < accumulatedZ) // if z positive? Probably a condition.
        {
            fVar5 += accumulatedZ;
        }

        // Update leftover and accumulatedX
        leftover = step - fVar5;
        if (leftover < 0.0f) leftover = 0.0f;
        accumulatedX = fVar5 + accumulatedX;

        // Now various branches to compute deltas for accumulatedY and accumulatedZ
        float deltaY, deltaZ; // local_30 for y, and fVar6 for z
        if (accumulatedX <= g_threshold1) // threshold1
        {
            if (accumulatedY <= g_maxTrailLength)
            {
                if (g_minClamp <= accumulatedY)
                {
                    float temp = g_minClamp;
                    advanceRandomState();
                    float temp2 = g_maxTrailLength - temp * g_perturbScale;
                    deltaY = temp2 * param_2;
                }
                else
                {
                    float temp = g_minClamp;
                    advanceRandomState();
                    deltaY = temp * param_2;
                }
                // Now handle deltaZ
                if (g_maxTrailLength < accumulatedZ) goto branch1;
                if (accumulatedZ < g_minClamp) goto branch2;
                float temp = accumulatedZ;
                advanceRandomState();
                float temp2 = g_maxTrailLength - temp * g_perturbScale;
                deltaZ = temp2 * param_2;
            }
            else // accumulatedY > g_maxTrailLength
            {
                float temp = accumulatedX;
                advanceRandomState();
                float temp2 = g_derivative - temp * param_2;
                deltaY = temp2;
                // Now handle deltaZ
                if (accumulatedZ <= g_derivative) // g_derivative? Actually g_derivative is g_0x5c, maybe different.
                {
branch2:
                    float temp = accumulatedZ;
                    advanceRandomState();
                    float temp2 = g_maxTrailLength - temp * g_perturbScale;
                    deltaZ = temp2 * param_2;
                }
                else
                {
                    float temp = accumulatedZ;
                    advanceRandomState();
                    float temp2 = g_derivative - temp * param_2;
                    deltaZ = temp2;
                }
            }
        }
        else // accumulatedX > g_threshold1
        {
            if (accumulatedY <= 0.0f)
            {
                float temp = accumulatedX;
                advanceRandomState();
                deltaY = temp * param_2;
            }
            else
            {
                float temp = accumulatedX;
                advanceRandomState();
                float temp2 = g_derivative - temp * param_2;
                deltaY = temp2;
            }
            // Handle deltaZ
            if (accumulatedZ <= g_derivative)
            {
branch1:
                float temp = accumulatedZ;
                advanceRandomState();
                float temp2 = g_derivative - temp * param_2;
                deltaZ = temp2;
            }
            else
            {
                float temp = accumulatedZ;
                advanceRandomState();
                float temp2 = g_derivative - temp * param_2;
                deltaZ = temp2;
            }
        }

        // Update accumulated positions
        accumulatedY += deltaY;
        accumulatedZ += deltaZ;

        outputCount = *(int32_t*)((char*)thisObj + 0x68) + 1;
        *(int32_t*)((char*)thisObj + 0x68) = outputCount;
        earlyIndex++;
        bufferIndex += 4; // 0x10/4 = 4 floats per point
    }

    // After loop, fill last point with max length
    buffer[outputCount * 4 - 4 + 2] = g_maxTrailLength; // offset 8
    buffer[outputCount * 4 - 4]     = 0.0f;              // offset 0
    buffer[outputCount * 4 - 4 + 1] = 0.0f;              // offset 4
}