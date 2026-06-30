// FUNC_NAME: SimManager::shutdown
void __fastcall SimManager::shutdown(SimManager* thisPtr)
{
    // Set vtable to first destructor stage (offset +0x0)
    thisPtr->vfptr = (void*)&PTR_FUN_00d5c684; // Vtable table for destruction phase 1
    // +0x0C: Pointer to a type info or base destructor data
    thisPtr->destructorData = (void*)&PTR_LAB_00d5c680;

    // Unregister or notify some global manager (likely a singleton registry)
    SimManager::unregister(&DAT_012069c4); // call to FUN_004086d0

    // If a child component exists, call its destructor via vtable offset +0x0C
    // +0x10: Pointer to child component (e.g., a sub-manager)
    if (thisPtr->childComponent != nullptr) {
        // Child vtable at +0x0C is a destructor function
        void (*childDestructor)(void) = *(void (**)())(*(int*)thisPtr->childComponent + 0xC);
        childDestructor();
    }

    // Update destructor stage data pointer
    thisPtr->destructorData = (void*)&PTR_LAB_00d5c67c; // phase 2

    // Clear the global singleton pointer (DAT_011298e0)
    g_SimManagerSingleton = nullptr; // DAT_011298e0 = 0

    // Final cleanup (e.g., deallocate memory or notify framework)
    SimManager::finalCleanup(); // call to FUN_004083d0
}