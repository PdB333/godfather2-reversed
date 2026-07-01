// FUNC_NAME: SightComponent::checkLineOfSight
// Description: Performs a line-of-sight check from this entity toward a target.
// Returns 1 if sight is clear (with result position), 0 otherwise.
// Uses a random dice to simulate imperfect awareness (e.g., random chance to “not see” even if clear).
// Member fields:
//   +0x10 m_objectHandle   : some ID/handle for the entity (used in raycast)
//   +0x14 m_losTimer       : float – cooldown/reset timer
//   +0x18 m_losState       : int – 0=unset, 1=clear, 2=blocked
// Globals:
//   DAT_01205228           : min offset / threshold for timer
//   _DAT_00d5c458          : random probability threshold (compared with rand*globalScale)
//   _DAT_00d69a64          : timer increment constant
//   _DAT_00d69a68          : spatial offset added to query position
//   _DAT_00d5780c          : some constant (possibly sentinel or default value)
//   PTR_FUN_00e32a8c      : vtable pointer for a raycast result class

int __thiscall SightComponent::checkLineOfSight(int this, int target, uint flags1, uint flags2, Vector3* outPos)
{
    WorldManager* world;
    int state;
    int randVal;
    float probScale;
    Vector3 startPoint;
    Vector3 localPoint;
    double dLocalDc;          // concatenation of two floats (used as input to physics)
    double dLocalE8;          // another concatenated double
    float fStack_f0;
    float fStack_e4;
    RaycastResult result;     // stack buffer + vtable pointer
    int initStatus;

    if (target == 0)
        return 0;

    world = getPhysicsWorld();

    // If the line-of-sight state is unset or if the timer has expired, re-evaluate
    if (*(int*)(this + 0x18) == 0 ||
        (*(float*)(this + 0x14) <= DAT_01205228 && DAT_01205228 != *(float*)(this + 0x14)))
    {
        // Dice‑roll to decide whether the state should be “clear” or “blocked”
        randVal = rand();
        probScale = (float)randVal * DAT_00e44590;     // DAT_00e44590 is a constant (0.0..1.0 scale)
        if (probScale <= _DAT_00d5c458)
            *(int*)(this + 0x18) = 1;   // clear
        else
            *(int*)(this + 0x18) = 2;   // blocked

        // Reset the timer to current time + some offset
        *(float*)(this + 0x14) = DAT_01205228 + _DAT_00d69a64;
    }

    // Obtain the target's world position (fills startPoint with x,y,z)
    getTargetWorldPosition(target, flags1, flags2, &startPoint);

    // Build a double‑encoded query point from the start point:
    //   low 32 bits = startPoint.x
    //   high 32 bits = startPoint.y + offset
    dLocalDc = __builtin_avr_insert_bits(startPoint.y + _DAT_00d69a68, (double)startPoint.x); // CONCAT44
    // Actually in x86, this would be: dLocalDc = (double)(((uint64_t)(startPoint.y + offset) << 32) | (uint32_t)startPoint.x);

    // Get the physics world's transformation (likely a position) from the world manager
    // The world stores some transform at offsets +0x30 and +0x38
    uint64_t worldTransform = *(uint64_t*)(world + 0x30);
    float worldTransformLow = (float)(uint32_t)worldTransform;
    float worldTransformHigh = (float)(worldTransform >> 32);
    // Build another double from those two floats with the same offset
    dLocalE8 = __builtin_avr_insert_bits(worldTransformHigh + _DAT_00d69a68, (double)worldTransformLow);

    // Perform the actual raycast / line‑of‑sight test
    // Parameters:    handle (this+0x10), world transform (world+0x30), query point, flags
    initStatus = physicsRayTest(*(int*)(this + 0x10), world + 0x30, &startPoint, 0);

    if (initStatus == 0) // success (no hit? or hit?)
    {
        // Set up a temporary result object
        initStatus = constructRaycastResult(&result, 0x40102, 0x300001, 0, 0);

        // Fill the result object with default values
        result.faceIndex = -1;
        result.extraIndex = -1;
        result.isValid    = 1;              // local_40 = 1
        result.vtable     = &PTR_FUN_00e32a8c;   // assign the right vtable
        result.status     = 0;              // local_70 = 0
        result.distance   = _DAT_00d5780c;
        result.hitNormal  = Vector3(0,0,0); // local_80 = 0
        result.hitPoint   = _DAT_00d5780c;  // local_cc = ...

        // Convert the internal result to the final output
        if (convertRaycastToOutput(&result, &outPos->x) == 0)   // local_70 == 0 indicates success
        {
            // Write the output position (actually it's stored as two doubles?)
            *outPos->x = startPoint.x;
            *outPos->y = startPoint.y;   // fStack_f0
            *outPos->z = startPoint.z;
            return 1;
        }
    }
    return 0;
}