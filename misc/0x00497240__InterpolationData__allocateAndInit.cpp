// FUNC_NAME: InterpolationData::allocateAndInit
void InterpolationData::allocateAndInit(InterpolationInitParams& params)
{
    int allocBuf[6]; // actually used as a pointer holder
    FUN_00498740(allocBuf, &params); // allocates a new InterpolationData block, returns pointer in allocBuf[0]

    InterpolationData* data = reinterpret_cast<InterpolationData*>(allocBuf[0]);

    // Store the two 64-bit values at both current and previous slots (duplicated for interpolation)
    // Offsets: +0x08 = currentValueA, +0x18 = prevValueA (same)
    //          +0x10 = currentValueB, +0x20 = prevValueB (same)
    // +0x28 = flags (32-bit)
    uint64 valA = ((uint64)params.high1 << 32) | params.low1;
    uint64 valB = ((uint64)params.high2 << 32) | params.low2;

    data->currentA = valA;
    data->prevA = valA;
    data->currentB = valB;
    data->prevB = valB;
    data->flags = static_cast<int32>(params.flag);
}