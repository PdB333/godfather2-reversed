// FUNC_NAME: EARSObjectBase::~EARSObjectBase
void __fastcall EARSObjectBase::~EARSObjectBase(void* this) {
    // Set vtable to a destructor-specific vtable to prevent virtual calls during destruction
    *(uint32_t*)this = (uint32_t)&vtable_EARSObjectBase_destructing; // +0x00
    // Set interface function tables (offsets 0x3C, 0x48, 0x50)
    *(uint32_t*)((char*)this + 0x3C) = (uint32_t)&interface_table_1; // +0x3C
    *(uint32_t*)((char*)this + 0x48) = (uint32_t)&interface_table_2; // +0x48
    *(uint32_t*)((char*)this + 0x50) = (uint32_t)&interface_table_3; // +0x50

    // Destroy sub-object at offset 0x70 if non-null
    uint32_t* subObj1 = (uint32_t*)((char*)this + 0x70); // +0x1c * 4 = 0x70
    if (*subObj1 != 0) {
        destroySubObject(subObj1); // FUN_004daf90
    }

    // Destroy sub-object at offset 0x68 if non-null
    uint32_t* subObj2 = (uint32_t*)((char*)this + 0x68); // +0x1a * 4 = 0x68
    if (*subObj2 != 0) {
        destroySubObject(subObj2); // FUN_004daf90
    }

    // Global cleanup/notification
    someGlobalCleanup(); // FUN_00473880
}