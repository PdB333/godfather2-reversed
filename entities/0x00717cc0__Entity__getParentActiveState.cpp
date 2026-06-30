// FUNC_NAME: Entity::getParentActiveState
// Function at 0x00717cc0: Retrieves the active state of the parent object.
// Checks a pointer member at offset 0x330, adjusts it by -0x48 to get a parent base,
// then validates the parent and returns its state.
uint __thiscall Entity::getParentActiveState() {
    uint ownerBase;
    int* ownerPtr = *(int**)((int)this + 0x330); // +0x330: pointer to child/component

    if (ownerPtr == nullptr) {
        ownerBase = 0;
    } else {
        ownerBase = (uint)((char*)ownerPtr - 0x48); // subtract offset to get parent structure base
    }

    if (ownerBase != 0) {
        uint isActive = FUN_0071ce70(ownerBase); // check if parent is active
        if (isActive != 0) {
            uint state = FUN_0071be60(); // retrieve state from parent
            return state;
        }
    }
    return ownerBase & 0xffffff00; // return cleaned identifier (low byte cleared)
}