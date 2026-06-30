// FUNC_NAME: BuildingManager::~BuildingManager
void __fastcall BuildingManager::dtor(uint32_t* this)
{
    // Set vtable pointers for dual inheritance (first base at +0x00, second at +0x08)
    *(uint32_t*)this = (uint32_t)&PTR_FUN_00d5f784;
    *(uint32_t*)((char*)this + 8) = (uint32_t)&PTR_LAB_00d5f77c;

    // Release owned sub-objects if they exist (offsets: 0x7b*4=0x1EC, 0x49*4=0x124)
    if (this[0x7b] != 0) // +0x1EC sub-object pointer
    {
        FUN_004daf90(&this[0x7b]); // delete sub-object 1
    }
    if (this[0x49] != 0) // +0x124 sub-object pointer
    {
        FUN_004daf90(&this[0x49]); // delete sub-object 2
    }

    // Global manager cleanup
    FUN_006c9820();
}