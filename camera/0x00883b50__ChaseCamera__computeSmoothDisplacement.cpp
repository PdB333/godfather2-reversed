// FUNC_NAME: ChaseCamera::computeSmoothDisplacement
void __thiscall ChaseCamera::computeSmoothDisplacement(float *outDelta, float *inWorldPos)
{
    // static timing globals (likely from engine time manager)
    static float sPrevTime = gInitialTime;   // DAT_0112e1a4
    static uint32_t sTimeInitFlag = 0;      // _DAT_0112e1a8

    // zero output
    outDelta[0] = 0.0f;
    outDelta[1] = 0.0f;
    outDelta[2] = 0.0f;
    outDelta[3] = 0.0f;

    // get frame time manager (FUN_00471610) – returns pointer to a time/velocity struct
    int *timeMgr = getTimeManager();                     // FUN_00471610()
    // Negate the velocity/position offset from the time manager (+0x10,0x14,0x18)
    float negVelX = 0.0f - *(float *)(timeMgr + 0x10);  // -vel.x
    float negVelY = 0.0f - *(float *)(timeMgr + 0x14);  // -vel.y
    float negVelZ = 0.0f - *(float *)(timeMgr + 0x18);  // -vel.z
    float negDt   = 0.0f - gTimeDelta;                  // -_DAT_00d5780c

    // One-time initialization of static previous time
    if ((sTimeInitFlag & 1) == 0) {
        sTimeInitFlag |= 1;
        sPrevTime = gInitialTime;               // _DAT_00d5c458
    }

    float dt = gCurrentTime - sPrevTime;         // _DAT_00e44564 - _DAT_0112e1a4

    // Two candidate positions:
    // 1) Using the current frame delta (dt)
    float posCandidate1_x = dt * negVelX + inWorldPos[0];
    float posCandidate1_y = dt * negVelY + inWorldPos[1];
    float posCandidate1_z = dt * negVelZ + inWorldPos[2];
    float posCandidate1_w = dt * negDt  + inWorldPos[3];

    // 2) Using the stored previous time
    float posCandidate2_x = sPrevTime * negVelX + inWorldPos[0];
    float posCandidate2_y = sPrevTime * negVelY + inWorldPos[1];
    float posCandidate2_z = sPrevTime * negVelZ + inWorldPos[2];
    float posCandidate2_w = sPrevTime * negDt  + inWorldPos[3];

    // Duplicate for later use
    float hitPos1_x = posCandidate1_x;
    float hitPos1_y = posCandidate1_y;
    float hitPos1_z = posCandidate1_z;
    float hitPos2_x = posCandidate2_x;
    float hitPos2_y = posCandidate2_y;
    float hitPos2_z = posCandidate2_z;

    // Perform a sweep test (FUN_00542650) to adjust positions based on collision
    // Arguments: two points, flags (0x40102), mask (20000h if flag bit at +0x74 is set)
    int flags = *(uint32_t *)(this + 0x74);              // +0x74: m_flags
    int layerMask = ( -((flags >> 1 & 1) != 0) & 0xFFFF0000 ) + 0x20000;
    SweepTest(&hitPos1_x, &hitPos2_x, 0x40102, layerMask, 0, 0); // FUN_00542650

    // Prepare debug draw structure (FUN_009e5ed0)
    // local_d0 points to a static function table PTR_FUN_00e32a8c
    static void **sDebugFuncTable = &PTR_FUN_00e32a8c; // undefined **local_d0
    // local_ac, local_a0, local_80, local_cc etc. – not fully used
    int dummy[23];                                     // local_60 [92] bytes
    float timeFromSweep = gTimeDelta;                  // local_cc = _DAT_00d5780c
    float hitTime = gTimeDelta;                        // local_b0 = _DAT_00d5780c
    int hitFound = 0;                                  // local_70
    DebugDrawCheck(dummy, &sDebugFuncTable);           // FUN_009e5ed0

    // If a collision was found (hitFound != 0)
    if (hitFound != 0) {
        // Clamp hitTime to non‑negative
        if (hitTime > 0.0f) {
            if (gTimeDelta <= hitTime) {
                return; // time already passed, no adjustment
            }
            // else fall through to apply the adjustment
        } else {
            hitTime = 0.0f; // negative time -> no offset
        }

        // Adjust the first candidate position by the hitTime along the velocity direction
        hitPos1_x += hitTime * negVelX;
        hitPos1_y += hitTime * negVelY;
        hitPos1_z += hitTime * negVelZ;
        hitPos1_w += hitTime * negDt;

        // Store the adjusted position as the output delta (relative to input world)
        outDelta[0] = hitPos1_x;
        outDelta[1] = hitPos1_y;
        outDelta[2] = hitPos1_z;
        outDelta[3] = hitPos1_w;

        // Convert to delta by subtracting the input world position
        float wpx = inWorldPos[0];
        float wpy = inWorldPos[1];
        float wpz = inWorldPos[2];
        float wpw = inWorldPos[3];
        outDelta[0] = hitPos1_x - wpx;
        outDelta[1] = hitPos1_y - wpy;
        outDelta[2] = hitPos1_z - wpz;
        outDelta[3] = hitPos1_w - wpw;
    }
}