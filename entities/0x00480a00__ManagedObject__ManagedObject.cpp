// FUNC_NAME: ManagedObject::ManagedObject
void __fastcall ManagedObject::ManagedObject(ManagedObject *this)
{
    ManagedObject *listHead;
    ManagedObject *listNode;
    ManagedObject *listNext;

    // Set vtable pointer and interface vtable pointers
    this->vtable = &PTR_FUN_00e33404;               // +0x00
    this->m_pInterfaceVTable1 = &PTR_LAB_00e33420;   // +0x3C
    this->m_pInterfaceVTable2 = &PTR_LAB_00e33430;   // +0x48
    this->m_pInterfaceVTable3 = &PTR_LAB_00e33434;   // +0x50 (initial)

    // Log a shutdown string (likely for debugging or state tracking)
    writeLog("shutdown");

    // Construct sub-objects at offsets +0x54 and +0x5C
    constructSubObject(&this->m_subObject1); // +0x54
    constructSubObject(&this->m_subObject2); // +0x5C
    initializeSubObject(&this->m_subObject1); // +0x54
    initializeSubObject(&this->m_subObject2); // +0x5C

    // Construct a global singleton (likely a manager or registry)
    constructSubObject(&g_GlobalObject); // DAT_0120e93c

    // Insert this object into a circular linked list (sentinel head at m_listHead)
    listHead = this->m_listHead; // +0x78
    if (listHead != 0)
    {
        listNode = *(ManagedObject **)((char *)listHead + 4); // skip sentinel? -> listHead->next
        if (listNode == &this->m_listHead) // only one node in list?
        {
            // Repair list: set head's next to new node (this->m_nodeNext)
            *(ManagedObject **)((char *)listHead + 4) = this->m_nodeNext; // +0x7C
            // Update interface vtable to final value
            this->m_pInterfaceVTable3 = &PTR_LAB_00e32854; // +0x50
            registerObject(); // call final registration
            return;
        }
        // Find the last node (node that points to sentinel head)
        listNext = listNode->m_listNext;
        while (listNext != &this->m_listHead)
        {
            listNode = listNode->m_listNext;
            listNext = listNode->m_listNext;
        }
        // Set that node's next to the new node
        listNode->m_listNext = this->m_nodeNext; // +0x7C
    }
    // Update interface vtable to final value
    this->m_pInterfaceVTable3 = &PTR_LAB_00e32854; // +0x50
    registerObject();
}