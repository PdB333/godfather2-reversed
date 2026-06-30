// FUNC_NAME: EntityComponent::canActivate
bool __thiscall EntityComponent::canActivate(EntityComponent* thisObj)
{
    // +0x48 points to a member pointer that is offset by 0x48 from some parent structure.
    // This retrieves the parent object's base address.
    Entity* parentObj;
    if (thisObj->m_pOwner != nullptr) {  // +0x48: pointer to owner/parent (offset within child)
        parentObj = (Entity*)(thisObj->m_pOwner - 0x48); // Recover parent base
    } else {
        parentObj = nullptr;
    }

    // +0x218 is a field in the parent that indicates availability or a counter.
    if (parentObj != nullptr && parentObj->m_nAvailableSlots != 0) { // +0x218
        int freeSlot = FUN_00572780(); // Returns -1 if no free slot, else slot index
        if (freeSlot != -1) {
            return true;
        }
    }
    return false;
}