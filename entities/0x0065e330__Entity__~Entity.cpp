// FUNC_NAME: Entity::~Entity

// Reconstructed destructor for a class that manages a linked list and ref-counted objects.
// Assumed to be a derived class, sets vtable to own class first, then to base class after cleanup.
// Offsets:
// +0x00: vtable pointer
// +0x04: linked list head (single linked list, nodes have vtable, data, next)
// +0x0C: pointer to a dynamically allocated block (freed after helper call)
// +0x18: pointer to first ref-counted object (with ref count at offset 8)
// +0x1C: pointer to second ref-counted object

class Entity {
public:
    // Vtable pointers (external symbols)
    static void** s_ownVTable;  // PTR_LAB_00e43124
    static void** s_baseVTable; // PTR_LAB_00e42de4

    void** m_vtable;       // +0x00
    Node* m_listHead;      // +0x04
    void* m_dynamicBlock;  // +0x0C
    RefCountedObject* m_refObj1; // +0x18
    RefCountedObject* m_refObj2; // +0x1C

    // Node structure for linked list
    struct Node {
        void** vtable; // +0x00
        void* data;    // +0x04
        Node* next;    // +0x08
    };

    // Ref-counted object (vtable at 0, ref count at 8)
    struct RefCountedObject {
        void** vtable; // +0x00
        int refCount;  // +0x08
        // destructor at vtable+8
    };

    void cleanupDynamicBlock();
    ~Entity() {
        // Set vtable to own class (ensure correct virtual dispatch during destruction)
        m_vtable = s_ownVTable;

        // Release dynamically allocated block
        if (m_dynamicBlock != nullptr) {
            cleanupDynamicBlock();
            free(m_dynamicBlock);
        }

        // Release first ref-counted object
        if (m_refObj2 != nullptr) {
            m_refObj2->refCount--;
            if (m_refObj2->refCount == 0) {
                ((void (*)(RefCountedObject*))(*m_refObj2->vtable)[2])(m_refObj2); // call destructor
            }
        }

        // Release second ref-counted object
        if (m_refObj1 != nullptr) {
            m_refObj1->refCount--;
            if (m_refObj1->refCount == 0) {
                ((void (*)(RefCountedObject*))(*m_refObj1->vtable)[2])(m_refObj1);
            }
        }

        // Clear linked list nodes (nodes are not freed, just zeroed)
        m_vtable = s_baseVTable; // Set vtable to base class for subsequent base destructor
        Node* currentNode = m_listHead;
        while (currentNode != nullptr) {
            Node* nextNode = currentNode->next;
            currentNode->vtable = nullptr;
            currentNode->data = nullptr;
            currentNode->next = nullptr;
            currentNode = nextNode;
        }
    }
};

// Note: The actual function ends after setting vtable to base; base destructor is called by the caller chain.