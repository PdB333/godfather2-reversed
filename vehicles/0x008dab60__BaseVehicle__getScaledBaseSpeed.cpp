// FUNC_NAME: BaseVehicle::getScaledBaseSpeed
// Address: 0x008dab60
// Role: Computes the effective base speed by multiplying the stored base speed (offset +0x1c8) with a power modifier from an optional engine/component (pointer at offset +0x190, modifier at +0x1db8).
float BaseVehicle::getScaledBaseSpeed()
{
    // +0x1c8: base speed (float)
    float baseSpeed = *(float*)((uintptr_t)this + 0x1c8);
    
    // +0x190: pointer to an engine/power component (could be a Transmission or Engine object)
    int* component = *(int**)((uintptr_t)this + 0x190);
    if (component != nullptr)
    {
        // +0x1db8: power multiplier (float)
        float modifier = *(float*)((uintptr_t)component + 0x1db8);
        baseSpeed *= modifier;
    }
    
    return baseSpeed;
}