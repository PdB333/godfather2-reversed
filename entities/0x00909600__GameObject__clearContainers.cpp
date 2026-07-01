// FUNC_NAME: GameObject::clearContainers
void __thiscall GameObject::clearContainers(char bDestroyObjects)
{
    int hasActiveObjects;
    int *pSlot;
    int slotValue;

    hasActiveObjects = CheckCondition();
    if ((hasActiveObjects != 0) || ((*(int *)(this + 100) != 0 && (*(int *)(this + 100) != 0x48)))) {
        *(uint *)(this + 0xb4) |= 5; // set flags indicating modification
    }
    if (bDestroyObjects == '\0') {
        *(undefined4 *)(this + 0xb0) = 0; // clear some state
        return;
    }
    if (hasActiveObjects != 0) {
        pSlot = (int *)(this + 0x70); // start of 6-slot array (each 8 bytes)
        do {
            slotValue = *pSlot; // first field in slot: handle or pointer
            if ((slotValue != 0) && (slotValue != 0x48)) {
                DestroySubObject(slotValue - 0xc); // base offset for structure
            }
            pSlot += 2; // advance to next slot (+8 bytes)
            hasActiveObjects = hasActiveObjects - 1;
        } while (hasActiveObjects != 0);
    }
    if (*(int *)(this + 100) != 0) {
        ReleaseHandle((undefined4 *)(this + 100)); // free associated resource
        *(undefined4 *)(this + 100) = 0;
    }
    return;
}