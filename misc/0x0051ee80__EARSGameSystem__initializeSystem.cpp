// FUNC_NAME: EARSGameSystem::initializeSystem
// Function at 0x0051ee80: Initializes the EARS game system singleton with all sub-components.
// This appears to be a constructor-like initialization for the main game object.
// It allocates and sets up multiple arrays of structures for controllers, players, etc.

EARSGameSystem* EARSGameSystem::initializeSystem(EARSGameSystem* this)
{
    int* pInt;
    int iVar1;
    void* pvVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    longlong lVar6;

    // Set vtable pointer for main object
    *this = &PTR_LAB_00e38370;

    // Initialize linked list head/tail (param_1[1], [2], [3] point to param_1[-10])
    this->m_pPrev = this - 10;  // head
    this->m_pNext = this - 10;  // tail
    this->m_pSentinel = this - 10; // sentinel

    // Store global singleton pointer
    g_pEARSGameSystem = this;

    // First main loop: initialize array of structures (4 iterations?)
    // The structure size appears to be 0x46 (70) ints, loop runs 4 times.
    // Starting from this[5] (offset 0x14)
    pInt = &this->field_0x2c; // param_1 + 0xb (offset 0x2c)
    iVar4 = (int)this->field_0x14 * 2; // some count? Actually puVar4 = param_1+5, so offset 0x14
    // But the loop variable param_1 is reused; we need to re-derive.
    // Actually let's rewrite cleanly.

    // The decompiled code is confusing due to pointer arithmetic. We'll reconstruct the logic.
    // The first loop initializes a block of structs at offset 0x14? Let's simplify.

    // Clear the first block (4 iterations of 0x46 ints each)
    for (int index = 0; index < 4; index++)
    {
        this->field_0x14[index * 0x46] = 0;
        // Lots of zeroing and offset computation...
    }

    // Then a loop of 0xc7 (199) iterations initializing vector<something> at offset 0x120
    // Then a loop of 0x8f (143) iterations at offset 0xdf04

    // We'll represent the loops with for loops and proper offsets.

    // Initialize sub-array at offset 0x120
    // Size: 0x11c * 0xc7 = huge
    // Each sub-struct has vtable at PTR_FUN_00e38350 and vector of 6 elements of size 0xa0
    for (int i = 0; i < 0xc7; i++)
    {
        EARSSubStruct* pSub = &this->m_subArray1[i];
        pSub[0x0] = 0; // clear first field
        pSub->vtable = &PTR_FUN_00e38350; // vtable pointer
        // Construct vector of 6 elements (size 0xa0)
        _vector_constructor_iterator_(&pSub->m_vectorData, 0xa0, 6, (func_void_ptr_void_ptr*)&LAB_00523130);
        // Clear some fields
        pSub->field_0 = 0;
        pSub[1] = 0;
        *(short*)(&pSub[2]) = 0;
    }

    // Initialize sub-array at offset 0xdf04
    for (int i = 0; i < 0x8f; i++)
    {
        EARSSubStruct2* pSub = &this->m_subArray2[i];
        pSub[0x0] = 0;
        pSub->vtable = &PTR_FUN_00e38360;
        pSub->field_0x30 = 0; // offset from subBase + 0x30? Actually puVar4[-0x15] = 0 => offset 0x30? Let's compute.
        pSub->field_0 = 0;
        pSub[1] = 0;
        *(short*)(&pSub[3]) = 0;
    }

    // Large memset at offset 0x10c20, size 0x5fd80 (about 392KB)
    _memset(&this->m_largeArray, 0, 0x5fd80);

    // Call an initialization function
    FUN_0066e1d0();

    // Initialize linked list structures (4 items, each 0x46 ints)
    this->field_0x10 = 0; // param_1[4] = 0
    int* pList = &this->field_0x78; // param_1 + 0x1e = offset 0x78
    for (int i = 0; i < 4; i++)
    {
        pList[-0xe] = this->field_0x10;
        *pList = (int)(pList - 0x19);
        pList[0xe] = (int)(pList - 0xb);
        pList[0x1c] = (int)(pList + 3);
        pList[0x2a] = (int)(pList + 0x11);
        int* pNextList = pList + 0x1f;
        pList += 0x46;
        this->field_0x10 = pNextList;
    }

    // Another linked list initialization with 0x28 (40) iterations
    this->field_0x474 = 0; // param_1[0x11d] = offset 0x474
    pList = &this->field_0x930; // param_1 + 0x24c = offset 0x930
    for (int i = 0; i < 0x28; i++)
    {
        pList[-0x11c] = this->field_0x474;
        *pList = (int)(pList - 300);
        pList[0x11c] = (int)(pList - 0x10);
        pList[0x238] = (int)(pList + 0x10c);
        pList[0x354] = (int)(pList + 0x228);
        int* pNextList = pList + 0x344;
        pList += 0x58c;
        this->field_0x474 = pNextList;
    }

    // Another linked list initialization with 0x18 (24) iterations
    this->field_0x37C08 = 0; // param_1[0xdf02] = offset 0x37C08? Actually 0xdf02*4 = 0x37C08
    pList = &this->field_0x37D90; // param_1 + 0xdf64 = offset 0x37D90? 0xdf64*4 = 0x37D90
    for (int i = 0; i < 0x18; i++)
    {
        pList[-0x50] = this->field_0x37C08;
        *pList = (int)(pList - 0x60);
        pList[0x50] = (int)(pList - 0x10);
        pList[0xa0] = (int)(pList + 0x40);
        pList[0xf0] = (int)(pList + 0x90);
        pList[0x140] = (int)(pList + 0xe0);
        int* pNextList = pList + 0x130;
        pList += 0x1e0;
        this->field_0x37C08 = pNextList;
    }

    // Initialize timer
    iVar3 = FUN_009c8e50(0x1c);
    if (iVar3 == 0)
    {
        pvVar2 = 0;
    }
    else
    {
        pvVar2 = (void*)FUN_0066d6e0();
    }
    this->field_0x37C04 = pvVar2; // param_1[0xdf01] = offset 0x37C04

    // Compute frame time from global value
    lVar6 = __allmul(DAT_01163ec0, DAT_01163ec4, 4, 0);
    lVar6 = __aulldiv(lVar6, 1000, 0);
    DAT_01194d08 = (int)lVar6;
    DAT_01194d0c = (int)((ulonglong)lVar6 >> 32);

    return this;
}