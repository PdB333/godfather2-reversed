// FUNC_NAME: EntryPool::add
void __thiscall EntryPool::add(EntryPool* this, int* entityPtr) {
    int capacity = this->capacity;               // offset +0x08
    if (this->count == capacity) {               // offset +0x04
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Grow the entry buffer (calls realloc/resize)
        FUN_00782b40(capacity);
    }
    // Calculate slot for new entry (8 bytes each: key + next)
    int* newEntry = this->entries + this->count * 2; // offset +0x00
    this->count++;

    if (newEntry != nullptr) {
        int entity = *entityPtr;                 // Entity pointer passed by reference
        *newEntry = entity;                      // Set the key (entity pointer)
        newEntry[1] = 0;                         // Initialize next to 0
        if (entity != 0) {
            // Insert into entity's intrusive linked list (entity->nextEntry at +0x04)
            newEntry[1] = *(int*)(entity + 4);   // Save current head
            *(int**)(entity + 4) = newEntry;     // Set new head to this entry
        }
    }
}