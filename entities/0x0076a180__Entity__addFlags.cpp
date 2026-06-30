// FUNC_NAME: Entity::addFlags
// Address: 0x0076a180
// Adds bits to a flag field at offset +0xa18. If any bits are newly set (i.e., not already present), triggers a virtual notification function at vtable offset 0x28 (from pointer at +0x58) with reason code 0x20. Then updates the flag field via OR.

void __thiscall Entity::addFlags(uint bits)
{
    uint &flags = *(uint *)((uint)this + 0xa18);
    if ((flags | bits) != flags)
    {
        // vtable pointer at +0x58, notification function at +0x28
        void (__thiscall *notifyFunc)(void *, uint) = 
            *(void (__thiscall **)(void *, uint))((*(uint *)((uint)this + 0x58)) + 0x28);
        notifyFunc(this, 0x20);
        flags |= bits;
    }
}