// FUNC_NAME: SomeBaseClass::SomeBaseClass (constructor)

void __fastcall SomeBaseClass::constructor(SomeBaseClass* this)
{
    int* someData = reinterpret_cast<int*>(this->field_0x184); // param_1[0x61]

    this->vtable = &g_someBaseClassVtable; // *param_1 = &PTR_FUN_00d7d7f0
    this->m_pfnOffset0x3C = &g_funcTable0x3C; // param_1[0xf] = &PTR_LAB_00d7d7e0
    this->m_pfnOffset0x48 = &g_funcTable0x48; // param_1[0x12] = &PTR_LAB_00d7d7dc
    this->m_pfnOffset0x50 = &g_funcTable0x50; // param_1[0x14] = &PTR_LAB_00d7d7d8
    this->m_pfnOffset0x54 = &g_funcTable0x54; // param_1[0x15] = &PTR_LAB_00d7d778
    this->m_pfnOffset0x58 = &g_funcTable0x58; // param_1[0x16] = &PTR_LAB_00d7d710

    if (someData != 0)
    {
        if (reinterpret_cast<int*>(someData[2]) != 0) // iVar1 + 8
        {
            FUN_009e7530(someData); // cleanup or release
        }
        FUN_009f01a0(); // some global reset / shutdown
    }

    FUN_0046ea20(); // base class initializer (likely BaseObject::BaseObject)
}