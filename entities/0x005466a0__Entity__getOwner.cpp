// FUNC_NAME: Entity::getOwner
// Address: 0x005466a0
// Role: Returns the owner entity pointer stored at offset 0x2e8.
// This is a simple accessor used by many game systems to retrieve the owning entity.
__thiscall Entity* Entity::getOwner(void) {
    // Dereference the pointer at offset 0x2e8 from the 'this' pointer.
    return *(Entity**)(this + 0x2e8);
}