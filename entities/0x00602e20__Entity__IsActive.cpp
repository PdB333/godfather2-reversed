// FUNC_NAME: Entity::isActive
// Function address: 0x00602e20
// Role: Checks if the 'active' flag (int at offset +0x48) is non-zero.
bool __fastcall Entity::isActive(Entity* this) {
    return *(int*)((char*)this + 0x48) != 0;
}