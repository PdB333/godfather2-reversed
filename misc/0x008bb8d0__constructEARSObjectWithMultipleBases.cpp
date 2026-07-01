// FUNC_NAME: constructEARSObjectWithMultipleBases
void __fastcall constructEARSObjectWithMultipleBases(uint32_t* thisObj)
{
    // Set vtable pointers for multiple inheritance
    thisObj[0]      = (uint32_t)&PTR_FUN_00d7b828;  // +0x00
    thisObj[0xF]    = (uint32_t)&PTR_LAB_00d7b818;  // +0x3C
    thisObj[0x12]   = (uint32_t)&PTR_LAB_00d7b814;  // +0x48
    thisObj[0x14]   = (uint32_t)&PTR_LAB_00d7b810;  // +0x50
    thisObj[0x15]   = (uint32_t)&PTR_LAB_00d7b7b0;  // +0x54
    thisObj[0x16]   = (uint32_t)&PTR_LAB_00d7b748;  // +0x58
    thisObj[0x60]   = (uint32_t)&PTR_LAB_00d7b734;  // +0x180

    // Zero-initialize two sub-objects at offsets 0x290 and 0x29C
    FUN_00408310(thisObj + 0xA4);
    FUN_00408310(thisObj + 0xA7);

    // Global EARS framework initialization (vtable registration etc.)
    FUN_008ba520();
}