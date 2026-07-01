// FUNC_NAME: VehicleEngine::getMaxSpeed
float __fastcall VehicleEngine::getMaxSpeed(int this)
{
    float result;
    
    // Call virtual function at vtable+0x30 on the object at this+0x210
    // This is likely a method on a transmission or gearbox component
    result = (*(float (__fastcall **)(int))(**(int **)(this + 0x210) + 0x30))(this);
    
    // Multiply by global speed multiplier (DAT_00d5e288)
    result = result * DAT_00d5e288;
    
    // Clamp to minimum of 0.0
    if (result < 0.0f) {
        result = 0.0f;
    }
    
    return result;
}