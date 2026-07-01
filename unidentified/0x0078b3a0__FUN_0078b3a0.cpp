// FUNC_NAME: UnknownClass::getSomeValue
undefined __thiscall UnknownClass::getSomeValue(int this) // 0x0078b3a0
{
    undefined4 uVar1;

    uVar1 = 0;
    if ((*(int *)(this + 0x1c) != 0) && (*(int *)(this + 0x1c) != 0x3c)) // +0x1c: m_pComponent or similar
    {
        // Dereference the component pointer and read value at offset 0xec
        uVar1 = *(undefined4 *)(*(int *)(this + 0x1c) + 0xec); // +0xec: likely a property (e.g., m_id, m_health)
    }
    return uVar1;
}