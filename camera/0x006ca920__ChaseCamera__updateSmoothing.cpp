// FUNC_NAME: ChaseCamera::updateSmoothing
// Function address: 0x006ca920
// Reconstructed from Ghidra decompile: camera smoothing/damping with distance-based adaptive damping
void __thiscall ChaseCamera::updateSmoothing(ChaseCamera* this, float deltaTime, const CameraInput* input)
{
    // Many address constants renamed – see comments for original symbols
    enum { OFFSET_DAMP_VEL_X = 0xa8, OFFSET_DAMP_VEL_Y = 0xac };
    enum { OFFSET_CLAMP_MIN_X = 0x74, OFFSET_CLAMP_MIN_Y = 0x78 };

    // Global singletons
    class SimManager* simMgr = *(SimManager**)(*(int*)DAT_012233a0 + 4); // SimManager singleton
    if (!simMgr) return;

    // Pointer to player's base object (offset -0x1f30 from another pointer?)
    int* playerObj = (int*)((char*)simMgr - 0x1f30);
    if (!playerObj) return;

    // Check if game is in a valid mode
    int gameMode = FUN_007a5f40(); // likely "getGameMode()"
    if (gameMode != 2) return; // Only continue in mode 2 (e.g., gameplay)

    // Check if player is in a menu or cutscene
    if (FUN_00481660()) return; // "isPaused()" or "isMenuActive()"

    // Retrieve some input value (likely time-step related)
    float maxTurnRate = input->maxTurnRate; // param_3[7]

    // Get the current camera's position/rotation (through a transform object)
    // Call 0x00425060 -> returns pointer to transform data
    TransformData* camTransform = static_cast<TransformData*>(FUN_00425060(someStackBuffer, 0));
    float posX = camTransform->position.x;
    float posY = camTransform->position.y;
    float posZ = camTransform->position.z; // local_90
    // Convert to a vector for later dot products

    // Another transform from the target entity?
    TransformData* targetTransform = static_cast<TransformData*>(FUN_00424fb0(someStackBuffer, 0));
    Vector3 targetPos = targetTransform->position; // local_d0, local_c8, etc.

    // Determine if there is a current follow-target
    int* followEntity = nullptr;
    if (*(int*)((char*)simMgr + 0x5cc) != 0) {
        followEntity = (int*)(*(int*)((char*)simMgr + 0x5cc) - 0x48); // adjust pointer offset
    }
    int* bestEntity = nullptr;

    // Compute the forward vector (likely from camTransform)
    Vector3 forward; // local_c4, local_bc
    forward.x = camTransform->forward.x;
    forward.y = camTransform->forward.y;
    forward.z = camTransform->forward.z;

    // Store the position of the camera and target for later
    Vector3 camPos = camTransform->position; // local_d0 (lower 4 bytes), local_c8 (upper?)
    // Actually careful: decompiled structure uses high/low splits, but I'll treat as Vector3

    // Compute the dot product: forward·(entityPos - targetPos)
    float dotForward = forward.x * (playerObjPos.x - targetPos.x) + forward.y * (playerObjPos.y - targetPos.y) + forward.z * (playerObjPos.z - targetPos.z);
    // This is fVar16 above

    // Initialize damping accumulators from global statics
    // These appear to be per-frame accumulators for smooth damping
    static float dampingAccelX = 0.0f;
    static float dampingAccelY = 0.0f;
    static int init1 = 0, init2 = 0;
    if ((init1 & 1) == 0) {
        init1 |= 1;
        dampingAccelX = 0.0f; // DAT_0112a7bc
        _atexit(&cleanup1);
    }
    if ((init2 & 1) == 0) {
        init2 |= 2;
        dampingAccelY = 0.0f; // DAT_0112a7b4
        _atexit(&cleanup2);
    }

    // Update dampingAccelX (match DAT_0112a7b0 in decompile)
    {
        int prevEntity = DAT_0112a7bc;
        float prevDist = 0.0f;
        if (prevEntity && (prevEntity - 0x48)) {
            Vector3 prevPos = getPositionFromEntity(prevEntity - 0x48);
            float prevDot = forward.x * (prevPos.x - targetPos.x) + forward.y * (prevPos.y - targetPos.y) + forward.z * (prevPos.z - targetPos.z);
            float threshold = SOME_CONSTANT * SOME_OTHER; // DAT_00e533ec * DAT_00d5f040
            if (prevDot >= threshold) {
                dampingAccelX -= DAMP_RATE * deltaTime; // DAT_00e50fd0
            } else {
                if (prevDot <= dotForward || dotForward <= 0.0f) {
                    dampingAccelX -= DAMP_RATE * deltaTime;
                } else {
                    dampingAccelX += DAMP_ACCEL * deltaTime; // DAT_00e50fd4
                }
            }
            clamp(dampingAccelX, 0.0f, DAMP_MAX); // DAT_00e50fcc
        } else {
            dampingAccelX = 0.0f;
        }
    }

    // Update dampingAccelY similarly (match DAT_0112a7ac)
    {
        // ... similar code for Y axis
        int prevEntityY = DAT_0112a7b4;
        // identical pattern with same constants
    }

    // Compare and possibly swap/select best entity
    // ... (long code selecting between two candidate entities based on damping values)

    // Now compute steering/turn amount
    float steer = 0.0f, throttle = 0.0f;
    FUN_006c9eb0(0, &steer, &throttle, maxTurnRate, maxTurnRate); // compute steering based on input

    float local9c, locala8;
    FUN_006ca770(&local9c, &locala8, input); // compute some intermediate values (maybe turn/bank)

    bool anyInput = (local9c != 0.0 || locala8 != 0.0 || steer != 0.0 || throttle != 0.0);

    // If there is input and a valid bestEntity, check if we should override damping
    if (anyInput && bestEntity) {
        int someState = FUN_006c9440(bestEntity, 0x55859efa); // find some specific entity?
        if (someState) {
            // Check various conditions to modify the input flags (uStack_f4, uStack_e8)
            // ...
        }
    }

    // Compute new damping velocities based on distance and direction
    Vector3 diff = entityPos - camPos; // local_7c,78,74
    float dotForward = forward.x * diff.x + forward.y * diff.y + forward.z * diff.z; // local_a0
    float dotSide = side.x * diff.x + side.y * diff.y + side.z * diff.z; // fVar17

    // Apply speed-dependent damping to the camera's velocity (at this+0xa8 / +0xac)
    // ... many branches involving local9c, locala8, direction signs

    // Modify stored velocities
    this->velX = (1.0f - dampingFactorX) * this->velX; // *(float*)(this+0xa8)
    this->velY = (1.0f - dampingFactorY) * this->velY; // *(float*)(this+0xac)

    // Additional clamping for low speeds (at this+0x74, +0x78)
    if (DAT_00e50fc8) { // some global flag
        float newClampX = (velX - input->minSpeed) / (input->maxSpeed - input->minSpeed) * input->clampFactor;
        if (newClampX < this->minClampX) this->minClampX = newClampX;
        float newClampY = (velY - input->minSpeed) / (input->maxSpeed - input->minSpeed) * input->clampFactor;
        if (newClampY < this->minClampY) this->minClampY = newClampY;
    }

    return;
}