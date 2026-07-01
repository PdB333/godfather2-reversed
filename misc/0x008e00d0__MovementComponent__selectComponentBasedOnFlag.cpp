// FUNC_NAME: MovementComponent::selectComponentBasedOnFlag
void __fastcall MovementComponent::selectComponentBasedOnFlag(int thisPtr)
{
    // Read a single component (e.g., speed or magnitude) from offset +0x218
    float component = *(float*)(thisPtr + 0x218);
    // Flag at +0x23c determines which axis this component belongs to
    bool flag = *(char*)(thisPtr + 0x23c) != 0;

    float zero = 0.0f;
    float first, second;

    if (flag) {
        // Flag set: component goes into first slot, second is zero
        first = component;
        second = zero;
    } else {
        // Flag clear: first is zero, component goes into second slot
        first = zero;
        second = component;
    }

    // Call engine function with the two components and a scale of 1.0f (0x3f800000)
    // Likely sets a 2D vector or applies direction to some system
    FUN_0094db30(first, second, 1.0f);
}