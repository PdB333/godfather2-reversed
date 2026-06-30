// FUNC_NAME: EntityRef::getAliveHandle
int __fastcall EntityRef::getAliveHandle()
{
    uint32_t* entityPtr = *(uint32_t**)((char*)this + 0x0C); // +0x0C: pointer to game entity
    uint32_t entityHandle = (uint32_t)entityPtr >> 8;       // Extract upper 24 bits as handle

    if (entityPtr != nullptr &&
        (*(uint32_t*)(entityPtr + 0x30 / sizeof(uint32_t)) >> 1 & 1) == 0 && // +0x30: dead flag (bit1 clear = alive)
        (*(uint8_t*)((char*)entityPtr + 0x3C) & 1) == 0)                     // +0x3C: destroyed flag (bit0 clear = intact)
    {
        return (int)((entityHandle << 8) | 1);             // Valid: return handle with low byte = 1
    }
    return (int)(entityHandle << 8);                       // Invalid: return handle with low byte = 0
}