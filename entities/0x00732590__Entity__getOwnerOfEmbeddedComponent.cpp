// FUNC_NAME: Entity::getOwnerOfEmbeddedComponent
// Function at 0x00732590
// Returns the owning object pointer from a stored pointer to an embedded component.
// The component is expected to be located at offset +0x48 inside its parent object.
// Field at +0x1e9c holds a pointer to the component (non-zero means valid).

int __thiscall Entity::getOwnerOfEmbeddedComponent(Entity *this) {
    // +0x1e9c: pointer to an embedded component (e.g., CrewLeaderComponent at Player+0x48)
    void *componentPtr = *(void **)((char *)this + 0x1e9c);
    if (componentPtr != nullptr) {
        // Subtract the component's offset within the parent to get the parent object
        return (int)((char *)componentPtr - 0x48);
    }
    return 0;
}