// FUNC_NAME: ListProcessor::processNextItem
// Address: 0x00621450
// Role: Iterates over a linked list or array, processing each item if a condition is met, and advances the iterator.

class ListProcessor {
public:
    // +0x04: Pointer to a handler object (vtable pointer at offset 0 of that object)
    void* m_pHandler;  
    // +0x10: Pointer to the list container (e.g., a linked list or array)
    void* m_pList;      

    // Virtual function table index 1 of the handler: called with a 32-bit value and 0
    // This is used to process an item
    void callHandlerFunc(uint32_t param);
};

// External functions used
void FUN_00621b20(void* outPtr);        // Initialize iteration (outputs list pointer and node pointer)
void FUN_00b97aea();                     // Error/assert function
void FUN_006217f0(void* list, void* iter, void* listCopy, void* node); // Advance iterator

bool __thiscall ListProcessor::processNextItem() {
    bool hasNext = false;

    if (m_pList != nullptr) {
        // Begin iteration: get the list container and first node
        void* listPtr;   // local_20
        void* nodePtr;   // local_1c
        FUN_00621b20(&nodePtr);  // Actually initializes both listPtr and nodePtr via output

        if (listPtr == nullptr) {
            FUN_00b97aea(); // Error
        }

        if (nodePtr == *(void**)((uint8_t*)listPtr + 0x1c)) {
            FUN_00b97aea(); // Error: reached end already?
        }

        // Read fields from the node (offsets 0x0c, 0x14, 0x1c)
        uint64_t field0C = *(uint64_t*)((uint8_t*)nodePtr + 0x0C);
        uint64_t field14 = *(uint64_t*)((uint8_t*)nodePtr + 0x14);
        uint64_t field1C = *(uint64_t*)((uint8_t*)nodePtr + 0x1C);

        // Check if a specific flag is set (high 16 bits of field1C high dword == 1)
        uint16_t flag = (uint16_t)(field1C >> 32);
        if (flag == 1) {
            // Extract high 32 bits of field0C as argument
            uint32_t arg = (uint32_t)(field0C >> 32);
            // Call virtual function at index 1 of m_pHandler's vtable
            callHandlerFunc(arg);
        }

        // Get the end iterator from the list
        void* endPtr = *(void**)((uint8_t*)m_pList + 0x1C);

        // Check if the list pointer matches
        if (listPtr != m_pList) {
            FUN_00b97aea(); // Error: list inconsistency
        }

        hasNext = (nodePtr != endPtr);
        if (hasNext) {
            // Advance to next node
            FUN_006217f0(m_pList, &listPtr, listPtr, nodePtr);
        }
    }
    return hasNext;
}