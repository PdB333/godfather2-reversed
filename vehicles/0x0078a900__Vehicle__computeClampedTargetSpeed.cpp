// FUNC_NAME: Vehicle::computeClampedTargetSpeed
void __thiscall Vehicle::computeClampedTargetSpeed(float* this, bool isBraking)
{
    // Globals inferred from game constants
    extern float DAT_00d5c458;  // Blend factor for speed averaging (e.g., 0.5f)
    extern float DAT_00d5e288;  // Maximum allowable speed limit
    extern float DAT_00d5ef84;  // Interpolation factor for final blend
    extern float DAT_00d699f0;  // Default lower bound when not braking
    extern int* DAT_012233a0;   // Pointer to some game state (e.g., g_pGameState)
    
    float lowerBound;
    float currentSpeed = *(float*)(this + 0x54);  // Current vehicle speed
    float targetSpeed  = *(float*)(this + 0x58);  // Desired/commanded speed
    
    // Check if game is in a specific state (not paused and not a special menu state)
    int* gameStatePtr = *(int**)(DAT_012233a0 + 4);
    if (gameStatePtr != 0 && *gameStatePtr != 0x1f30)
    {
        // Choose appropriate lower bound based on braking flag
        lowerBound = DAT_00d699f0;  // Default lower limit
        if (isBraking)
        {
            lowerBound = DAT_00d5e288;  // When braking, use max speed as lower bound? (or maybe reverse limit)
        }
        
        // Compute a blended "low" speed from current and target
        float blended = (currentSpeed + targetSpeed) * DAT_00d5c458;  // Weighted average
        float lowSpeed = blended * 2.0f - targetSpeed;  // 2*blended - target -> this expands the range
        if (lowSpeed < 0.0f)
        {
            lowSpeed = 0.0f;
        }
        
        // Clamp target speed to maximum limit
        float clampedTarget = targetSpeed;
        if (targetSpeed > DAT_00d5e288)
        {
            clampedTarget = DAT_00d5e288;
        }
        
        // Blend between low and capped target
        float finalSpeed = (clampedTarget - lowSpeed) * DAT_00d5ef84 + lowSpeed;
        
        // Apply lower bound
        if (finalSpeed < lowerBound)
        {
            lowerBound = finalSpeed;
        }
    }
    
    // Store result into member variable based on braking state
    if (isBraking)
    {
        *(float*)(this + 0x40) = lowerBound;  // Brake input / brake torque
        return;
    }
    
    // For non-braking: clamp result between 0 and max speed and store to throttle input
    if (lowerBound > DAT_00d5e288)
    {
        *(float*)(this + 0x4c) = DAT_00d5e288;
    }
    else if (lowerBound >= 0.0f)
    {
        *(float*)(this + 0x4c) = lowerBound;
    }
    else
    {
        *(float*)(this + 0x4c) = 0.0f;
    }
}