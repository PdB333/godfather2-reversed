// FUNC_NAME: TNLConnection::processReliablePacket
void __fastcall TNLConnection::processReliablePacket(void) {
    // +0x1a4: m_pendingReliablePacket (pointer to incoming reliable data)
    int* pendingReliable = *(int**)((int)this + 0x1a4);
    // +0x190 (400): m_currentReliablePacket (pointer to outgoing packet node)
    int* currentReliable = *(int**)((int)this + 400);

    if (pendingReliable != 0 && currentReliable != 0) {
        // Create a temporary node pointing into the packet's internal data area at +0x48
        int* tempNode = (int*)((int)currentReliable + 0x48);
        // Save the original next pointer from the packet node at +0x4c
        int savedNext = *(int*)((int)currentReliable + 0x4c);
        // Overwrite the next pointer with the address of our stack variable (marks node for cleanup)
        *(int**)((int)currentReliable + 0x4c) = &tempNode;

        // Process the pending reliable packet (likely decode/handle)
        FUN_00408a00(&pendingReliable, 0);

        // Release the current packet node (tempNode always non-null here)
        if (tempNode) {
            FUN_004daf90(&tempNode);
        }
    }
}