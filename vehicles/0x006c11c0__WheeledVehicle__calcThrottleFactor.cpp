// FUNC_NAME: WheeledVehicle::calcThrottleFactor
float __thiscall WheeledVehicle::calcThrottleFactor(void)
{
    // this +0x298: pointer to engine data / curve ID
    // this +0x10c: current RPM/velocity
    // this +0x108: max RPM/velocity
    // this +0x80: throttle response factor / acceleration curve strength
    float ratio = *(float *)(this + 0x10c) / *(float *)(this + 0x108);
    float curveValue = curveLookup(*(int *)(this + 0x298), 0, 1.0f, 1.0f, ratio);
    return (curveValue - 1.0f) * *(float *)(this + 0x80) + 1.0f;
}