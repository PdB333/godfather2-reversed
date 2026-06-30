// FUNC_NAME: VehicleBrain::computeWheelForce
void __thiscall VehicleBrain::computeWheelForce(void)
{
    float *forcePtr;
    uint wheelIndex;
    int state;
    float globalScale;
    WheelData *wheelData;
    
    // Global constant (likely gravity or unit conversion factor)
    globalScale = DAT_00e2b1a4;
    
    // +0x100: wheel slot index (0..0xFFF)
    wheelIndex = *(uint *)(this + 0x100);
    if (wheelIndex < 0x1000) {
        // Wheel data table (0x38 bytes per entry) at base 0x011a0f28
        wheelData = (WheelData *)((byte *)&DAT_011a0f28 + wheelIndex * 0x38);
    } else {
        wheelData = NULL; // Invalid index, but subsequent dereference will crash
    }
    
    // +0x124: computed force X component (lateral?)
    forcePtr = (float *)(this + 0x124);
    *forcePtr = globalScale / (float)*(ushort *)&wheelData->suspensionDamping; // +0x02
    
    // +0x128: computed force Y component (longitudinal?)
    *(float *)(this + 0x128) = globalScale / (float)*(ushort *)&wheelData->traction; // +0x04
    
    // +0x138: wheel state (4=rolling,5=skidding,0xE=something)
    state = *(int *)(this + 0x138);
    if ((state == 4) || (state == 5) || (state == 0xe)) {
        // +0x13c: flag indicating which component to zero (1 -> second, 0 -> first)
        *(undefined4 *)(this + 0x124 + (uint)(*(int *)(this + 0x13c) == 1) * 4) = 0;
    }
    
    // +0x11c: handle for first force receiver (e.g., chassis?)
    if (*(int *)(this + 0x11c) != 0) {
        FUN_0060ac80(*(unsigned int *)(this + 0x14), *(int *)(this + 0x11c), forcePtr);
    }
    // +0x120: handle for second force receiver (e.g., wheel itself?)
    if (*(int *)(this + 0x120) != 0) {
        FUN_0060ac80(*(unsigned int *)(this + 0x10), *(int *)(this + 0x120), forcePtr);
    }
    return;
}