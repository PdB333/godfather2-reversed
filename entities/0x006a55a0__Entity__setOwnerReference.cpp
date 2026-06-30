// FUNC_NAME: Entity::setOwnerReference
void __thiscall Entity::setOwnerReference(Entity** ownerPtr) {
    int* currentOwnerSlot = reinterpret_cast<int*>(this + 0x694); // pointer to m_pOwner
    if (currentOwnerSlot != reinterpret_cast<int*>(ownerPtr)) {
        int newOwner = *ownerPtr;
        if (*currentOwnerSlot != newOwner) {
            if (*currentOwnerSlot != 0) {
                FUN_004daf90(currentOwnerSlot); // release old owner
            }
            *currentOwnerSlot = newOwner;
            if (newOwner != 0) {
                *(reinterpret_cast<int*>(this + 0x698)) = *(reinterpret_cast<int*>(newOwner + 4)); // store previous backlink
                *reinterpret_cast<int**>(newOwner + 4) = currentOwnerSlot; // link back to this slot
            }
        }
    }
    // Reset local offset/velocity fields
    *reinterpret_cast<Vector3D*>(this + 0x14) = Vector3D::zero;
}