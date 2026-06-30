// FUNC_NAME: EARSBaseObject::destroy (or EARSBaseObject::destructor)
// Address: 0x0051a060 - EA EARS Engine: Base object destructor. Cleans up child list and sibling/parent pointer, then optionally deallocates memory.

class EARSBaseObject {
public:
    // +0x00: vtable pointer (base class vtable)
    void** vtable;
    // +0x04: Head of singly linked list of child objects (each child node: [0] = next, [1] = ??)
    void* m_childListHead;
    // +0x08: Pointer to a single related object (e.g., parent or sibling chain tail)
    void* m_singleLink;

    // Destructor with destroy flag (bit 0 = free memory)
    void __thiscall destroy(unsigned char destroyFlag) {
        // Step 1: Set vtable to base class vtable (for proper virtual dispatch during destruction)
        this->vtable = (void**)0x00e38258; // Base vtable

        // Step 2: Clear the single link pointer (offset +0x08)
        if (this->m_singleLink != nullptr) {
            // Clear the pointed-to object's reference (if any)
            *(void**)this->m_singleLink = nullptr;
            this->m_singleLink = nullptr;
        }

        // Step 3: Set vtable to root class vtable (core object vtable)
        this->vtable = (void**)0x00e32808; // Root vtable

        // Step 4: Walk the child list (offset +0x04) and clear each node's references
        void* currentNode = this->m_childListHead;
        while (currentNode != nullptr) {
            void* nextNode = *(void**)((char*)currentNode + 0x04); // Next pointer is at offset +0x04
            // Clear the node's data and next pointer
            *(void**)currentNode = nullptr;                 // Data pointer at offset +0x00
            *(void**)((char*)currentNode + 0x04) = nullptr; // Next pointer at offset +0x04
            currentNode = nextNode;
        }

        // Step 5: If destroy flag bit 0 is set, deallocate this object
        if ((destroyFlag & 1) != 0) {
            FUN_009c8eb0(this); // Deallocation function (likely operator delete)
        }
    }
};