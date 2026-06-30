// FUNC_NAME: LinkedListNode::unlink
void __thiscall LinkedListNode::unlink(void* arg) {
    // Pointer 'this' is in ECX; not explicitly in decompiled but used as 'in_EAX'
    // Global flag indicating if the list system is active
    extern bool g_isListSystemActive; // DAT_01205358

    if (this != nullptr && g_isListSystemActive) {
        // +0x0c: pointer to previous node in doubly linked list
        // +0x10: pointer to next node
        // Unlink from the list
        if (*(void**)((uint8_t*)this + 0x0c) != nullptr) {
            // The previous node's next becomes this node's next
            *(void**)(*(int*)((uint8_t*)this + 0x0c) + 0x10) = *(void**)((uint8_t*)this + 0x10);
        }
        if (*(int*)((uint8_t*)this + 0x10) != 0) {
            // The next node's previous becomes this node's previous
            *(void**)(*(int*)((uint8_t*)this + 0x10) + 0x0c) = *(void**)((uint8_t*)this + 0x0c);
        }

        // +0x18: index into per-thread data used for tracking or allocation
        int index = *(int*)((uint8_t*)this + 0x18);

        // Clear node's links
        *(void**)((uint8_t*)this + 0x10) = nullptr;
        *(void**)((uint8_t*)this + 0x0c) = nullptr;

        // Thread-local storage: FS:0x2c typically points to TLS data block
        // In this build, it's used to get a per-thread structure
        int* pTlsBase = *(int**)(__readfsdword(0x2c));
        // The structure at pTlsBase[2] (+8) has a flag array at offset 0x7c + index
        uint8_t* flagArray = (uint8_t*)(*(int*)(pTlsBase + 2) + 0x7c);
        if ((*(uint32_t*)(flagArray + index) & 0x4000) != 0) {
            // If the specific flag is set, perform additional cleanup
            void* container = FUN_00432cd0(arg, this);
            if (container != nullptr) {
                FUN_004186d0(container);
            }
        }
    }
}