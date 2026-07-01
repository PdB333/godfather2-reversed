// FUNC_NAME: Vehicle::setSpeed
// Address: 0x007ac7b0
// Role: Set vehicle speed with dirty flag for network sync

void __thiscall Vehicle::setSpeed(float speed)
{
    // Compare with current speed at offset +0x60
    if (speed != *(float *)(this + 0x60))
    {
        // Set dirty flag at offset +0x64 (100 decimal)
        *(byte *)(this + 0x64) = 1;
        // Update speed
        *(float *)(this + 0x60) = speed;
    }
}