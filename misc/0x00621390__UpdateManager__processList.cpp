// FUNC_NAME: UpdateManager::processList
void __fastcall UpdateManager::processList(void)
{
    ListManager *listMgr;
    ListNode *node;
    ListNode **listEnd;
    int dummy;
    byte stackBuf[12];

    listMgr = *(ListManager **)(this + 0x10);
    if (listMgr != nullptr) {
        for (ListNode *head = *(ListNode **)(listMgr + 0x20); head != nullptr; ) {
            // Get the actual node from the double pointer at +0x1c (maybe a circular list sentinel?)
            node = **(ListNode ***)(listMgr + 0x1c);
            if (node == *(ListNode **)(listMgr + 0x1c)) {
                // Empty list? Probably throws or asserts
                FUN_00b97aea();
            }
            // Check if node flags have bit 0 set
            if ((*(byte *)(node + 8) & 1) != 0) {
                if (node == *(ListNode **)(listMgr + 0x1c)) {
                    FUN_00b97aea();
                }
                // Call virtual function at vtable[1] with node->someID and 0
                (**(code **)(*(int *)(this + 4) + 4))(*(int *)(node + 16), 0);
            }
            // Process the node (maybe remove from list?)
            FUN_006217f0(*(int *)(this + 0x10), stackBuf, (int)listMgr, node);
            // Re-read listMgr and head pointer (may have changed)
            listMgr = *(ListManager **)(this + 0x10);
            head = *(ListNode **)(listMgr + 0x20);
        }
    }
}