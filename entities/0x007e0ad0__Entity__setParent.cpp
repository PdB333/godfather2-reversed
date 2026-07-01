// FUNC_NAME: Entity::setParent
// Function at 0x007e0ad0 sets the parent of an entity, managing an intrusive linked list of children.
// Offset 0xFC: pointer to parent's child list head (or null)
// Offset 0x100: previous sibling's "next" pointer (back link)
// Parent object offset 0x48: child list head pointer
// Parent object offset 0x04: pointer to previous child's "next" slot (used for list linking)

void __thiscall Entity::setParent(Entity* newParent) {
    int** ppChildList = (int**)(this + 0xFC);  // pointer to this entity's slot for parent's child list
    int* pNewParentChildList = (newParent != nullptr) ? (int*)(newParent + 0x48) : nullptr; // new parent's child list head

    if (*ppChildList != pNewParentChildList) {
        // Remove from old parent's list if currently attached
        if (*ppChildList != nullptr) {
            // FUN_004daf90 likely is removeFromList(ppChildList)
            removeFromList(ppChildList);
        }

        *ppChildList = pNewParentChildList;  // attach to new parent's child list

        if (pNewParentChildList != nullptr) {
            // Copy the previous sibling's back link from new parent's prev field into this entity's back link
            *(int*)(this + 0x100) = *(int*)(newParent + 4); // this->m_prevSiblingSlot = newParent->prevSiblingSlot
            // Update new parent's prev field to point to this entity's child list slot
            *(int**)(newParent + 4) = ppChildList; // newParent->prevSiblingSlot = &this->m_childListSlot
        }
    }
}