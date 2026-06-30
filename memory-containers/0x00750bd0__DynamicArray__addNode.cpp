// FUNC_NAME: DynamicArray::addNode
struct DynamicArray {
    void* data;       // +0x0: pointer to array of nodes (each 0xC bytes)
    int count;        // +0x4: number of used elements
    int capacity;     // +0x8: allocated element count
};

struct Node {
    int value;        // +0x0: some pointer or identifier (e.g., object address)
    int next;         // +0x4: linked list next pointer (singly linked list rooted in the value object)
    int extra;        // +0x8: additional data (from input param2[2])
};

// Insert a new node into the dynamic array and maintain a singly linked list
// rooted at value->+4 (where value is the pointer stored in node.value)
void __thiscall DynamicArray::addNode(DynamicArray* this, Node* inputNode) {
    Node* newElem;
    int newCapacity;

    if (this->count == this->capacity) {
        // Need to grow array
        if (this->capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = this->capacity * 2;
        }
        // FUN_00750050 reallocates the data array to hold newCapacity elements (size 0xC each)
        growArray(newCapacity);  // Placeholder for actual realloc function
    }

    // Calculate pointer to the new element slot (at index old count)
    newElem = (Node*)((int)this->data + this->count * 0xC);
    this->count++;

    if (newElem != 0) {
        int val = inputNode->value;
        newElem->value = val;
        newElem->next = 0;
        if (val != 0) {
            // Insert into singly linked list rooted at val+4
            newElem->next = *(int*)(val + 4);  // Store previous head
            *(int*)(val + 4) = (int)newElem;   // Update head to new element
        }
        newElem->extra = inputNode->extra;
    }
}