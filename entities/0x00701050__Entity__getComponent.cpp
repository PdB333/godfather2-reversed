// FUNC_NAME: Entity::getComponent
// Function at 0x00701050: Simple inline getter returning the value at offset 0x2DC from this pointer.
// This is likely a pointer to a component (e.g., damage component, owner, or some data block)
uint32_t __thiscall Entity::getComponent() const {
    return *(uint32_t*)((uint8_t*)this + 0x2DC);
}