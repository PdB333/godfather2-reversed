// FUNC_NAME: EARSBaseClass::~EARSBaseClass
struct EARSBaseClassVTable {
    void (*destructor)(void*, bool);
    // ... other virtual functions
};

struct EARSBaseClassNode {
    EARSBaseClassNode* pPrev; // +0x00: previous pointer
    EARSBaseClassNode* pNext; // +0x04: next pointer
};

class EARSBaseClass {
public:
    EARSBaseClassVTable* vtable;        // +0x00
    EARSBaseClassNode* pNodeListHead;   // +0x04: linked list of nodes
    void* pResource;                    // +0x08: some resource pointer

    // Destructor
    void __thiscall ~EARSBaseClass(bool freeMemory) {
        // Clean up the resource at +0x08
        if (pResource != nullptr) {
            sub_004daf90(pResource); // Resource-specific cleanup
        }

        // Reset vtable to a static placeholder (likely to prevent double virtual calls)
        vtable = reinterpret_cast<EARSBaseClassVTable*>(&s_vtablePlaceholder);

        // Clear the linked list: iterate nodes and zero their pointers
        EARSBaseClassNode* pNode = pNodeListHead;
        while (pNode != nullptr) {
            EARSBaseClassNode* pNext = pNode->pNext;
            pNode->pNext = nullptr;
            pNode->pPrev = nullptr;
            pNode = pNext;
        }

        // If requested, free the memory for this object
        if (freeMemory) {
            sub_009c8eb0(this); // custom deallocator (likely operator delete)
        }
    }
};

// Static vtable placeholder (address 0x00e32808)
extern EARSBaseClassVTable s_vtablePlaceholder;

// External helper functions (called by destructor)
void __thiscall sub_004daf90(void* resource);
void __thiscall sub_009c8eb0(void* object);