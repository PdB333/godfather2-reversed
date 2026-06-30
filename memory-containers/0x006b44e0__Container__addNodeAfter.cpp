// FUNC_NAME: Container::addNodeAfter
void __thiscall Container::addNodeAfter(int* this, int* afterNode) {
    int* newElement;
    int capacity;

    // Check if array needs to grow
    capacity = this[2]; // +0x08: capacity
    if (this[1] == capacity) { // +0x04: size
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Reallocate internal array to new capacity
        ArrayRealloc(capacity);
    }

    // Compute address of new element (each element is 8 bytes: data + next pointer)
    newElement = (int*)(this[0] + this[1] * 8); // +0x00: data pointer, +0x04: size
    this[1]++; // increment size

    if (newElement != (int*)0x0) {
        // Store the pointer to the "after" node as the element's data
        int data = *afterNode;
        *newElement = data; // first 4 bytes: stored value (pointer to a node)
        newElement[1] = 0;  // second 4 bytes: next pointer, initially NULL

        if (data != 0) {
            // Insert new element after the node pointed to by `data`
            // Linked list: each node has a next pointer at offset 4
            newElement[1] = *(int*)(data + 4);       // new->next = data->next
            *(int**)(data + 4) = newElement;         // data->next = new
        }
    }
}