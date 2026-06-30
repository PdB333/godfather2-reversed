// FUNC_NAME: InputManager::normalizeDeadzoneStickInput
void __fastcall InputManager::normalizeDeadzoneStickInput(
    float *outHorizontal, float *outVertical, 
    void *controllerState, float sensitivityMultiplier)
{
    float magnitude;
    ushort flags;
    uint deadzoneMask;
    double deadzoneThreshold;
    float hStick;
    float vStick;
    float fVar7;
    
    deadzoneThreshold = DAT_00e44768; // Global deadzone threshold value
    deadzoneMask = DAT_00e44680;      // Deadzone mask for upper bits
    
    flags = *(ushort *)(controllerState + 0x2c); // Controller flags/buttons state +0x2c
    
    if ((flags & 0x200) == 0) {
        // No deadzone adjustment needed, direct copy
        *outVertical = *(float *)(controllerState + 0x40);   // Raw horizontal stick +0x40
        *outHorizontal = *(float *)(controllerState + 0x44); // Raw vertical stick +0x44
    }
    else {
        // Apply deadzone scaling
        hStick = *(float *)(controllerState + 8);      // Deadzone radius or threshold +0x08
        vStick = *(float *)(controllerState + 0x40) * DAT_00e3ac58;  // Scaled horizontal
        fVar7 = *(float *)(controllerState + 0x44) * _DAT_00e44770;  // Scaled vertical
        magnitude = (float)((uint)hStick & deadzoneMask);
        
        *outVertical = vStick;   // Actually horizontal output
        *outHorizontal = fVar7;  // Actually vertical output
        
        if (deadzoneThreshold < (double)magnitude) {
            // Normalize horizontal by deadzone radius
            *outVertical = vStick / hStick;
        }
        if (deadzoneThreshold < (double)(float)((uint)*(float *)(controllerState + 0xc) & deadzoneMask)) {
            // Normalize vertical by secondary threshold
            *outHorizontal = fVar7 / *(float *)(controllerState + 0xc);
        }
    }
    
    if ((flags & 0x4000) != 0) {
        // Apply sensitivity multiplier
        *outVertical = *outVertical * sensitivityMultiplier;
        *outHorizontal = *outHorizontal * sensitivityMultiplier;
        return;
    }
    
    // Apply global stick sensitivity (non-boosted)
    magnitude = *(float *)(controllerState + 0x48); // Global stick sensitivity +0x48
    fVar7 = *outHorizontal;
    *outVertical = *outVertical * magnitude;
    *outHorizontal = magnitude * fVar7;
    return;
}