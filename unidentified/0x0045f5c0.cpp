// FUN_0045f5c0: Weapon::calculateTrajectory
void __thiscall Weapon::calculateTrajectory(float* outTrajectory)
{
    // Check flag at offset +0x61 (bit 7: 0x80)
    // Likely indicates whether predictive trajectory is enabled
    if (!(*(uint8*)(this + 0x61) & 0x80))
    {
        // Simple trajectory: just get base velocity and apply weapon modifier if present
        getBaseVelocity(outTrajectory); // FUN_00471cc0
        void* weaponData = *(void**)(this + 0x218); // offset 0x86
        if (weaponData)
        {
            outTrajectory[3] *= *(float*)((uint8*)weaponData + 0x104);
        }
        return;
    }

    // Predictive trajectory: calculate multiple segments
    float baseVelocity[4];
    getBaseVelocity(baseVelocity); // initial base velocity

    outTrajectory[0] = baseVelocity[0];
    outTrajectory[1] = baseVelocity[1];
    outTrajectory[2] = baseVelocity[2];
    outTrajectory[3] = baseVelocity[3];

    // Get target position via virtual call on object pointed by this+0x54 (offset 0x15)
    // The object's vtable at offset 4 returns a pointer to a struct with position at +0x30
    // The call is: (**(code**)(this->mTarget + 4))()
    void* baseTarget = *(void**)(this + 0x54); // offset 0x15
    int* (__thiscall* getTargetPos)(void*) = *(int* (__thiscall**)(void*))((uint8*)baseTarget + 4);
    int* targetPos = getTargetPos(baseTarget); // returns pointer to position data

    int numSegments = *(int*)(this + 0x264); // offset 0x99
    for (int i = 1; i < numSegments; i++)
    {
        int segmentIdx = i * 4;
        float segmentDelta[4];
        // Virtual function at *this vtable + 0xa4 (index 41) - retrieves segment point by index
        void (__thiscall* getSegment)(void*, float*, int*) = *(void (__thiscall**)(void*, float*, int*))(*(int*)this + 0xa4);
        getSegment(this, segmentDelta, &segmentIdx);

        // Compute offset from target position (at targetPos + 0x30, 0x34, 0x38)
        float dx = segmentDelta[0] - *(float*)((uint8*)targetPos + 0x30);
        float dy = segmentDelta[1] - *(float*)((uint8*)targetPos + 0x34);
        float dz = segmentDelta[2] - *(float*)((uint8*)targetPos + 0x38);

        float adjusted[4]; // temp (w constant from global DAT_00e2b1a4)
        adjusted[0] = baseVelocity[0] + dx;
        adjusted[1] = baseVelocity[1] + dy;
        adjusted[2] = baseVelocity[2] + dz;
        adjusted[3] = baseVelocity[3] + *(float*)0x00e2b1a4; // constant (likely gravity or wind)

        // Apply some transformation (vector normalization or clamping)
        applySegmentAdjustment(adjusted); // FUN_004bd160

        // The result is not accumulated; only the initial base velocity is output.
        // The loop likely is for side effects or internal state updates.
    }

    // Final adjustment: apply weapon multiplier and then final transformation
    void* weaponData = *(void**)(this + 0x218); // offset 0x86
    if (weaponData)
    {
        outTrajectory[3] *= *(float*)((uint8*)weaponData + 0x104);
    }
    applyFinalTrajectory(outTrajectory); // FUN_00471d20
}