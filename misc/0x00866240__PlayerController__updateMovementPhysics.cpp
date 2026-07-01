// FUNC_NAME: PlayerController::updateMovementPhysics
void __fastcall PlayerController::updateMovementPhysics(uint this)
{
    float magnitude;
    float speedScalar;
    float turnFactor;
    float10 lengthResult;
    double cosResult, sinResult;
    float headingAngle;
    float newX, newZ;
    // Vector components from object offsets
    float posX, posY, posZ; // at +0x1050, +0x1054, +0x1058
    float velocityX, velocityZ; // intermediate locals

    // Clear some flag at +0xf60
    *(uint *)(this + 0xf60) = 0;

    // Apply some damping or blending (mask low byte of pointer? Possibly a parent handle)
    FUN_00549ac0(this & 0xffffff00);

    // Read current position/offset vector
    posX = *(float *)(this + 0x1050);
    posY = *(float *)(this + 0x1054);
    posZ = *(float *)(this + 0x1058);

    // Compute magnitude of that vector
    lengthResult = FUN_00875220(this, &posX);

    // If magnitude exceeds threshold (global at 0x00d5f00c)
    if ((float10)DAT_00d5f00c < ABS(lengthResult))
    {
        // Start turning animation or rotation
        FUN_005ff860();
        FUN_008659a0();

        // Read speed and turn factor
        newX = *(float *)(this + 0x1050); // re-read? Actually local_18 = this+0x1050
        speedScalar = *(float *)(this + 0x1148); // m_speed
        // Y component (unused directly)
        // z component will be used
        newZ = *(float *)(this + 0x1058);
        turnFactor = *(float *)(this + 0xfc4); // m_turnFactor

        // If turnFactor is not a special sentinel value
        if (turnFactor != _DAT_00d577a0)
        {
            // Compute rotation adjustments using sin/cos
            cosResult = (double)speedScalar;
            FUN_00b99e20(); // likely cos(angle)
            newX = newX - (float)cosResult * turnFactor;

            sinResult = (double)speedScalar;
            FUN_00b99fcb(); // likely sin(angle)
            newZ = (float)sinResult * turnFactor + newZ;
        }

        // Compute new heading angle from (newX, newZ)
        lengthResult = FUN_00470250(&newX); // atan2? Returns angle
        headingAngle = (float)(lengthResult + lengthResult); // double it
        *(float *)(this + 0x1100) = headingAngle; // store heading

        // Apply steering input (global handle)
        FUN_00600210(_DAT_00d5c458, 0, 0, 0);
    }

    // Clear bit 0x10000 (ground contact flag?)
    *(uint *)(this + 0xf28) = *(uint *)(this + 0xf28) & 0xfffeffff;
}