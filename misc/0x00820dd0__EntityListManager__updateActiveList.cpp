// FUNC_NAME: EntityListManager::updateActiveList
void __fastcall EntityListManager::updateActiveList(EntityListManager* this)
{
    int* headPtr;
    int newNode;

    // Global flag indicating whether the system is active
    if (DAT_012233a4 != 0) {
        // Get a node from the free pool (or lookup by ID at offset +0xA0)
        newNode = FUN_0044ede0(this->field_0xA0);

        headPtr = &this->listHead;  // +0xB0

        // If the node is different from current head
        if (*headPtr != newNode) {
            // Remove current head if it exists (probably unlink and return to pool)
            if (*headPtr != 0) {
                FUN_004daf90(headPtr);
            }

            // Set new head
            *headPtr = newNode;

            // If new node is not null, update its next pointer to point to the head pointer
            if (newNode != 0) {
                // newNode->next (at +4) currently points to something; store that in this->oldNext (+0xB4)
                this->oldNext = *(int*)(newNode + 4);
                // Set newNode->next = &this->listHead (so it points back to the head pointer)
                *(int**)(newNode + 4) = headPtr;
            }
        }

        // Check flag at +0x120; if zero, perform additional processing
        if (this->field_0x120 == 0) {
            FUN_00820bf0();
        }
    }
    return;
}