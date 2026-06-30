// FUNC_NAME: SimActionManager::processActionBuckets
void SimActionManager::processActionBuckets()
{
    SimActionManager* current = this;
    while (current != nullptr) {
        // Process 8-byte action entries (type + pointer)
        int actionCount = current->m_actionCount;          // +0x1c
        ActionEntry* actions = current->m_actions;         // +0x0c
        while (actionCount > 0) {
            actionCount--;
            ActionEntry* entry = &actions[actionCount];    // 8-byte stride
            int type = entry->type;
            void* object = entry->object;
            if (type == ACTION_TYPE_ACTIVE) {               // type == 4
                // Mark object as active (set bit 0 at offset +5)
                unsigned char* flags = (unsigned char*)object + 5;
                *flags |= 1;
                type = entry->type; // re-read? actually the code rereads after setting but before the check below, so it's fine
            }
            if (type > 3 && ((*(unsigned char*)object + 5) & 1) == 0) {
                entry->type = 0; // clear entry
            }
        }

        // Process 20-byte extended action entries (id, ???, type, pointer, ???)
        int arraySize = 1 << (current->m_log2Size & 0x1f);  // +0x07 byte
        if (arraySize > 0) {
            ExtendedAction* extendedActions = current->m_extendedActions; // +0x10
            for (int i = arraySize - 1; i >= 0; i--) {
                ExtendedAction* ext = &extendedActions[i];
                int type = ext->type;
                void* object = ext->object;
                if (type == ACTION_TYPE_ACTIVE) {
                    unsigned char* flags = (unsigned char*)object + 5;
                    *flags |= 1;
                    type = ext->type;
                }
                if (type > 3 && ((*(unsigned char*)object + 5) & 1) == 0) {
                    ext->type = 0; // clear type
                    if (ext->id > 3) {
                        ext->id = -1; // invalidate ID
                    }
                }
            }
        }
        current = current->m_nextBucket; // +0x18
    }
}