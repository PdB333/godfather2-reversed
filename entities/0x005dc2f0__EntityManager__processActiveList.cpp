// FUNC_NAME: EntityManager::processActiveList
// Address: 0x005dc2f0
// This appears to be a function that processes a list of active entities (or objects).
// It iterates over a linked list stored in a bucket/collection structure, processes each entry,
// and handles reference counting. The vtable call at the end suggests a polymorphic update step.

typedef void (*VTableFunc)(void*);  // approximate

class EntityManager {
public:
    // Offset 0x08: pointer to a collection structure (likely an array or linked list head)
    void* m_pCollection;

    // Offset 0x10: vtable pointer (first entry at +0: destructor? +4: update function)
    void** m_vtable;

    // Offset 0x14? Unknown, but used as this+8 and this+0x10

    // Internal structure for collection items
    struct CollectionItem {
        int field0;      // +0x00
        int field4;      // +0x04
        int field8;      // +0x08
        int fieldC;      // +0x0C
        CollectionItem* pNext; // +0x10 (offset 4 in int array)
    };

    // Internal collection descriptor
    struct Collection {
        int field0;      // +0x00
        int field4;      // +0x04
        int field8;      // +0x08
        int fieldC;      // +0x0C
        CollectionItem* pHead; // +0x10? Not used directly
        // ...
        int field20;     // +0x20: pointer to something, maybe a secondary list head
        // ...
        CollectionItem** ppListHead; // +0x1c: pointer to the actual head pointer (double indirection)
    };

    // External functions (from other modules)
    void assertListNotEmpty();   // FUN_00b97aea - assertion when list is empty
    void processEntity(void* collection, char buffer[8], Collection* pColl, CollectionItem* pItem); // FUN_005dec30
    void refCountInc();          // FUN_005dcdc0 - increment reference count
    void refCountDec(void* ptr); // FUN_009c8eb0 - decrement reference count (takes node pointer)
    void finalizeUpdate();       // FUN_005de360 - cleanup after processing

    // Main update function
    bool processActiveList() {
        Collection* pCollection = (Collection*)m_pCollection;
        bool result = false; // uVar4

        if (pCollection != NULL) {
            int* pNode = (int*)pCollection->field20; // some head/ID pointer

            // Loop while there are items to process
            while (pNode != NULL) {
                // Get the head item from the linked list stored at offset 0x1c
                CollectionItem* pItem = **(CollectionItem***)(&pCollection->ppListHead);

                // Check if the list is empty (sentinel check: head pointer points to itself)
                if (pItem == (CollectionItem*)pCollection->ppListHead) {
                    assertListNotEmpty();  // should not happen
                }

                // Save the next item before processing (item+0x10 is next pointer)
                CollectionItem* pNext = pItem->pNext;

                // Process this item
                char tempBuffer[8]; // output buffer, possibly unused
                processEntity((void*)(this + 8), tempBuffer, pCollection, pItem);

                // If there is a next item, manage reference counts
                if (pNext != NULL) {
                    refCountInc();           // lock something
                    refCountDec((void*)pNext); // unlock next node?
                }

                // Re-fetch collection pointer (may have changed)
                pCollection = (Collection*)m_pCollection;
                pNode = (int*)pCollection->field20;
            }

            result = true;
        }

        // Finalize update step
        finalizeUpdate();

        // Call virtual function at vtable+4 (e.g., postUpdate)
        VTableFunc postUpdate = (VTableFunc)(*(this->m_vtable + 1));
        postUpdate(this);

        return result;
    }
};