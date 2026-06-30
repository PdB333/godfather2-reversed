// FUNC_NAME: AICarBehavior::updateTargetAngle
// Function at 0x006d72a0: Updates the target angle for steering, comparing desired angle with current angle to determine turn direction.
// Called from FUN_006bfbd0 and FUN_006d8950 (likely update loop or state machine).

void __thiscall AICarBehavior::updateTargetAngle(int thisPtr, int someInput)
{
    float fVar1; // 2*PI constant
    float fVar2; // scaling factor
    float10 desiredAngleRaw; // result from helper function
    float fVar4;

    // Only process if both flags are zero (idle state)
    if ((*(int *)(thisPtr + 0x224) == 0) && (*(int *)(thisPtr + 0x228) == 0))
    {
        // Get desired angle from helper (likely normalizes or computes something)
        desiredAngleRaw = (float10)FUN_006d7210(someInput);
        *(float *)(thisPtr + 0x24c) = (float)desiredAngleRaw; // m_targetAngle

        // Load constants: DAT_00e445c8 and DAT_00d5f4b4
        fVar2 = DAT_00e445c8; // likely 1/(2*PI) or something related to angle scaling
        fVar1 = DAT_00d5f4b4; // likely 2*PI
        fVar4 = (float)desiredAngleRaw;

        // Wrap target angle to [0, 2π) if negative
        if (desiredAngleRaw < (float10)0)
        {
            fVar4 = (float)desiredAngleRaw + fVar1;
        }
        *(float *)(thisPtr + 0x24c) = fVar4 * fVar2;

        // Get current angle from object (at offset 0x234)
        fVar4 = *(float *)(thisPtr + 0x234); // m_currentAngle
        if (fVar4 < 0.0)
        {
            fVar4 = fVar4 + fVar1;
        }

        // Compare desired and current (after scaling by fVar2, which is positive constant)
        if ((float)desiredAngleRaw * fVar2 < fVar4 * fVar2)
        {
            // Desired angle is smaller – set turning state to 2 (maybe turn right?)
            *(int *)(thisPtr + 0x224) = 2; // m_turnDirection
            *(int *)(thisPtr + 0x228) = 1; // m_turnActive
            return;
        }
        // Desired angle is larger or equal – set state to 1 (turn left?)
        *(int *)(thisPtr + 0x224) = 1;
        *(int *)(thisPtr + 0x228) = 1;
    }
}