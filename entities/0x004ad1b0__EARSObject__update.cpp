// FUNC_NAME: EARSObject::update
void EARSObject::update(void)
{
    // Forward to the real update implementation at 0x004ae6f0
    // This is likely a virtual thunk or a base-class stub called during the main game loop.
    // Callers from 0x007b5720 (main update loop) invoke this thousands of times per frame.
    realUpdate();  // FUN_004ae6f0: actual per-object update logic
    return;
}