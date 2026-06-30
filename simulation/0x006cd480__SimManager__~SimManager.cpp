// FUNC_NAME: SimManager::~SimManager
void __fastcall SimManager::~SimManager(SimManager* this) // param_1 is this
{
    int* pChildList; // piVar1, points to child list pointer at offset 0xC0
    int* pChild;     // piVar2, temporary for iterating children

    // Set vtable pointers for this object (base and derived)
    *(void***)this = &PTR_FUN_00d5f174;      // +0x00: vtable pointer (base)
    *(void***)((char*)this + 8) = &PTR_LAB_00d5f16c; // +0x08: second vtable (if multiple inheritance)

    // Access child list pointer at offset 0xC0
    pChildList = (int*)((char*)this + 0xC0); // +0xC0: pointer to array/container

    // If the list pointer is not null and not a special sentinel value (0x48)
    if ((*pChildList != 0) && (*pChildList != 0x48))
    {
        // Each element in the list has size 0x48 (72 bytes)
        // Compute the base of the first element (list pointer minus 0x48)
        if (*pChildList == 0)
        {
            pChild = (int*)0x0;
        }
        else
        {
            pChild = (int*)(*pChildList - 0x48);
        }
        // Call the destructor for each element (vtable method at offset 0x70)
        (**(code**)(*pChild + 0x70))(); // call virtual destructor or cleanup
    }

    // Global reference count check (DAT_0112a804)
    if ((DAT_0112a804 != 0) && (DAT_0112a804-- == 1))
    {
        // When reference count drops to zero, perform global cleanup
        // local_c is a buffer for some cleanup data
        undefined4 local_c = DAT_0112a80c; // copy global data
        undefined4 local_8 = 0;
        undefined1 local_4 = 0;
        FUN_00408a00(&local_c, 0); // some cleanup with buffer
        FUN_006cc3b0();           // additional global cleanup
    }

    // Delete other dynamically allocated member at offset 0xC8
    if (*(int*)((char*)this + 0xC8) != 0) // +0xC8: another pointer
    {
        FUN_004daf90((int*)((char*)this + 0xC8)); // free memory
    }

    // Delete the child list itself if it exists
    if (*pChildList != 0)
    {
        FUN_004daf90(pChildList); // free the list container
    }

    // Final cleanup (possibly global resource manager)
    FUN_006c9820(); // deinitialize or release global object
}