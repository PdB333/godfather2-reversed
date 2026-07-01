//FUNC_NAME: Entity::clearFlagAndNotify
void __fastcall Entity::clearFlagAndNotify(void)
{
    uint32_t flags = *(uint32_t *)((uint8_t *)this + 0xc88);
    if ((flags & 0xFFFFEFFF) != flags)
    {
        // Bit 12 (0x1000) is set; clear it and call virtual function at vtable+0x28 (index 10)
        (*(void (__thiscall **)(void *, int))(*(uint32_t *)((uint8_t *)this + 0x58) + 0x28))(this, 0x10);
        *(uint32_t *)((uint8_t *)this + 0xc88) = flags & 0xFFFFEFFF;
    }
}