// FUNC_NAME: TNL::PacketNode::initNode (0x00644ae0)

void __thiscall TNL::PacketNode::initNode(uint tagOffset, TNL::PacketManager* manager)
{
    // +0x04: flags (low bit = 1 indicates node is in use? tagOffset identifies node type)
    this->flags = tagOffset | 1;

    // +0x08, +0x0C: circular linked list pointers (prev, next) – point to self initially
    this->prev = this;
    this->next = this;

    // Write the tag offset into the node's memory at that same offset (self‑identifying marker)
    *(uint*)((uint8*)this + tagOffset) = tagOffset;

    // If the manager's pool hasn't been fully initialized yet (byte at +0x46C == 0)
    if (manager->poolInitialized == '\0')
    {
        // +0x440: pointer to a pool descriptor structure
        uint32* poolDesc = (uint32*)manager->poolDescriptor;

        // +0x04 in poolDesc contains a relative offset (stored in a compressed/shifted form)
        uint32 relativeOffset = *(poolDesc + 1);

        // Recover the actual offset: shift right 1, clear low 2 bits (4‑byte alignment)
        uint32 alignedOffset = (relativeOffset >> 1) & 0x3FFFFFFC;

        // +0x468: set manager's "lastAllocated" pointer to the computed address
        manager->lastAllocated = (uint32*)((uint8*)poolDesc + alignedOffset);
    }
}