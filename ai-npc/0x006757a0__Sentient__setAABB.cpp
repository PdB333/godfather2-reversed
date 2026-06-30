// FUNC_NAME: Sentient::setAABB
void __fastcall Sentient::setAABB(float *boxData)
{
    // +0x7c: min.x (float)
    // +0x80: min.y
    // +0x84: min.z
    // +0x88: max.x
    // +0x8c: max.y
    // +0x90: max.z
    if (boxData != 0)
    {
        *(float *)(this + 0x7c) = boxData[0]; // min.x
        *(float *)(this + 0x80) = boxData[1]; // min.y
        *(float *)(this + 0x84) = boxData[2]; // min.z
        *(float *)(this + 0x88) = boxData[3]; // max.x
        *(float *)(this + 0x8c) = boxData[4]; // max.y
        *(float *)(this + 0x90) = boxData[5]; // max.z
    }
    else
    {
        // Null pointer clears only the first two fields (min.x, min.y)
        *(float *)(this + 0x7c) = 0.0f;
        *(float *)(this + 0x80) = 0.0f;
        // Note: remaining 4 fields are left unchanged – this may be intentional
        // (e.g., min.z and max are not zeroed, possibly indicating an invalid state)
    }
}