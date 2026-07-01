// FUNC_NAME: CompositeObject::releaseAllSubObjects

void __fastcall CompositeObject::releaseAllSubObjects(void *thisPtr)
{
    // The object holds three sub-object handles, each consisting of a vtable pointer and an object pointer.
    // Offsets: +0x00: vtable for sub-object 3, +0x04: pointer to sub-object 3
    //          +0x08: vtable for sub-object 2, +0x0C: pointer to sub-object 2
    //          +0x10: vtable for sub-object 1, +0x14: pointer to sub-object 1
    void **vtable1 = *(void ***)thisPtr;             // +0x10, vtable pointer for sub-object 1
    void  *obj1    = *(void **)((char *)thisPtr + 0x14); // +0x14, pointer to sub-object 1
    void **vtable2 = *(void ***)((char *)thisPtr + 0x08); // +0x08, vtable for sub-object 2
    void  *obj2    = *(void **)((char *)thisPtr + 0x0C); // +0x0C, pointer to sub-object 2
    void **vtable3 = *(void ***)((char *)thisPtr + 0x00); // +0x00, vtable for sub-object 3
    void  *obj3    = *(void **)((char *)thisPtr + 0x04); // +0x04, pointer to sub-object 3

    // Release sub-object 1
    if (obj1 != 0)
    {
        // Call release method at vtable offset 4 (e.g., Release(0) or Delete(0))
        ((void (__thiscall*)(void *, int))vtable1[1])(obj1, 0);
        *(void **)((char *)thisPtr + 0x14) = 0;
    }
    // Call static cleanup function at vtable offset 12 (e.g., destroy the vtable itself)
    ((void (*)())vtable1[3])();

    // Release sub-object 2
    if (obj2 != 0)
    {
        ((void (__thiscall*)(void *, int))vtable2[1])(obj2, 0);
        *(void **)((char *)thisPtr + 0x0C) = 0;
    }
    ((void (*)())vtable2[3])();

    // Release sub-object 3
    if (obj3 != 0)
    {
        ((void (__thiscall*)(void *, int))vtable3[1])(obj3, 0);
        *(void **)((char *)thisPtr + 0x04) = 0;
    }
    ((void (*)())vtable3[3])();
}