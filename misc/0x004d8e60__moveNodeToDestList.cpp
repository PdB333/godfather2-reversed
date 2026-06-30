// FUNC_NAME: moveNodeToDestList

// Globals (defined elsewhere, offsets documented)
int* g_sourceListHead; // +0x00 head of source linked list (DAT_012189f8)
int* g_destListHead;   // +0x00 head of destination linked list (DAT_01218a00)
int* g_destListTail;   // +0x00 tail of destination linked list (DAT_012189fc)

// Structure: node with next pointer at +0xF0
void moveNodeToDestList(int node) {
    int* pNode = reinterpret_cast<int*>(node);
    int* pPrev = nullptr;

    if (g_sourceListHead != nullptr) {
        if (g_sourceListHead == pNode) {
            // Remove head of source list
            pPrev = pNode; // Keep reference to node
            g_sourceListHead = reinterpret_cast<int*>(*reinterpret_cast<int*>(pNode + 0xF0));
        } else {
            // Traverse to find predecessor
            pPrev = g_sourceListHead;
            while (true) {
                int* pNext = reinterpret_cast<int*>(*reinterpret_cast<int*>(pPrev + 0xF0));
                if (pNext == pNode) {
                    break;
                }
                pPrev = pNext;
                if (*reinterpret_cast<int*>(pPrev + 0xF0) == 0) {
                    return; // Node not found
                }
            }
            // Unlink node
            *reinterpret_cast<int*>(pPrev + 0xF0) = *reinterpret_cast<int*>(pNode + 0xF0);
        }

        // Disconnect node from its list
        *reinterpret_cast<int*>(pNode + 0xF0) = 0;

        // Append node to destination list
        if (g_destListHead != nullptr) {
            *reinterpret_cast<int*>(g_destListTail + 0xF0) = pNode;
            g_destListTail = pNode;
            return;
        }

        // Destination list was empty, node becomes both head and tail
        g_destListHead = pNode;
        g_destListTail = pNode;
        return;
    }
    // Source list empty - no operation (globals unchanged)
}