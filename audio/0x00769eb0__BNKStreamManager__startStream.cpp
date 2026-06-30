// FUNC_NAME: BNKStreamManager::startStream
void __thiscall BNKStreamManager::startStream(BNKStreamManager* this)
{
    // Offset +0x7c: bitfield flags (lower 4 bits = state)
    this->flags7C = this->flags7C & 0xfffffff0;   // Clear lower 4 bits (state field)

    bool isStreamActive = someCheck();   // FUN_00769860 - likely checks if already playing
    if (!isStreamActive)
    {
        // Parameters: (1, 1, 0, 1.0f, 1.0f) - possibly priority, volume, etc.
        void* stream = createStreamInstance(1, 1, 0, 1.0f, 1.0f);   // FUN_00769400
        // Virtual table call at offset +0x2c (likely a "play" or "start" method)
        (this->vtable->play)(stream);   // vtable[0x2c/4] = 0x0b entry
    }
}