// FUNC_NAME: LinkedListElement::destroy
int __thiscall LinkedListElement::destroy(int this, byte shouldDeleteMemory)
{
    // Set vtable pointer at +0x28 to the destruction-time vtable (PTR_LAB_00e317cc)
    // This ensures virtual calls during destruction hit the correct final overrider
    *(int*)(this + 0x28) = (int)&PTR_LAB_00e317cc;

    // Unlink this node from its doubly linked list
    // Field offsets:
    //   +0x18: pointer to previous element (prev)
    //   +0x1c: pointer to next element (next)
    //   +0x20: pointer to associated data (data), possibly a linked object
    int* prev = *(int**)(this + 0x18);
    int* next = *(int**)(this + 0x1c);
    int* data = *(int**)(this + 0x20);

    if (prev != 0) {
        if (next == 0) {
            // No next element: update prev's forward pointer to point to data (??)
            // Offset +4 in prev likely corresponds to 'next' pointer of prev node
            *(int*)(prev + 1) = (int)data; // prev->next = data
        } else {
            // Update next's backward pointer to point to data (??)
            // Offset +8 in next likely corresponds to 'prev' pointer of next node
            *(int*)(next + 2) = (int)data; // next->prev = data
        }
    }

    if (data != 0) {
        // Update data's forward pointer to point to this node's next
        // Offset +4 in data likely corresponds to a 'next' pointer in the data object
        *(int*)(data + 1) = (int)next; // data->next = next
    }

    // Call base destructor (likely of a parent class)
    FUN_0064d150();

    // If the deletion flag is set, free the memory using operator delete
    if ((shouldDeleteMemory & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}