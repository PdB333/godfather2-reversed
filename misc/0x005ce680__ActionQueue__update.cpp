// FUNC_NAME: ActionQueue::update
// Address: 0x005ce680
// This function appears to be a queue update tick that processes nodes (actions/events).
// It traverses a singly linked list starting from m_head (stored at +0x04).
// For each node, if the type (+0x04) is 8 and the pending count (+0x34) is less than 12,
// it calls FUN_005ced60 (likely to process/execute the action). If type > 2, it decrements
// the type field (used as a countdown). After each node, m_head is moved to the next node.
// At the end, the pending count is cleared, and the global age counter (+0x38) is decremented if > 2.

// Assumed struct layout for each node in the linked list:
// struct ActionNode {
//     int unknown;           // +0x00 (perhaps previous pointer or data)
//     int type;              // +0x04 (action type, if >2 it's a countdown, type==8 triggers processing)
//     // ... other fields (likely 0x20 bytes total before next pointer)
//     ActionNode* next;      // +0x20
// };

// Assumed member offsets for this class:
// +0x00: m_firstNode (first node? possibly root, but used to initialize m_head)
// +0x04: m_headNode (current traversal pointer)
// +0x34: m_pendingNodeCount (count of pending processed nodes, reset each tick)
// +0x38: m_ageCounter (global tick counter, decremented if >2 at end)

// The decompiled code:
//   iVar1 = *unaff_ESI;               -> currentNode = m_firstNode
//   unaff_ESI[1] = iVar1;             -> m_headNode = currentNode
//   while (iVar1 != 0) {
//     iVar2 = *(int *)(iVar1 + 4);    -> nodeType = currentNode->type
//     if (iVar2 == 8) {
//       if (unaff_ESI[0xd] < 0xc) {  -> if (m_pendingNodeCount < 12)
//         FUN_005ced160(...,1);       -> processNode(this, currentNode, buffers..., 1)
//         unaff_ESI[1] = iVar1;       -> m_headNode = currentNode (redundant? maybe for consistency)
//       }
//     } else if (2 < iVar2) {
//       *(int *)(iVar1 + 4) = iVar2 + -1; -> currentNode->type--
//     }
//     iVar1 = *(int *)(unaff_ESI[1] + 0x20);  -> currentNode = m_headNode->next
//     unaff_ESI[1] = iVar1;                   -> m_headNode = currentNode
//   }
//   unaff_ESI[0xd] = 0;               -> m_pendingNodeCount = 0
//   if (2 < unaff_ESI[0xe]) {
//     unaff_ESI[0xe] = unaff_ESI[0xe] + -1; -> m_ageCounter--
//   }

void ActionQueue::update()
{
    Node* currentNode = this->m_firstNode;          // +0x00
    this->m_headNode = currentNode;                  // +0x04

    while (currentNode != 0)
    {
        int nodeType = currentNode->type;            // +0x04

        if (nodeType == 8)
        {
            if (this->m_pendingNodeCount < 12)       // +0x34
            {
                // Buffers for the called function (unknown size)
                uint8_t buffer1[16];                 // local_60
                uint8_t buffer2[16];                 // local_70
                uint8_t buffer3[76];                 // local_50

                // Call the processing function
                FUN_005ced60(this, currentNode, buffer1, buffer2, buffer3, 0, 0, 0, 0, 1);

                // Update head to current node (possibly to re-insert or mark processed)
                this->m_headNode = currentNode;      // +0x04
            }
        }
        else if (nodeType > 2)
        {
            // Decrement the type (countdown timer)
            currentNode->type = nodeType - 1;        // +0x04
        }

        // Move to the next node
        currentNode = this->m_headNode->next;        // +0x20
        this->m_headNode = currentNode;              // +0x04
    }

    // Reset pending count
    this->m_pendingNodeCount = 0;                    // +0x34

    // Decrement global age counter if above 2
    if (this->m_ageCounter > 2)                      // +0x38
    {
        this->m_ageCounter--;
    }
}