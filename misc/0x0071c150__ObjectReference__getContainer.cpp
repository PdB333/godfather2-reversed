// FUNC_NAME: ObjectReference::getContainer
// Address: 0x0071c150
// Retrieves a pointer to the containing object from a stored member pointer offset.
// Used for container_of operations (like from a component back to owner entity).
// Field offsets:
//   0x00: vtable (implied)
//   0x04: unknown (likely 4 bytes)
//   0x08: m_pMember - pointer to a member (e.g., a sub-object within the containing object)
//   0x3C: m_flag - signed byte (if negative, the container can be retrieved; otherwise returns 0)

int __thiscall ObjectReference::getContainer(void) {
    int container = 0;
    int* memberPtr = *(int**)(this + 8); // m_pMember at +0x8
    if (memberPtr != NULL) {
        container = (int)(memberPtr) - 0x48; // Subtract offset of member in container
    }
    // Only return non-zero if m_flag is negative (bit7 set) and the computed pointer is valid
    if ((*(char*)(this + 0x3C) >= 0) || (container == 0)) {
        container = 0;
    }
    return container;
}