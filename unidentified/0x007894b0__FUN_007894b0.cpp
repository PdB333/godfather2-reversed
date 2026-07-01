// FUNC_NAME: SomeClass::activateDoubleUpdate
void __fastcall SomeClass::activateDoubleUpdate(SomeClass* this)
{
    // Set bit 0 of flags at offset +0x50
    *(uint32_t*)((uint8_t*)this + 0x50) |= 1;

    // Call update function twice (likely double-buffering or dual processing)
    int loopCount = 2;
    do {
        someUpdateFunction(); // FUN_004df710 - internal update routine
        loopCount--;
    } while (loopCount != 0);
}