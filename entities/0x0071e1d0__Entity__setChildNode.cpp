// FUNC_NAME: Entity::setChildNode

// Function address: 0x0071e1d0
// Sets the child node pointer to a new node, handling linked list backlinks.
// The child node is embedded in a container at offset 0x48.
// The container (pNewChildContainer) has a backlink pointer at +0x04 and a value at +0x11c.
// The parent object (this) stores the child node pointer at +0x78 and a saved backlink at +0x7c.

struct Container; // forward declaration

void __thiscall Entity::setChildNode(void *pNewChildContainer) {
    int *pChildNodePtr = (int *)((char *)this + 0x78); // this->m_pChildNode (offset +0x78)
    int iOldNodeAddr, iNewNodeAddr;
    Container *pOldContainer = nullptr;
    Container *pNewContainer = (Container *)pNewChildContainer;

    // Handle removal of old child if it exists and is valid
    if (*pChildNodePtr != 0 && *pChildNodePtr != 0x48) {
        // Get the container from the old child node pointer
        if (*pChildNodePtr == 0) {
            iOldNodeAddr = 0;
        } else {
            iOldNodeAddr = *pChildNodePtr - 0x48; // subtract offset of node inside container
        }
        pOldContainer = (Container *)iOldNodeAddr;

        // Check if the old container has a flag (bit0 at offset 0x114) and perform cleanup
        if ((*(uint8 *)((char *)pOldContainer + 0x114) & 1) != 0) {
            // Call some cleanup function on the old container
            FUN_0071e180(pOldContainer);
        }

        // Copy value from old container's offset 0x11c to this's offset 0x80
        *(int *)((char *)this + 0x80) = *(int *)((char *)pOldContainer + 0x11c);
    }

    // Compute new node pointer: container+0x48
    int *pNewNode = (int *)(pNewContainer ? (char *)pNewContainer + 0x48 : nullptr);

    // Only update if the pointers differ
    if (*pChildNodePtr != (int)pNewNode) {
        // Remove old node from list (if any)
        if (*pChildNodePtr != 0) {
            FUN_004daf90(pChildNodePtr);
        }

        // Set the new child node pointer
        *pChildNodePtr = (int)pNewNode;

        if (pNewNode != nullptr) {
            // Save the old backlink pointer (which pointed to this node) into this's saved backlink
            *(int **)((char *)this + 0x7c) = *(int **)((char *)pNewContainer + 4); // container's +0x04

            // Update the new node's backlink to point to this child pointer location
            *(int **)((char *)pNewContainer + 4) = pChildNodePtr;
        }
    }
}