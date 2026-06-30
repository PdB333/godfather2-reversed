// FUNC_NAME: steeringComputeSteeringForce
// Address: 0x005f6ae0
// Purpose: Computes steering force/position for an agent to arrive at a target while avoiding obstacles.
//          Recursively refines path when agent is blocked. Uses radii and angular interpolation.

struct ObstacleInfo {
    float x;       // +0x10
    float y;       // +0x14
    float radius;  // +0x18
    // Other fields not used here
};

struct ExtraObjInfo {
    int* objPtr;   // +0x0c (pointer to another object with radius at +0x18)
};

// Global constants (from DAT addresses)
static const float g_const1 = 1.0f; // DAT_00e2b1a4 (probably 1.0)
static const float g_altConst = 0.5f; // DAT_00e2eff4 (alternate constant)
static const float g_radToAngleFactor = 0.01745329252f; // DAT_00e2b294 (approx 1/57.2958, to convert radians to degrees? Unclear)
static const float g_distanceMultiplier = 1.0f; // _DAT_00e407a0 (probably 1.0)
static const unsigned int g_signMask = 0x7FFFFFFF; // DAT_00e44680 (sign mask for float)
static const float g_smallValue = 0.0001f; // DAT_00e44810 (epsilon)
static const float g_pi = 3.14159265f; // DAT_00e44808 (π)
static const float g_halfPi = 1.57079633f; // _DAT_00e44804 (π/2)
static const float g_twoPi = 6.28318531f; // DAT_00e44644 (2π)

// Math helpers (replace with actual sinf/cosf etc.)
float dblSin(double angle);
float dblCos(double angle);
void FUN_00b9b988(); // sin? (double)
void FUN_00b9c766(); // cos? (double)
void FUN_00b99fcb(); // atan2? (double) returns sin/cos?
void FUN_00b99e20(); // atan2? (double)

// Forward declaration of obstacle check function (FUN_005f6ee0)
int obstacleCheck(float* agentPos, float* targetPos, ObstacleInfo* obstacle, ExtraObjInfo* extra);

