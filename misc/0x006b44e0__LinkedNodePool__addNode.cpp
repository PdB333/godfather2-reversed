// FUNC_NAME: LinkedNodePool::addNode
// Address: 0x006b44e0

class LinkedNodePool {
public:
    int* data;      // +0x00: pointer to array of Node structures (each 8 bytes: int value, int next)
    int size;       // +0x04: current number of nodes
    int capacity;   // +0x08: allocated capacity (in nodes)

    // Adds a new node to the pool, storing *valuePtr and linking it into the doubly‑linked chain
    // headed at the object pointed to by *valuePtr (which must have a 'next' field at offset +4)
    void addNode(int* valuePtr);
};

// Reallocation helper (likely a member of the same class or a global grow function)
// Defined elsewhere; takes new capacity and updates data and capacity.
void resizePool(int newCapacity);

void LinkedNodePool::addNode(int* valuePtr) {
    int val = *valuePtr;
    Node* newNode;

    // Grow the array if necessary (double capacity, or start at 1 if empty)
    if (this->size == this->capacity) {
        int newCap = (this->capacity == 0) ? 1 : (this->capacity * 2);
        resizePool(newCap);
    }

    // Point to the next free slot in the array (each Node is 8 bytes)
    newNode = reinterpret_cast<Node*>(this->data + this->size * 2);
    this->size++;

    // Initialize the node
    newNode->value = val;
    newNode->next = nullptr;

    // If the value is non‑null, it is a pointer to an object that holds a linked list of nodes.
    // Insert this node as the new head of that list.
    if (val != 0) {
        // Save the object's current head pointer (at offset +4) as our next
        newNode->next = *reinterpret_cast<int**>(val + 4);
        // Set the object's head to point to the new node
        *reinterpret_cast<int**>(val + 4) = newNode;
    }
}