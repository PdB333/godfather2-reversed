// FUNC_NAME: EARSObject::EARSObject
void __fastcall EARSObject::EARSObject(void* this)
{
    FUN_00612e00(); // Base class constructor
    *(int32_t*)((intptr_t)this + 0x10) = 0; // +0x10: m_fieldOne
    *(int32_t*)((intptr_t)this + 0x14) = 0; // +0x14: m_fieldTwo
    return;
}