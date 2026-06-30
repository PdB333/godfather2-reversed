// FUNC_NAME: TNLConnection::setGhostPacketData
void TNLConnection::setGhostPacketData(int ghostId, int packetId, void* data, int dataWordCount)
{
    // Linked list of packet nodes (head at this+0x94)
    PacketNode* node = this->packetListHead;

    // Search for existing node matching (ghostId, packetId)
    while (node != nullptr)
    {
        if (node->ghostId == ghostId && node->packetId == packetId)
        {
            // Update existing data
            memcpy(node->data, data, dataWordCount * 4);
            return;
        }
        node = node->next;
    }

    // No existing node found – we may need to create one
    PacketNode* newNode = nullptr;

    // Ghost manager at this+0x90, containing array of ghost objects
    GhostManager* mgr = this->ghostManager;
    if (mgr->objectCount != 0)
    {
        for (unsigned int i = 0; i < mgr->objectCount; i++)
        {
            // Ghost object stride 0xB0
            GhostObject* obj = reinterpret_cast<GhostObject*>(
                reinterpret_cast<char*>(mgr->objectArray) + i * 0xB0);

            // Each ghost object has a pointer at +0x54 (e.g., to network ghost)
            void* ghostPtr = obj->associatedGhost;
            if (ghostPtr != nullptr)
            {
                // The ghost has two ID fields (+0x10 and +0x18)
                int idLow  = *reinterpret_cast<int*>(static_cast<char*>(ghostPtr) + 0x10);
                int idHigh = *reinterpret_cast<int*>(static_cast<char*>(ghostPtr) + 0x18);

                // If either matches the requested ghostId, link the packet node
                if (idLow == ghostId || idHigh == ghostId)
                {
                    if (newNode == nullptr)
                    {
                        // Allocate a new packet node (function at 0x0042c5d0)
                        newNode = allocatePacketNode();
                        if (newNode == nullptr)
                            return; // allocation failure

                        newNode->ghostId       = ghostId;
                        newNode->packetId      = packetId;
                        newNode->dataSize      = dataWordCount; // in ints
                        memcpy(newNode->data, data, dataWordCount * 4);

                        // Insert at front of linked list
                        newNode->next = this->packetListHead;
                        this->packetListHead = newNode;
                    }

                    // Update the ghost object's packet pointer at +0x80
                    obj->packetNode = newNode;
                }
            }
        }
    }
}