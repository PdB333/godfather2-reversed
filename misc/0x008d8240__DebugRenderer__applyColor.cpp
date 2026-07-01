// FUNC_NAME: DebugRenderer::applyColor
void __thiscall DebugRenderer::applyColor(void* thisPtr, unsigned int* colorPtr)
{
    // offset +0x184: pointer to some debug state struct (usually +0x8 is a flag?)
    void* statePtr = *(void**)((char*)thisPtr + 0x184);
    if (statePtr != nullptr)
    {
        void* flagPtr = *(void**)((char*)statePtr + 0x8);
        if (flagPtr != nullptr)
        {
            unsigned int color[4]; // +0x0: R/X, +0x4: G/Y, +0x8: B/Z, +0xC: A/W
            color[0] = colorPtr[0];
            color[1] = colorPtr[1];
            color[2] = colorPtr[2];
            color[3] = 0; // force alpha to 0
            FUN_009f1820(color, 0); // actual setter function, likely "setColor" or "apply"
        }
    }
}