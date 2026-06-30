// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject(EARSObject *this)
{
    // Set vtable pointers to the destructor vtables
    this->vfptr = (void**)&PTR_FUN_00d5ea20;       // +0x00: main vtable
    this->vfptr2 = (void**)&PTR_LAB_00d5ea10;      // +0x3C: second vtable (offset 0xF * 4)
    this->vfptr3 = (void**)&PTR_LAB_00d5ea0c;      // +0x48: third vtable (offset 0x12 * 4)

    // --- Remove this object from the global registry ---
    uint32 idx = 0;
    uint32 foundIdx = 0xFFFFFFFF;
    if (gObjectCount != 0) {
        do {
            foundIdx = idx;
            if (gObjectArray[idx] == this) break;
            idx++;
            foundIdx = 0xFFFFFFFF;
        } while (idx < gObjectCount);
    }
    if (foundIdx != gObjectCount - 1) {
        // Swap with the last element
        gObjectArray[foundIdx] = gObjectArray[gObjectCount - 1];
    }
    gObjectCount--;
    if (gObjectCount == 0) {
        // Free the dynamic array and reset
        operatorDeleteArray(gObjectArray); // FUN_009c8f10
        gObjectArray = nullptr;
        gObjectCapacity = 0;               // DAT_0112a6a8
    }

    // Destroy global singleton objects
    destroyStaticObject(gSoundManager);   // DAT_01206778 -> FUN_004086d0
    destroyStaticObject(gResourceManager); // DAT_0120e93c -> FUN_004086d0

    // Cleanup additional subsystems
    cleanupSubsystem(); // FUN_006bcc90

    // Free any dynamically allocated buffers owned by this object
    if (this->bufferA) { // +0x1A (offset 0x68)
        operatorDeleteArray(this->bufferA); // FUN_009c8f10
        // Note: original doesn't null, but cleanup optional
    }
    if (this->bufferB) { // +0x17 (offset 0x5C)
        operatorDeleteArray(this->bufferB); // FUN_009c8f10
    }

    // Final global cleanup
    finalCleanup(); // FUN_0046c640
}