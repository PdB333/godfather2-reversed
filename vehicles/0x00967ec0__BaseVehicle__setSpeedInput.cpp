// FUNC_NAME: BaseVehicle::setSpeedInput
void __thiscall BaseVehicle::setSpeedInput(int inputValue) {
    float floatInput = (float)inputValue;
    // Clear bit 19 (0x80000) of flags at +0x6f4 (likely 'accelInputActive' flag)
    *(uint*)((int)this + 0x6f4) &= 0xfff7ffff;
    
    // Round negative values towards zero (e.g., for brake/reverse input)
    if (inputValue < 0) {
        floatInput += *(float*)0x00e44578; // 0.5f or half-constant for rounding
    }
    
    // Apply scaled input using global vehicle configuration (DAT_01129908 + 0x14 = speedScalar)
    applyVehicleInput(floatInput + *(float*)(*(int*)0x01129908 + 0x14));
    
    // Clear bit 18 (0x40000) of flags (likely 'brakeInputActive' flag)
    *(uint*)((int)this + 0x6f4) &= 0xfffbffff;
    
    finalizeInputProcessing();
}