// FUNC_NAME: AudioManager::~AudioManager

void __thiscall AudioManager::~AudioManager()
{
    int iResult;
    int *pInt;
    AudioManager *pThis;

    // Set vtable pointer (first virtual table) and another vtable pointer at offset +0x0C
    this->vtable = &PTR_FUN_00e30ec4;
    this->field_0C = &PTR_LAB_00e30ed4;

    // Release global audio resources
    releaseGlobalResource(&DAT_01206940);
    releaseGlobalResource(&DAT_012069dc);

    // Get pointer to global audio manager structure
    pThis = DAT_01223404;                         // +0x00: pointer to self?
    pInt = DAT_01223404 + 1;                      // +0x04: some pointer field

    if (DAT_01223404[4] != 0) {                   // +0x10: check if active
        FUN_004c9390();                            // Unload or stop sound?
        iResult = *pInt;                           // +0x04: pointer value
        if (iResult != 0) {
            FUN_004c9a70();                        // Free or release
            FUN_009c8eb0(iResult);                 // Free memory at iResult
        }
        pThis = DAT_01223404;                      // refresh after possible changes
        *pInt = 0;
    }

    // Virtual call at offset 0x0C (third method) on object at +0x14 (slot 5)
    pInt = (int *)pThis[5];                        // +0x14: pointer to another object
    if (pInt != (int *)0x0) {
        (**(code **)(*pInt + 0xc))();              // call virtual method
        pThis = DAT_01223404;
        pThis[5] = 0;
    }

    // Delete the main structure via virtual destructor (first vtable method with argument 1)
    if (pThis != (AudioManager *)0x0) {
        (**(code **)*pThis)(1);                    // operator delete(this, 1)
    }

    // Clean up another global structure
    destroyStructure(DAT_01223518);                // +0x14? another manager
    if (DAT_01223518 != (AudioManager *)0x0) {
        (**(code **)*DAT_01223518)(1);             // delete it
    }

    // Virtual call on an object pointed to by this->field_14 (offset +0x14)
    if ((int *)this[5] != (int *)0x0) {
        (**(code **)(*(int *)this[5] + 0xc))();
    }

    // Update vtable pointer at offset +0x0C to a different one (base class?)
    this->field_0C = &PTR_LAB_00e30ed8;

    // Clear global singleton pointer and perform final shutdown
    DAT_01223400 = 0;                             // singleton nulled
    finalizeShutdown();                            // e.g., release remaining resources
}