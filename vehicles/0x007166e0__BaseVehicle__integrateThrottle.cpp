// FUNC_NAME: BaseVehicle::integrateThrottle

// Global step value (likely acceleration * delta time or constant increment per frame)
extern float gAccelStep; // _DAT_00e51720

void __fastcall BaseVehicle::integrateThrottle(void *this)
{
    // Member at offset +0x1b0: current throttle integration value (e.g., speed or accumulator)
    float *throttleComponent = (float *)((char *)this + 0x1b0);
    *throttleComponent = *throttleComponent + gAccelStep;
}