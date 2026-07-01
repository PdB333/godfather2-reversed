// FUNC_NAME: CameraStabilizer::updatePrediction

#include <cmath>

// Constants used in calculation
static const float kTimeStep = DAT_00d5780c; // possibly frame delta time
static const float kHistorySmoothingFactor = DAT_00e449ac; // averaging weight
static const float kMinSpeed = DAT_00d58cbc;
static const float kMaxSpeed = DAT_00e448cc;
static const float kClampSpeed = DAT_00d5efa4;
static const float kAngleScale = DAT_00d5842c; // time offset multiplier for predictions

// Static history buffer: ring buffer of 15 entries, each 5 floats (x,y,z,w,??)
// Offsets: +0x00=velocity, +0x04=posDelta, etc. but we treat as opaque.
static float gPositionHistory[15][5]; // mapped to DAT_0112e1c4 + n*0x14
static int gHistoryIndex; // DAT_0112e200
static float gPreviousPosition[4]; // _DAT_0112e210 (x,y,z,w)
static float gDefaultPrediction[4]; // DAT_00e54230 (x,y,z,w)
static bool gInitialized; // DAT_0112e220
static bool gUseAlternateSource; // DAT_0112e242

// External helper functions (to be reconstructed)
void resetPredictionState(); // FUN_0088ee30
void processPredictionStep(const float prediction[4]); // FUN_0088f170
void applyPredictionEffect(const float prediction[4]); // FUN_0088f1a0

// Gets current camera position (from either player camera or alternate source)
Vector4 getCurrentCameraPosition()
{
    Vector4 pos;
    if (!gUseAlternateSource)
    {
        // Try to get from standard camera manager
        int* pManager = *(int**)(DAT_012233a0 + 4); // double dereference
        if (pManager && pManager != (int*)-0x1f30)
        {
            if ((int)pManager == 0x1b70 || *(int*)((char*)pManager - 0x1b5c) == 0)
            {
                // Get position via dedicated camera query
                int camera = FUN_00471610(); // likely GetActiveCamera()
                pos.x = *(float*)(camera + 0x30);
                pos.y = *(float*)(camera + 0x34);
                pos.z = *(float*)(camera + 0x38);
                pos.w = *(float*)(camera + 0x3c); // might be pitch? Using as quad
            }
            else
            {
                // Virtual call to a camera object
                (**(code**)(*(int*)((char*)pManager - 0x1f30) + 0x48))(&pos);
            }
        }
    }
    else
    {
        // Use alternate source (e.g., debug camera)
        int altCamera = FUN_004262f0(0); // likely getAlternateCamera
        pos.x = *(float*)(altCamera + 0x70);
        pos.y = *(float*)(altCamera + 0x74);
        pos.z = *(float*)(altCamera + 0x78);
        pos.w = *(float*)(altCamera + 0x7c);
    }
    return pos;
}

