// FUNC_NAME: SomeGameObject::attachToManagerLists
// This function appears to register the object with two separate intrusive linked lists.
// It sets a flag and inserts the object's embedded node into two lists (likely for different subsystems).
// The early return condition may be a budget check; if memory is tight, it avoids adding.

void __thiscall SomeGameObject::attachToManagerLists(void* param_2, void* param_3, uint32_t param_4)
{
    // Check if the object's owner/state suggests we're under memory pressure
    if (m_ownerState != 0 && m_ownerState != 0xFFFFD8BC)
    {
        uint32_t allocFlags = 0x20000;
        uint32_t allocResult = FUN_007e04a0(allocFlags);    // memory allocation query
        uint32_t thresholdCheck = FUN_007e0790(allocResult); // returns some size
        if (thresholdCheck != 0 && thresholdCheck < 0x8000000)
        {
            // Not enough budget, skip attachment
            return;
        }
    }

    m_attachedFlag = 1;   // +0xFC

    // ---- Insert param_3 into list A (head at +0x100) ----
    ListNode** listAHead = (ListNode**)(this + 0x100);
    ListNode* newNodeA = (param_3 != 0) ? (ListNode*)((char*)param_3 + 0x48) : 0; // embedded node offset 0x48
    if (*listAHead != newNodeA)
    {
        if (*listAHead != 0)
        {
            FUN_004daf90(listAHead); // remove old head from list
        }
        *listAHead = newNodeA;

        if (newNodeA != 0)
        {
            // Save old next pointer (at node+4) into m_listABackLink (+0x104)
            m_listABackLink = *(uint32_t*)(newNodeA + 4);
            // Set node's next pointer to address of list head (circular/instrusive)
            *(ListNode***)(newNodeA + 4) = listAHead;
        }
    }

    // ---- Insert param_2 into list B (head at +0x108) ----
    ListNode** listBHead = (ListNode**)(this + 0x108);
    ListNode* newNodeB = (param_2 != 0) ? (ListNode*)((char*)param_2 + 0x48) : 0;
    if (*listBHead != newNodeB)
    {
        if (*listBHead != 0)
        {
            FUN_004daf90(listBHead);
        }
        *listBHead = newNodeB;

        if (newNodeB != 0)
        {
            m_listBBackLink = *(uint32_t*)(newNodeB + 4); // +0x10C
            *(ListNode***)(newNodeB + 4) = listBHead;
        }
    }

    m_extraData = param_4;   // +0x110

    FUN_0090bb90(1); // notify/update some global state
}