// FUNC_NAME: SimManager::~SimManager
void __fastcall SimManager_dtor(void* this) // __thiscall, this in ECX
{
    int countA;
    int i;
    int countB;
    int* iter;
    int countC;
    // Local buffer for ID lookup
    char buf[8];
    
    // Set vtables for derived class (likely multiple inheritance)
    *(int**)this = &PTR_FUN_00e39fb0;                     // primary vtable
    *(int**)((char*)this + 8) = &PTR_LAB_00e39fc8;        // secondary base vtable
    *(int**)((char*)this + 12) = &PTR_LAB_00e39fdc;       // third base vtable
    
    // Destroy first sub‑object container (array at offset 8)
    countA = *(int*)((char*)this + 0x80);                  // +0x80: count for first array
    for (i = 0; i < countA; i++)
    {
        FUN_009f2410((char*)this + 8);                    // cleanup each element in sub‑object at +8
    }
    *(int*)((char*)this + 0x80) = 0;                      // reset count
    
    // Destroy second sub‑object container (array at offset 12)
    countB = *(int*)((char*)this + 0x8C);                  // +0x8C: count for second array
    for (i = 0; i < countB; i++)
    {
        FUN_00a0dec0((char*)this + 12);                   // cleanup each element in sub‑object at +12
    }
    *(int*)((char*)this + 0x8C) = 0;                      // reset count
    
    // Search for a specific resource (ID 0x1300) in a separate list
    countC = *(int*)(*(int*)((char*)this + 0x30) + 0x78); // pointer at +0x30 points to object with count at +0x78
    if (countC > 0)
    {
        iter = *(int**)(*(int*)((char*)this + 0x30) + 0x74); // array at +0x74
        for (i = 0; i < countC; i++)
        {
            if (*iter == 0x1300)                           // resource type ID
            {
                FUN_009f0250(buf, 0x1300);                // lookup and potentially remove
                break;
            }
            iter++;
        }
    }
    
    FUN_009f01a0();                                       // global cleanup – possibly resource manager finalize
    
    // Free allocated memory blocks using thread‑local allocator (tag 0x17)
    int slotIndex1 = *(int*)((char*)this + 0x90);          // +0x90: index (or size)
    if (slotIndex1 >= 0)
    {
        TlsGetValue(DAT_01139810);                        // get thread‑local storage
        FUN_00aa26e0(*(void**)((char*)this + 0x88), slotIndex1 * 4, 0x17); // free pointer at +0x88
    }
    
    int slotIndex2 = *(int*)((char*)this + 0x84);          // +0x84
    if (slotIndex2 >= 0)
    {
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(*(void**)((char*)this + 0x7C), slotIndex2 * 4, 0x17);
    }
    
    int slotIndex3 = *(int*)((char*)this + 0x78);          // +0x78
    if (slotIndex3 >= 0)
    {
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(*(void**)((char*)this + 0x70), slotIndex3 * 4, 0x17);
    }
    
    int slotIndex4 = *(int*)((char*)this + 0x6C);          // +0x6C
    if ((int)slotIndex4 >= 0)
    {
        TlsGetValue(DAT_01139810);
        // Each element is 0x30 bytes, only low 30 bits used for count
        FUN_00aa26e0(*(void**)((char*)this + 0x64), (slotIndex4 & 0x3FFFFFFF) * 0x30, 0x17);
    }
    
    // Restore vtables to base class destructors (for destruction ordering)
    *(int**)((char*)this + 12) = &PTR_LAB_00e39f9c;
    *(int**)((char*)this + 8) = &PTR_LAB_00dc3dd4;
    *(int**)this = &PTR_LAB_00d96914;
}