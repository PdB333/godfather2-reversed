// FUNC_NAME: Vehicle::getCurrentSpeed
float __fastcall Vehicle::getCurrentSpeed(int this)
{
    // +0x2c88: pointer to vehicle physics/engine component
    // +0x60: current speed value (float) in the physics component
    return *(float *)(*(int *)(this + 0x2c88) + 0x60);
}