float* steeringComputeSteeringForce(float* outPos, float* inOutAgentPos, float* targetPos, 
                                    ObstacleInfo* obstacle, ExtraObjInfo* extra,
                                    int recursionDepth, char useAltConst, char doProjection)
{
    float fVar1, fVar2, fVar3, fVar4, fVar5;
    float fVar11, fVar12;
    float dx, dy;
    float distSq, dist;
    bool bProjected;
    int newObstacleIdx;
    float* retPos;
    float local_40;       // obstacle radius (possibly combined)
    float local_3c;       // angular factor
    float local_30[2];    // temporary position
    float local_28, local_24;  // difference components
    float local_1c, local_18;  // dot product components

    // --- Step 1: Set up obstacle radius ---
    local_40 = obstacle->radius;
    if (extra->objPtr != NULL) {
        // Add radius of another object (if exists)
        local_40 += ((ObstacleInfo*)(extra->objPtr))->radius;
    }

    // --- Step 2: Compute differences between agent and obstacle center ---
    fVar1 = inOutAgentPos[1];          // agent.y
    fVar2 = targetPos[1];              // target.y
    fVar3 = inOutAgentPos[0];          // agent.x
    fVar4 = obstacle->x;
    fVar5 = targetPos[0];              // target.x
    local_24 = fVar1 - obstacle->y;    // agent.y - obstacle.y
    fVar11 = fVar2 - obstacle->y;      // target.y - obstacle.y
    local_28 = fVar3 - fVar4;         // agent.x - obstacle.x

    // --- Step 3: Choose angular factor based on parameter ---
    local_3c = g_const1;               // DAT_00e2b1a4 (usually 1.0)
    if (useAltConst != 0) {
        local_3c = g_altConst;         // DAT_00e2eff4 (alternate factor)
    }

    // --- Step 4: Distance from agent to obstacle center squared ---
    fVar12 = local_24 * local_24 + local_28 * local_28;
    *outPos = 0.0f;
    outPos[1] = 0.0f;
    bProjected = false;

    // --- Step 5: If target is within obstacle radius and doProjection flag is set ---
    float distTarget = sqrtf(fVar11 * fVar11 + (fVar5 - fVar4) * (fVar5 - fVar4));
    if ((distTarget < local_40) && (doProjection != 0)) {
        fVar5 = targetPos[0];
        local_1c = fVar3 - fVar5;                 // agent.x - target.x
        local_18 = fVar1 - targetPos[1];          // agent.y - target.y
        // Check if agent is moving toward obstacle (dot product with direction from obstacle to target)
        bProjected = ((obstacle->y - targetPos[1]) * local_18 + (fVar4 - fVar5) * local_1c) <= 0.0f;
        if (bProjected) {
            // If projected, set output to target position
            *outPos = fVar5;
            outPos[1] = fVar2;
        }
    }

    // --- Step 6: If agent is too close to obstacle (distance < radius), push agent away ---
    float distanceToObs = sqrtf(fVar12);
    local_30[0] = distanceToObs;
    if (distanceToObs < local_40) {
        dist = sqrtf(fVar12);
        // Avoid division by zero: if dist is very small, set to 1.0
        if ((double)(float)((unsigned int)dist & g_signMask) < (double)g_smallValue) {
            dist = 1.0f;
        }
        // Push agent directly away from obstacle along the normal direction
        local_24 = (g_const1 / dist) * local_24 * local_40 * g_distanceMultiplier;
        local_28 = (g_const1 / dist) * local_28 * local_40 * g_distanceMultiplier;
        inOutAgentPos[0] = fVar4 + local_28;   // new agent.x = obstacle.x + offset*normal.x
        inOutAgentPos[1] = obstacle->y + local_24; // new agent.y = obstacle.y + offset*normal.y
    }

    // --- Step 7: Determine if agent is far enough to compute angular interpolation ---
    if (local_40 * g_distanceMultiplier <= local_30[0]) {
        // Agent is outside the critical zone: use angular interpolation (arrive via arc)
        if (!bProjected) {
            // Compute angle from obstacle to current agent direction
            local_30[0] = g_const1 / local_30[0]; // 1/distance
            double dAngle1 = (double)(local_30[0] * local_40); // arcsin? Actually used with sin/cos later
            double sinVal = dblSin(dAngle1); // FUN_00b9b988
            double dAngle2 = (double)((float)((unsigned int)local_28 & g_signMask) * local_30[0]); // normal.x * 1/dist
            double cosVal = dblCos(dAngle2); // FUN_00b9c766
            local_30[0] = (float)cosVal;
            // Convert angle to correct quadrant based on signs of difference
            if ((local_28 <= 0.0f) || (0.0f <= local_24)) {
                if (local_28 < 0.0f) {
                    if (0.0f <= local_24) {
                        if (0.0f < local_24) {
                            local_30[0] = (g_pi - local_30[0]) + g_halfPi;
                        }
                    } else {
                        local_30[0] = local_30[0] + g_twoPi;
                    }
                }
            } else {
                local_30[0] = (g_pi - local_30[0]) + g_pi;
            }
            // Add angular offset and compute new position on circle
            local_30[0] = (float)dAngle1 * local_3c + local_30[0];
            double finalAngle = (double)local_30[0];
            float sinFinal = sinf((float)finalAngle); // FUN_00b99fcb (sinf)
            *outPos = sinFinal * local_40 * g_radToAngleFactor + obstacle->x;
            float cosFinal = cosf((float)finalAngle); // FUN_00b99e20 (cosf)
            outPos[1] = cosFinal * local_40 * g_radToAngleFactor + obstacle->y;
        }
    } else {
        // Agent is very close: simply move along the tangent direction (linear steering)
        float fVar1 = inOutAgentPos[1];
        *outPos = local_3c * local_24 + inOutAgentPos[0];
        outPos[1] = fVar1 - local_3c * local_28;
    }

    // --- Step 8: Recursive refinement if recursion depth < 5 and obstacle check finds new obstacle ---
    if ((recursionDepth < 5) && 
        (newObstacleIdx = obstacleCheck(inOutAgentPos, outPos, obstacle, extra, *(int*)(obstacle + 0xc)),
         newObstacleIdx != 0)) {
        retPos = steeringComputeSteeringForce(local_30, inOutAgentPos, outPos, 
                                              (ObstacleInfo*)newObstacleIdx, extra,
                                              recursionDepth + 1, useAltConst, 0);
        // Copy recursive result to output
        *outPos = *retPos;
        outPos[1] = retPos[1];
    }

    return outPos;
}