// FUNC_NAME: NodeListContainer::pushEntry

// Represents a container that stores fixed-size nodes (8 bytes each) in a dynamic array.
// Each node holds a pointer to an object and a next pointer for intrusive list linking.
// The container grows by doubling when full.
// The function inserts a new node at the end of the array and links it into the
// intrusive list of the object referenced by the source entry.
class NodeListContainer
{
public:
    // Each node: [object pointer, next pointer]
    struct Node
    {
        void* object; // +0x00
        Node* next;   // +0x04
    };

    Node* data;     // +0x00 base of dynamically allocated node array
    int   count;    // +0x04 number of nodes currently stored
    int   capacity; // +0x08 capacity of the array

    // param_1 = this
    // param_2 = pointer to a structure whose first field is the object pointer
    void __thiscall pushEntry(const int* source)
    {
        int newCapacity;
        Node* newNode;

        // Expand array if full
        if (count == capacity)
        {
            if (capacity == 0)
                newCapacity = 1;
            else
                newCapacity = capacity * 2;
            growToCapacity(newCapacity); // FUN_0074c900
        }

        // Point to the next free slot (index count) and increment count
        newNode = (Node*)((int)data + count * 8); // offset = count * 8 bytes
        count++;

        // Initialize the node
        newNode->object = (void*)*source; // copy object pointer from source
        newNode->next   = nullptr;        // default next = null

        // If object is not null, link this node into its intrusive list
        if (newNode->object != nullptr)
        {
            // The object has a 'next' pointer at offset +0x04
            // Save current head of that object's list
            newNode->next = (Node*)(*(int*)((int)newNode->object + 4));
            // Update object's list head to point to this node
            *(int**)((int)newNode->object + 4) = (int*)newNode;
        }
    }

private:
    // Expands the node array to at least newCapacity
    void __thiscall growToCapacity(int newCapacity); // FUN_0074c900
};