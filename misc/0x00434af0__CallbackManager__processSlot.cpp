// FUNC_NAME: CallbackManager::processSlot
void __thiscall CallbackManager::processSlot(int slotIndex) {
    // slotIndex is passed in EAX; this pointer in ECX
    // struct CallbackManager:
    //   +0:  int numSlots
    //   +4:  SlotData* slotArray (array of 0x30-byte entries)
    // struct SlotData (size 0x30):
    //   +0x14: uint** callbackArray  (array of pointers to CallbackNode)
    //   +0x18: int callbackCount
    // struct CallbackNode (size >= 16):
    //   +0:  CallbackNode* nextFree
    //   +4:  void (*function)(void*)
    //   +12: void* userData
    // Global allocator structure (gMemoryAllocator):
    //   +0:  void* blockStart
    //   +4:  uint blockSize
    //   +8:  CallbackNode* freeListHead
    //   +20: uint freeCount
    //   +28: void* allocatorClassPtr (vtable with deallocate at offset 8)

    if (slotIndex < numSlots) {
        SlotData* slot = (SlotData*)(slotArray + slotIndex * 0x30);
        uint** callbackArray = slot->callbackArray;    // +0x14
        int callbackCount = slot->callbackCount;       // +0x18
        bool hasCallbacks = (callbackCount != 0);

        if (hasCallbacks) {
            uint** current = callbackArray;            // start of array
            while (hasCallbacks) {
                CallbackNode* node = (CallbackNode*)*current;
                // Execute callback if function pointer is not null
                if (node->function != 0) {
                    node->function(node->userData);
                }

                // Free the callback node using the global allocator
                CallbackNode* blockStart = (CallbackNode*)gMemoryAllocator.blockStart; // +0
                if (blockStart != 0) {
                    // Check if node belongs to this allocator's block
                    bool inBlock = (blockStart <= node && node < (CallbackNode*)((uint8*)blockStart + gMemoryAllocator.blockSize));
                    if (inBlock) {
                        // Return to free list
                        node->nextFree = gMemoryAllocator.freeListHead; // +8
                        gMemoryAllocator.freeCount++;                   // +20
                        gMemoryAllocator.freeListHead = node;           // +8
                    } else {
                        // Use external deallocation via vtable
                        void* allocatorClass = gMemoryAllocator.allocatorClassPtr; // +28
                        void (**vtable)(void*) = *(void (***)(void*))allocatorClass;
                        vtable[2](node);  // vtable entry at offset 8
                    }
                }

                current++;
                callbackCount--;
                hasCallbacks = (callbackCount != 0);
            }

            // After processing all callbacks, call the cleanup function
            // Pass the address just past the end of the callback array
            processCallbackBuffer((uint8*)callbackArray + callbackSlotCount * 4);
        }
    }
}