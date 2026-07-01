// FUNC_NAME: Entity::clearPointer
void __fastcall Entity::clearPointer(Entity* this) {
    // Offset +0x4C: cleared to null (likely a pointer or flag)
    *(int32_t*)((uint8_t*)this + 0x4C) = 0;
}