// FUNC_NAME: SomePoolSlot::getOwnerIfActive
// Address: 0x0071c120
// Returns the owning object from an internal node pointer (offset +8) if the slot is active (bit 9 of flags at +0x3c is set).
int __thiscall SomePoolSlot::getOwnerIfActive(void) {
    int nodePtr = *(int *)(this + 8); // Pointer to embedded node (or data)
    int ownerPtr = 0;
    if (nodePtr != 0) {
        ownerPtr = nodePtr - 0x48; // Back-calculate to containing object (node is at offset 0x48 in owner)
    }
    // Check bit 9 of the flags word (e.g., active/in-use flag)
    if (((*(unsigned short *)(this + 0x3c) >> 9) & 1) == 0 || ownerPtr == 0) {
        ownerPtr = 0;
    }
    return ownerPtr;
}