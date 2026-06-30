// FUNC_NAME: AnimBlendController::computeBlendWeight
void __thiscall AnimBlendController::computeBlendWeight(void* thisPtr)
{
    uint maxInput = *(uint *)((int)thisPtr + 0xe8);   // +0xe8: first blend input
    uint clipMax   = *(uint *)((int)thisPtr + 0xd4);   // +0xd4: maximum clamp value
    if (maxInput < clipMax) {
        maxInput = clipMax;
    }
    *(uint *)((int)thisPtr + 0xfc) = maxInput;        // +0xfc: stored max (used elsewhere)

    uint minInput = *(uint *)((int)thisPtr + 0xf0);   // +0xf0: second blend input
    uint clipMin   = *(uint *)((int)thisPtr + 0xdc);   // +0xdc: minimum clamp value
    if (clipMin <= minInput) {
        minInput = clipMin;
    }
    // Compute blend product with fixed‑point scaling
    int product = maxInput * minInput;
    float fProduct = (float)product;
    if (product < 0) {
        fProduct += 2147483648.0f;   // DAT_00e44578 (0x4f000000) – convert negative int to float without sign corrupt
    }
    uint blendResult = (uint)(long long)(fProduct * 0.001f);   // DAT_00e2e210 – scaling factor (approx 0.001?)
    *(uint *)((int)thisPtr + 0xf8) = blendResult;             // +0xf8: final blend weight
    if (blendResult > 0x400) {
        *(uint *)((int)thisPtr + 0xf8) = 0x400;               // clamp to 1024
    }
}