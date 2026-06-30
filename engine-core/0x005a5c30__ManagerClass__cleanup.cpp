// FUNC_NAME: ManagerClass::cleanup
void __thiscall ManagerClass::cleanup(void)
{
    // First loop: iterate over 64 object pointers at offset 0x1c10
    int* ppObj = (int*)(this + 0x1c10);
    for (int i = 0; i < 64; i++)
    {
        uint* pObj = (uint*)*ppObj;
        if (pObj != nullptr)
        {
            // Call virtual destructor/cleanup via vtable dispatch
            // The vtable pointer is at offset 0 of the object, masked with 0x7fff
            // to get an index into a global function table at DAT_0103aee0
            (**(code**)(&DAT_0103aee0 + (*pObj & 0x7fff) * 4))(pObj);
            *ppObj = 0; // Clear pointer
        }
        ppObj++;
    }

    // Second loop: iterate backward over 64 structures (size 0x2c) at offset 0x2508
    // The loop starts at the end of the array (offset 0x3028) and goes backward
    int* pStructEnd = (int*)(this + 0x3028); // One past the last element
    for (int j = 0; j < 64; j++)
    {
        pStructEnd -= 0x2c / sizeof(int); // Move to previous structure (0x2c bytes = 11 ints)
        int count = *(pStructEnd + 0); // First field: count (offset 0)
        if (count > 0)
        {
            do {
                FUN_005a6ff0(); // Cleanup function for each count
                count--;
            } while (count != 0);
        }
    }

    // Additional cleanup
    FUN_005b3890(); // Likely memory manager cleanup

    // Check a pointer at offset 0x2514 (first element of the structure array, field at +0x0C)
    int* pData = *(int**)(this + 0x2514);
    if (pData != nullptr)
    {
        FUN_005b1e40(); // Destructor or release
        (*DAT_0119caf8)(pData, 4); // Free memory (size 4)
    }

    FUN_005a71e0(); // Final cleanup step 1
    FUN_005a7170(); // Final cleanup step 2
}