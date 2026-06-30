// FUNC_NAME: EntityManager::~EntityManager
void __fastcall EntityManager::~EntityManager(EntityManager* this)
{
    // Set vtable to the derived class vtable initially? Actually first set to PTR_FUN_00e407e4
    this->vtable = &PTR_FUN_00e407e4;

    // Call base class destructor (or some cleanup)
    FUN_005f8c90();

    // Delete all entries in the dynamic array of pointers
    int count = this->arraySize; // offset 0x30
    if (count > 0) {
        do {
            count--;
            int* entry = this->arrayPtr[count]; // offset 0x2C is array of pointers
            if (entry != nullptr) {
                // Remove entry from an intrusive linked list where entry is a node
                int* nextNode = *(int**)(entry + 1); // next pointer at +4
                if (nextNode == (int*)&this->selfListNode) { // head is address of member at +0x24
                    // entry is the last node, replace its next with head's next
                    *(int**)(entry + 1) = this->selfListNext;
                } else {
                    // Find previous node
                    int* prevNode = nextNode;
                    int* currentNode = *(int**)(prevNode + 1);
                    while (currentNode != (int*)&this->selfListNode) {
                        prevNode = currentNode;
                        currentNode = *(int**)(prevNode + 1);
                    }
                    prevNode[1] = this->selfListNext;
                }
                // Delete the node itself
                FUN_009c8eb0(entry);
            }
        } while (count > 0);
    }

    // Free the array of pointers
    if (this->arrayPtr != nullptr) {
        FUN_009c8f10(this->arrayPtr);
    }

    // Remove the self-registration node from a global list (if present)
    if (this->selfListNode != 0) {
        int* selfNode = (int*)this->selfListNode;
        int* nextOfSelf = *(int**)(selfNode + 1);
        if (nextOfSelf == (int*)&this->selfListNode) {
            // Self node is the only one in the list; unlink from head
            *(int**)(selfNode + 1) = this->selfListNext;
        } else {
            // Traverse to find previous node
            int* prevNode = nextOfSelf;
            int* currentNode = *(int**)(prevNode + 1);
            while (currentNode != (int*)&this->selfListNode) {
                prevNode = currentNode;
                currentNode = *(int**)(prevNode + 1);
            }
            prevNode[1] = this->selfListNext;
        }
    }

    // Switch vtable to base class (second vtable)
    this->vtable = &PTR_FUN_00e32808;

    // Clear a singly linked list of listeners/children (null-terminated)
    Undefined4* listener = this->listenerList; // offset 0x4
    while (listener != nullptr) {
        Undefined4* next = (Undefined4*)listener[1];
        listener[1] = 0;
        *listener = 0;
        listener = next;
    }
}