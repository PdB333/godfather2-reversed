// FUNC_NAME: ActionQueueOwner::processActions
void ActionQueueOwner::processActions()
{
    uint index = 0;
    if (this->actionQueueCount != 0) {
        ActionQueueEntry *entry = this->actionQueue;  // +0xbc
        do {
            void *target = entry->target;             // +0x04 of entry (second int)
            if (target == nullptr) {
                // Use default handler from global manager
                void **managerVtable = *DAT_01205590;  // global manager
                FuncPtr handler = (FuncPtr)(managerVtable[1]);  // offset 0x4 -> index 1
                handler();
            }
            else {
                if (entry->type == 2) {
                    FuncPtr handler = (FuncPtr)(*(void***)target)[5];  // vtable+0x14 -> index 5
                    handler();
                }
                else if (entry->type == 1) {
                    FuncPtr handler = (FuncPtr)(*(void***)target)[6];  // vtable+0x18 -> index 6
                    handler();
                }
            }
            // Clear the entry
            entry->target = nullptr;
            entry->type = 0;
            index++;
            entry++;
        } while (index < this->actionQueueCount);  // +0x9b
    }
    this->actionQueueCount = 0;  // +0x9b
}

// Assumed structures:
// struct ActionQueueEntry {
//     int type;      // +0x00: 1 or 2, identifies which virtual function to call
//     void *target;  // +0x04: pointer to object
// };
// Offset +0x9b: uint8 actionQueueCount (or uint8)
// Offset +0xbc: ActionQueueEntry actionQueue[] (variable length, count from +0x9b)