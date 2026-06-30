// FUN_004403f0: GameManager::shutdown
void __fastcall GameManager::shutdown(GameManager* this)
{
    short counter;               // Local counter for wait loop

    // Set cleanup vtable pointers
    *(int*)this = &PTR_FUN_00e31088;          // +0x00: vtable for shutdown state
    *(int*)((char*)this + 4) = &PTR_LAB_00e3108c; // +0x04: secondary vtable (maybe for derived class)

    // Release global singleton references
    FUN_004086d0(&DAT_012069c4); // Decrement reference count on global A
    FUN_004086d0(&DAT_012067cc); // Decrement reference count on global B

    // Wait loop: decrement a short counter until -1, calling yield/processMessages each step
    counter = *(short*)((char*)this + 0x16); // +0x16: remaining wait ticks
    while (counter > -1)
    {
        FUN_00440b80(1); // Likely yield or process one message
        counter = *(short*)((char*)this + 0x16) - 1;
        *(short*)((char*)this + 0x16) = counter;
    }

    // Destroy all managed sub-objects (array of component layers)
    if (*(short*)((char*)this + 0x14) > 0) // +0x14: number of objects
    {
        int count = *(short*)((char*)this + 0x14);
        void** objArray = *(void***)((char*)this + 0x18); // +0x18: pointer to array of object pointers

        for (int i = 0; i < count; i++)
        {
            void* obj = objArray[i];
            if (obj != nullptr)
            {
                FUN_00441450(); // Prepare object for destruction (maybe detach)

                // Each object has three embedded sub‑layers at offsets 0, 8, 16 (each with vtable)
                // Layer 3 (offset 24 in object) – high‑level component
                ((void(__thiscall*)(void*, int))(*(int**)(*(int*)obj + 4)))(*(void**)((char*)obj + 24), 0x20);
                *(void**)((char*)obj + 24) = nullptr;
                if (*(void**)((char*)obj + 20) != nullptr)
                {
                    ((void(__thiscall*)(void*, int))(*(int**)(*(int*)(*(void**)((char*)obj + 16)) + 4)))(*(void**)((char*)obj + 20), 0);
                    *(void**)((char*)obj + 20) = nullptr;
                }
                ((void(__thiscall*)(void*))(*(int**)(*(int*)(*(void**)((char*)obj + 16)) + 0xc)))(*(void**)((char*)obj + 16));

                // Layer 2 (offset 16, 12, 8)
                if (*(void**)((char*)obj + 12) != nullptr)
                {
                    ((void(__thiscall*)(void*, int))(*(int**)(*(int*)(*(void**)((char*)obj + 8)) + 4)))(*(void**)((char*)obj + 12), 0);
                    *(void**)((char*)obj + 12) = nullptr;
                }
                ((void(__thiscall*)(void*))(*(int**)(*(int*)(*(void**)((char*)obj + 8)) + 0xc)))(*(void**)((char*)obj + 8));

                // Layer 1 (offset 0, 4) – base layer
                if (*(void**)((char*)obj + 4) != nullptr)
                {
                    ((void(__thiscall*)(void*, int))(*(int**)(*(int*)(*(void**)obj + 4)))(*(void**)((char*)obj + 4), 0);
                    *(void**)((char*)obj + 4) = nullptr;
                }
                ((void(__thiscall*)(void*))(*(int**)(*(int*)(*(void**)obj + 0xc)))(*(void**)obj);

                FUN_009c8eb0(obj); // Free the object memory
            }
        }
    }

    // Free the array of object pointers
    FUN_009c8f10(*(void**)((char*)this + 0x18));

    // Release a singleton owned by this manager
    ((void(__thiscall*)(void*))(*(int**)(*(int*)(*(void**)((char*)this + 0x1c)) + 0xc)))(*(void**)((char*)this + 0x1c));
    *(void**)((char*)this + 0x1c) = nullptr;

    // Free another allocated buffer
    FUN_009c8f10(*(void**)((char*)this + 0x20));

    // Perform global cleanup (e.g., deinitialize subsystems)
    FUN_004083d0();

    // Set final vtable for dead/destroyed state
    *(int*)this = &PTR_LAB_00e3109c; // +0x00: vtable for destructed object

    // Clear global initialization flag
    DAT_01223420 = 0;
}