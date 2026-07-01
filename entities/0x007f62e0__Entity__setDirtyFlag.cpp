// FUNC_NAME: Entity::setDirtyFlag
void __fastcall Entity::setDirtyFlag(Entity* this) {
    // Set bit 0x20 in the dirty flags field at offset +0x970
    *(uint32_t*)((uint8_t*)this + 0x970) |= 0x20;
}