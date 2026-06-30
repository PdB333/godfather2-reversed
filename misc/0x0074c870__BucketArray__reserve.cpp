// FUNC_NAME: BucketArray::reserve
class BucketArray {
public:
    struct Node {
        int objectPtr;  // +0x00: pointer to object (may be intrusive linked list head)
        int next;       // +0x04: next pointer (linking objects together)
    };

    // Layout: this+0: Node* data; this+4: int size (number of active buckets); this+8: int capacity (total allocated buckets)
    Node* data;       // offset +0x00
    int size;         // offset +0x04
    int capacity;     // offset +0x08

    void __thiscall reserve(uint newCapacity);
};

// Allocate memory (wraps malloc)
void* __fastcall allocMemory(size_t size);

// Free memory (wraps free)
void __fastcall freeMemory(void* ptr);

// Destroy a node (likely destructor or deallocation of per-bucket resources)
void __fastcall destroyNode(BucketArray::Node* node);

void __thiscall BucketArray::reserve(uint newCapacity) {
    if (this->capacity >= newCapacity) {
        return;
    }

    Node* newData = (Node*)allocMemory(newCapacity * sizeof(Node)); // allocate new bucket array
    if (this->data != nullptr) {
        for (uint i = 0; i < this->size; i++) {
            Node* oldNode = &this->data[i];
            Node* newNode = &newData[i];

            // Copy the object pointer into the new node
            newNode->objectPtr = oldNode->objectPtr;
            newNode->next = 0;

            // If the old bucket held an object, relink the intrusive list
            if (oldNode->objectPtr != 0) {
                // Read the old object's next pointer (at offset 0x04 in the object)
                newNode->next = *(int*)(oldNode->objectPtr + 4);
                // Update the object's next pointer to point to the new node (new head of list)
                *(int**)(oldNode->objectPtr + 4) = newNode;
            }

            // Destroy the old bucket node (frees per-bucket resources if any)
            if (oldNode->objectPtr != 0) {
                destroyNode(oldNode);
            }
        }

        // Free the old bucket array
        freeMemory(this->data);
    }

    this->data = newData;
    this->capacity = newCapacity;
}