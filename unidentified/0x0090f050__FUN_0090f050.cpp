// FUNC_NAME: UnknownClass::deserialize
void __thiscall UnknownClass::deserialize(int *this, const int *source)
{
    int iVar1;
    int iVar2;
    bool bCondition;

    // Copy fields from source to this
    this[0x14] = *source;                         // m_type (offset +0x50)
    FUN_004d3e20(source + 1);                     // Skip over a string/object at source[1]
    this[0x19] = source[5];                       // m_field19 (offset +0x64)
    FUN_004d3e20(source + 6);                     // Skip over another string/object at source[6]
    this[0x1e] = source[10];                      // m_field1e (offset +0x78)
    this[0x1f] = source[0xb];                     // m_field1f (offset +0x7C)
    this[0x20] = source[0xc];                     // m_field20 (offset +0x80)

    if (this[0x14] == 1)                          // Type 1
    {
        iVar1 = FUN_0084aea0(this[0x20]);         // Get some resource by ID
        if (iVar1 == 0)
            return;
        iVar1 = FUN_0084a410();                   // Query current family/group
        bCondition = (iVar1 == 0x637b907);        // Compare against constant (family hash?)
    }
    else if (this[0x14] == 4)                     // Type 4
    {
        iVar1 = *(int *)(DAT_0112a590 + 0xc);     // Global state value
        iVar2 = FUN_0084ad70(0x637b907);          // Lookup constant in some table
        bCondition = (iVar2 == iVar1);
    }
    else
    {
        goto LAB_0090f0d8;                        // No condition check for other types
    }

    if (!bCondition)
        return;                                   // Condition failed, do nothing

LAB_0090f0d8:
    // Call virtual function at vtable offset 0x28 (index 10)
    (*(void (__thiscall **)(int *))(this[0] + 0x28))(this);
}