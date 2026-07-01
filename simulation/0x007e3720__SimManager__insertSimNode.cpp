// FUNC_NAME: SimManager::insertSimNode
struct SimNode {
    int data;           // +0x00
    SimNode* next;      // +0x04
    char flags;         // +0x08
    SimNode* nextList;  // +0x0C  (secondary list)
    SimNode* prev;      // +0x10
};

struct SimNodeList {
    SimNode* head;          // +0x00
    SimNode* tail;          // +0x04
    int count;              // +0x08
    void* defaultPool;      // +0x0C
    void* allocator;        // +0x10  (pointer to IAllocator vtable)
};

void __fastcall SimNodeList::insertSimNode(SimNode* srcNode)
{
    void* pool = this->defaultPool;
    if (pool == nullptr) {
        pool = (void*)0x01218a14;     // global default pool
    }

    SimNode* newNode = (SimNode*)(*reinterpret_cast<void*(__fastcall***)(void*, void*)>(
        this->allocator))[0](0x14, pool);

    if (newNode != nullptr) {
        int data = srcNode->data;
        newNode->data = data;
        newNode->next = nullptr;

        // Insert newNode after an existing node pointed to by source data
        if (data != 0) {
            newNode->next = reinterpret_cast<SimNode*>(data)->next;
            reinterpret_cast<SimNode*>(data)->next = newNode;
        }

        newNode->flags = reinterpret_cast<char*>(srcNode)[8];
        newNode->nextList = nullptr;
        newNode->prev = nullptr;
    }

    // Append newNode to the doubly-linked tail list
    if (this->tail != nullptr) {
        this->tail->nextList = newNode;
        newNode->prev = this->tail;
        this->tail = newNode;
    } else {
        this->head = newNode;
        this->tail = newNode;
    }

    this->count++;
}