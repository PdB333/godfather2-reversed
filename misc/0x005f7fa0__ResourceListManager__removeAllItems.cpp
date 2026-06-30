// FUNC_NAME: ResourceListManager::removeAllItems
int ResourceListManager::removeAllItems(ContainerEntry* entries, uint* count) {
    if (entries == nullptr) {
        return 0;
    }
    
    uint index = 0;
    ContainerEntry* currentEntry = entries;
    
    if (*count != 0) {
        do {
            // Release resource if present
            if (currentEntry->resource != nullptr) {
                // Virtual call: resource->release(0)
                ((void (*)(void*, int))((*(int**)(currentEntry->resource))[1]))(currentEntry->resource, 0);
                currentEntry->resource = nullptr;
            }
            
            // Unlink this entry from its linked list
            ListHead* head = currentEntry->listHead;
            if (head != nullptr) {
                ContainerEntry* nextEntry = head->first;
                if (nextEntry == currentEntry) {
                    head->first = currentEntry->next;
                } else {
                    ContainerEntry* prev = nextEntry;
                    while (prev->next != currentEntry) {
                        prev = prev->next;
                    }
                    prev->next = currentEntry->next;
                }
            }
            
            index++;
            currentEntry++;
        } while (index < *count);
    }
    
    // Release the container itself
    // Virtual call: this->releaseContainer(entries, 0)
    ((void (*)(void*, void*, int))(*((int**)(this->vtable)) + 1))(this, entries, 0);
    
    return 0;
}