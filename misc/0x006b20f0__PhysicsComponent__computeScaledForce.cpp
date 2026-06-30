// FUNC_NAME: PhysicsComponent::computeScaledForce
float __thiscall PhysicsComponent::computeScaledForce(int thisPtr, float forceTypeIndex)
{
    // Read base multiplier from lookup table: DAT_00e50d14 + (forceTypeIndex * 0x10)
    // The table appears to contain 16-byte entries with a float at the start.
    float baseMultiplier = *(float *)(&DAT_00e50d14 + (int)forceTypeIndex * 0x10);

    // Get current speed magnitude from the object at offset +0x40
    // FUN_008c7710 is likely getSpeed() or getVelocityMagnitude()
    float speed = (float)FUN_008c7710(*(undefined4 *)(thisPtr + 0x40));

    // +0x16c contains an integer state value
    int state = *(int *)(thisPtr + 0x16c);

    // Only apply speed multiplier if speed > 0 and state matches one of these movement states
    // States 2, 3, 4 likely correspond to running, sprinting, or airborne.
    if ((float)0.0f < speed && (state == 2 || state == 3 || state == 4)) {
        baseMultiplier *= speed;
    }

    return (float)baseMultiplier;
}