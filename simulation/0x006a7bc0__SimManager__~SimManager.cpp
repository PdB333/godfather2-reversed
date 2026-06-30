// FUNC_NAME: SimManager::~SimManager
void __fastcall SimManager::~SimManager(void* thisPtr)
{
    // This constructor is the standard destructor for SimManager.
    // Offset: +0x00 - vtable pointer for base class
    // Offset: +0x08 - secondary vtable pointer (for interface IUnknown?)
    // Offset: +0x0C - pointer to inner object (e.g., scene graph root)
    // Offset: +0x10 - pointer to allocated memory block
    // Offset: +0x24 - another resource pointer (e.g., collision manager)

    // Set vtable to the base class destructor stub (prevents double destruction)
    *(int*)thisPtr = (int)&PTR_LAB_00d5d868;

    // Set secondary vtable pointer
    *(int*)((char*)thisPtr + 8) = (int)&PTR_LAB_00d5d864;

    // Call virtual destructor of the inner object (offset +0x0C)
    // vtable at +0x0C, vtable entry +0x0C = destructor (likely)
    (*(void (__thiscall**)(void*))(*(int*)(*(int*)((char*)thisPtr + 12)) + 12))((void*)*(int*)((char*)thisPtr + 12));

    // Deinitialize subsystem (e.g., free static memory, close devices)
    SimManager::deinitialize(); // FUN_006a7840

    // Release resource at offset +0x24 (e.g., NavMesh manager)
    if (*(int*)((char*)thisPtr + 36) != 0) {
        // Decrement reference count and possibly free
        SimManager::releaseReference(*(void**)(*(int*)((char*)thisPtr + 36) + 8)); // FUN_009c8f10
    }

    // Free memory block at offset +0x10
    int memBlock = *(int*)((char*)thisPtr + 16);
    if (memBlock != 0) {
        // Release inner pointer of the block (offset +0x08) then free the block
        SimManager::releaseReference(*(void**)(memBlock + 8)); // FUN_009c8f10
        SimManager::freeMemoryBlock((void*)memBlock); // FUN_009c8eb0
    }

    // Finalize vtable (point to empty dtor stub)
    *(int*)((char*)thisPtr + 8) = (int)&PTR_LAB_00d5d85c;

    // Decrement global instance count
    gSimManagerInstanceCount = 0; // DAT_01129984

    // Call final cleanup (e.g., shutdown singletons)
    SimManager::finalCleanup(); // FUN_0049c640
}