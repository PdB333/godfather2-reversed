// FUNC_NAME: GameObject::getOptionalField
// Address: 0x004f2a40
// Retrieves a value from internal data if a flag is non-zero.
// Accesses this+4 as a pointer to an internal structure, then reads offset 0xc from that structure.
// Calls another function (FUN_004f23a0) with the fetched value.
// Returns 0 if flag is 0.

int GameObject::getOptionalField(int flag)
{
    if (flag != 0)
    {
        // this->m_data at +0x4, field at +0xc within m_data
        int value = *(int *)(*(int *)(this + 4) + 0xc);
        return FUN_004f23a0(value);
    }
    return 0;
}