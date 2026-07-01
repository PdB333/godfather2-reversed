// FUNC_NAME: AudioDataManager::releaseBankSlots
// Function address: 0x008764f0
// Releases and frees an array of 8 bank slot objects stored at offset 0xDC4 from 'this'.
// Each slot is 8 bytes (two ints: pointer + padding/next). Calls release helper, vtable destructor, then free.
void __fastcall AudioDataManager::releaseBankSlots(int this)
{
    int *slotPtr;          // current slot pointer
    int remaining;         // loop counter

    slotPtr = (int *)(this + 0xDC4); // +0xDC4: bank slot array base (8 entries, 8 bytes each)
    remaining = 8;
    do {
        if (*slotPtr != 0) {
            // Release the object (reference counting or cleanup)
            FUN_006e72d0(*slotPtr);
            // Call vtable[0] destructor with argument 1
            if (*(void **)*slotPtr != (void *)0x0) {
                (*(code *)**(void ***)*slotPtr)(1);
            }
            // Free the memory block
            if (*slotPtr != 0) {
                FUN_004daf90(slotPtr);
                *slotPtr = 0;
            }
        }
        slotPtr += 2; // next slot (2 x sizeof(int) = 8 byte stride)
        remaining--;
    } while (remaining != 0);
}