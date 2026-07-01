// FUNC_NAME: Entity::getField64
uint32_t __fastcall Entity::getField64(Entity* this) {
    // Returns the value at offset +0x64 from this pointer
    return *(uint32_t*)((char*)this + 0x64);
}