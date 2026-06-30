// Function at 0x006b1980: Returns pointer to data block at offset 0xF0 in Entity.
// FUNC_NAME: Entity::getDataBlock
void* __thiscall Entity::getDataBlock(void* this) {
    return (char*)this + 0xF0;
}