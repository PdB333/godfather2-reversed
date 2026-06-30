// FUNC_NAME: EARSStreamManager::~EARSStreamManager
void __thiscall EARSStreamManager::~EARSStreamManager(void* this) // Function address: 0x00412230
{
    // Set vtable pointer (derived class)
    *(int**)this = &PTR_FUN_00e2f504;
    // Set a secondary vtable or base pointer at offset +0x208
    *(int**)((char*)this + 0x208) = &PTR_LAB_00e2f52c;

    // Call base class destructor (or chain cleanup)
    FUN_00412130();

    // Check and release sub-object at offset +0x20C
    if (*(void**)((char*)this + 0x20C) != nullptr) {
        FUN_009c8f10(*(void**)((char*)this + 0x20C));
    }

    // Update secondary pointer at +0x208 to a different vtable
    *(int**)((char*)this + 0x208) = &PTR_LAB_00e2f530;

    // Reset global streaming counter
    DAT_012233bc = 0;

    // Final cleanup call
    FUN_004c27f0();
}