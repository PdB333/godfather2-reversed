// FUNC_NAME: SimManager::SimManager
void __fastcall SimManager::SimManager(SimManager* thisPtr)
{
    // Set vtable pointer (first 4 bytes of object)
    thisPtr->vtable = &PTR_FUN_00d60bd8;                       // +0x00

    // Set sub-vtable pointers (possibly for base classes or interfaces)
    thisPtr->baseVtable1 = &PTR_LAB_00d60bc8;                  // +0x0f * 4 = +0x3C
    thisPtr->baseVtable2 = &PTR_LAB_00d60bc4;                  // +0x12 * 4 = +0x48

    // Initialize first sub-object (e.g., a list/array) at offset +0x50
    FUN_004086d0(&thisPtr->subObject1);                        // +0x14 * 4 = +0x50
    FUN_00408310(&thisPtr->subObject1);                        // clear/init after construction

    // Initialize second sub-object at offset +0x58
    FUN_004086d0(&thisPtr->subObject2);                        // +0x16 * 4 = +0x58
    FUN_00408310(&thisPtr->subObject2);

    // Also initialize a static global structure
    FUN_004086d0(&DAT_012069c4);

    // Cleanup check: reset pointer at +0x22 (offset +0x88) and its back-reference
    if (thisPtr->deferredPtr1 != nullptr)
    {
        *(int*)(thisPtr->deferredPtr1 + 8) = 0;                // clear back-link at offset +8
        thisPtr->deferredPtr1 = nullptr;
    }

    // Cleanup check: if pointer at +0x1E (offset +0x78) is non-null, release via function pointer at +0x21 (+0x84)
    if (thisPtr->ownedObject != nullptr)
    {
        void (*releaseFunc)(void*) = (void (*)(void*))thisPtr->releaseFunc; // +0x21*4 = +0x84
        releaseFunc(thisPtr->ownedObject);
    }

    // Final global initialization (e.g., register manager)
    FUN_0046c640();
}