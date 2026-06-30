// FUNC_NAME: DataManager::processEntryById
void __thiscall DataManager::processEntryById(DataEntry* entry, int* param)
{
    // DataManager linked list at offset 0x24 is a circular doubly linked list of nodes.
    // Each node has next at +0x0, prev at +0x4, and pointer to DataEntry at +0x8.
    // DataEntry struct: m_name1 at +0x0, m_name2 at +0x10, m_id at +0x20.
    Node* currentNode = *(Node**)this[0x9];  // head of list

    while (true)
    {
        if (currentNode == (Node*)this[0x9])  // wrapped around, not found
        {
            return;
        }

        // Validate current node (safety check)
        if (currentNode == (Node*)this[0x9])
        {
            FUN_00b97aea();  // likely assert or error handler
        }

        DataEntry* dataEntry = currentNode->entry;  // +0x8

        if (*param == dataEntry->m_id)  // +0x20, compare ID
        {
            break;  // found match
        }

        // Safety check again (redundant?)
        if (currentNode == (Node*)this[0x9])
        {
            FUN_00b97aea();
        }

        currentNode = currentNode->next;  // advance to next node
    }

    // Retrieve the two strings from the entry
    const char* stringA = dataEntry->m_name1;  // +0x0
    if (stringA == nullptr)
    {
        stringA = (const char*)0x0120546e;  // placeholder empty string
    }

    const char* stringB = dataEntry->m_name2;  // +0x10
    if (stringB == nullptr)
    {
        stringB = (const char*)0x0120546e;
    }

    // Call virtual function at vtable offset 0x1c (index 7)
    // This function takes the two strings and the second value of param (param[1])
    (this->vtable->processEntry)(stringA, stringB, param[1]);

    return;
}