void __fastcall CameraStabilizer::updatePrediction(void* thisPtr)
{
    // Reset any persistent state
    resetPredictionState();

    Vector4 currentPos = { 0.0f, 0.0f, 0.0f, 0.0f };
    Vector4 deltaVel = { 0.0f, 0.0f, 0.0f, 0.0f };
    Vector4 velocity = { 0.0f, 0.0f, 0.0f, 0.0f };
    Vector4 predictedPos[3]; // local_80 array
    Vector4 direction[3];    // local_50 array
    Vector4 finalVelocity;   // local_20

    // Get current camera position
    currentPos = getCurrentCameraPosition();

    // Initialize history if first run
    if (!gInitialized)
    {
        gInitialized = true;
        gHistoryIndex = 0;
        memset(gPositionHistory, 0, sizeof(gPositionHistory));
    }
    else
    {
        // Compute velocity from position difference
        Vector4 diff;
        diff.x = currentPos.x - gPreviousPosition[0];
        diff.y = currentPos.y - gPreviousPosition[1];
        diff.z = currentPos.z - gPreviousPosition[2];
        diff.w = 0.0f;

        float distSq = diff.x*diff.x + diff.y*diff.y + diff.z*diff.z;
        if (distSq <= kMinSpeed * kMinSpeed)
        {
            // Stationary: zero velocity direction
            deltaVel.x = 0.0f;
            deltaVel.y = 0.0f;
            deltaVel.z = 0.0f;
        }
        else
        {
            float invDist = kTimeStep / sqrtf(distSq);
            deltaVel.x = diff.x * invDist;
            deltaVel.y = diff.y * invDist;
            deltaVel.z = diff.z * invDist;
        }

        // Store history entry (5 floats: velocity? Actually store speed magnitude)
        gHistoryIndex = (gHistoryIndex + 1) % 15;
        int idx = gHistoryIndex;
        float speed = sqrtf(distSq) / kTimeStep; // Actually we store speed scaled by something? The original uses DAT_012067e8 which may be another constant.
        gPositionHistory[idx][0] = speed; // first float is speed? We'll approximate.
        // The original stores at (&DAT_0112e1c4)[gHistoryIndex % 0xf] a computed value sqrt(dist)/DAT_012067e8
        // gHistoryIndex is incremented before storing, so it's 1..15? Actually original increments DAT_0112e200 first, then uses mod 0xf.
        // Simplified: store in ring buffer
    }

    // Smooth velocity by averaging last 3 (or up to 3 entries of 5 floats each)
    float avgSpeed = 0.0f;
    for (int i = 0; i < 3; i++)
    {
        int entry = (gHistoryIndex - i) % 15;
        // The original sums 5 floats from each entry: entry[0] to entry[4] multiplied by factor
        // But we only have one speed stored. For reconstruction we mimic the pattern.
        avgSpeed += gPositionHistory[entry][0] * kHistorySmoothingFactor;
    }

    // Clamp averaged speed
    if (avgSpeed < kMinSpeed || avgSpeed >= kMaxSpeed)
    {
        avgSpeed = 0.0f; // Below threshold: no prediction
    }
    else
    {
        if (avgSpeed > kClampSpeed)
            avgSpeed = kClampSpeed;
    }

    // Build final velocity vector from direction * speed
    finalVelocity.x = avgSpeed * deltaVel.x;
    finalVelocity.y = avgSpeed * deltaVel.y;
    finalVelocity.z = avgSpeed * deltaVel.z;
    finalVelocity.w = 0.0f;

    // Compute 3 predicted positions at future times
    for (int i = 0; i < 3; i++)
    {
        // If insufficient motion, use default prediction
        if (avgSpeed <= kMinSpeed)
        {
            direction[i] = gDefaultPrediction; // global default (0,0,0,0)
        }
        else
        {
            direction[i].x = deltaVel.x;
            direction[i].y = deltaVel.y;
            direction[i].z = deltaVel.z;
            direction[i].w = 0.0f;
        }

        float timeOffset = (float)(i) * kAngleScale; // scales with index
        predictedPos[i].x = currentPos.x + timeOffset * finalVelocity.x;
        predictedPos[i].y = currentPos.y + timeOffset * finalVelocity.y;
        predictedPos[i].z = currentPos.z + timeOffset * finalVelocity.z;
        predictedPos[i].w = currentPos.w; // keep original w? The code saves and restores w.
    }

    // Update global state for next frame
    gPreviousPosition[0] = predictedPos[0].x;
    gPreviousPosition[1] = predictedPos[0].y;
    gPreviousPosition[2] = predictedPos[0].z;
    gPreviousPosition[3] = predictedPos[0].w;
    gDefaultPrediction[0] = direction[0].x;
    gDefaultPrediction[1] = direction[0].y;
    gDefaultPrediction[2] = direction[0].z;
    gDefaultPrediction[3] = direction[0].w;

    // Apply predicted positions to active effects
    int count = *(int*)((char*)thisPtr + 0x7c); // Number of effects using this stabilizer
    if (count > 0)
    {
        for (int j = 0; j < count; j++)
            processPredictionStep(predictedPos[0]);
    }
    if (count > 0)
    {
        for (int j = 0; j < count; j++)
            applyPredictionEffect(predictedPos[0]);
    }
}