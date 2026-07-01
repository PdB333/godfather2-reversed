// FUNC_NAME: AudioEventQueue::~AudioEventQueue

struct AudioEventNode {
    uint32_t data;          // +0x00
    AudioEventNode* next;   // +0x04
};

class AudioEventQueue {
    // Unknown fields at +0x00 and +0x04
public:
    void** vtable;             // +0x08
    AudioEventNode* headNode;  // +0x0C
    void* resourcePointer;    // +0x10
};

void __thiscall AudioEventQueue::~AudioEventQueue(AudioEventQueue* this) {
    // Free the owned resource if present
    if (this->resourcePointer != nullptr) {
        AudioResource::release(this->resourcePointer);
    }
    
    // Set vtable to the post-destruction stub (prevents further virtual calls)
    this->vtable = &PTR_FUN_00e32808;
    
    // Clear the linked list: nullify each node's data and next pointer
    AudioEventNode* currentNode = this->headNode;
    while (currentNode != nullptr) {
        AudioEventNode* nextNode = currentNode->next;
        currentNode->next = nullptr;
        currentNode->data = 0;
        currentNode = nextNode;
    }
}