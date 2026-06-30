// FUNC_NAME: GameSystemManager::~GameSystemManager
void __fastcall GameSystemManager::~GameSystemManager(GameSystemManager* thisPtr)
{
    // Save original vtable pointer and set to intermediate destructor vtable
    thisPtr->vtablePtr = (void*)&PTR_FUN_00e31184;
    thisPtr->field_0C = &PTR_LAB_00e31194;

    // Destroy critical sections (global synchronization objects)
    destroyCriticalSection((CRITICAL_SECTION*)&g_criticalSection1); // +0x012069e4
    destroyCriticalSection((CRITICAL_SECTION*)&g_criticalSection2); // +0x012069dc

    // Free the linked list stored in field_10 (list of pointers)
    int* listPtr = (int*)thisPtr->field_10;
    if (listPtr != nullptr) {
        if (*listPtr != 0) {
            freePointer(*listPtr); // free each element's data
        }
        freeListContainer(listPtr); // free the list node itself
    }

    // Destroy remaining critical sections
    destroyCriticalSection((CRITICAL_SECTION*)&g_criticalSection3); // +0x012069ec
    destroyCriticalSection((CRITICAL_SECTION*)&g_criticalSection4); // +0x012069d4

    // Restore vtable pointer to final destructor state
    thisPtr->field_0C = &PTR_LAB_00e31198;

    // Clear global flag and perform final cleanup
    g_someGlobalFlag = 0;
    finalizeCleanup();
}