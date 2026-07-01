// FUNC_NAME: VehicleBrain::getSpeed
float VehicleBrain::getSpeed() const
{
    // Pointer to internal physics state at this+0x04.
    // Speed float is at offset 0x44 within that state.
    return *(float*)(*(int*)(this + 4) + 0x44);
}