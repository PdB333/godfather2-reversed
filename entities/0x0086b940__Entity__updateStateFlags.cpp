// FUNC_NAME: Entity::updateStateFlags
void __fastcall Entity::updateStateFlags(Entity* this)
{
    // Offset 0xC8 (200) is a flags field: byte[0xC8] contains bit 6, ushort[0xC8] contains bit 0
    if (((*(uint8_t*)((uintptr_t)this + 0xC8) >> 6) & 1) == 0) {
        *(uint16_t*)((uintptr_t)this + 0xC8) |= 1;
    }
}