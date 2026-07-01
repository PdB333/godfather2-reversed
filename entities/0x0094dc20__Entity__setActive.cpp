// FUNC_NAME: Entity::setActive
// Function address: 0x0094dc20
// Role: Sets a boolean flag at offset 0xB9 to 1 (active/true).
// This is likely a member function of a base game object class (e.g., Entity, GameObject).
// The flag at +0xB9 may control visibility, update, or processing state.

void __thiscall Entity::setActive(Entity* this) {
    // Set the byte at offset 0xB9 to 1 (active)
    *(uint8_t*)((uintptr_t)this + 0xB9) = 1;
}