// FUNC_NAME: UnknownClass::initOnce

void __thiscall UnknownClass::initOnce(UnknownClass* this)
{
    // +0x4a: ushort initialization flags (bit 0 = has been initialized)
    if (!(this->m_initFlags & 1))
    {
        // One-time initialization routines
        sub_5c1f00();              // global initialization
        sub_5c1f60(this);          // instance-specific initialization
        this->m_initFlags |= 1;    // mark as initialized
    }
}