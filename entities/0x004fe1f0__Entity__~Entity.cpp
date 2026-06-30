// FUNC_NAME: Entity::~Entity
void __thiscall Entity::~Entity(Entity *this) {
    // Offset 0x00: vtable pointer (set to base destructor vtable initially)
    // Offset 0x24 (+0x24): next pointer in global linked list
    // Offset 0x34 (+0x34): child array (array of Attachment, size 0x90 each)
    // Offset 0x3c (+0x3c): child count
    // Offset 0x50 (+0x50): flag for deferred deletion (1 byte)
    // Offset 0x10 (+0x10): additional allocated memory block pointer
    // Offset 0x14 (+0x14): size of that memory block

    Entity *iterator;
    int childIndex;
    int *listPrev;
    int listHead;
    int *attachmentArray;
    int attachmentCount;
    int i;
    int *attachmentPtr;

    // Step 1: Detach any attachments that reference this Entity
    for (iterator = gEntityListHead; iterator != 0; iterator = *(Entity **)((int)iterator + 0x24)) {
        attachmentArray = *(int **)((int)iterator + 0x34);
        attachmentCount = *(int *)((int)iterator + 0x3c);
        if (attachmentArray != 0 && 0 < attachmentCount) {
            i = 0;
            attachmentPtr = attachmentArray;
            do {
                // Check attachment flags and parent pointer
                if ( (*(byte *)(attachmentPtr + 0x78) & 1) == 0 ) {
                    Entity **parentPtr = *(Entity ***)(attachmentPtr + 0x7c);
                    if (parentPtr != 0 && parentPtr == this) {
                        // Copy world matrix from some engine data (thread-local transform pool)
                        // The address is computed from FS segment + 0x2c + 8 + parentPtr[4] * 0x10?
                        // Actually the original code reads a matrix from a pool per thread
                        float *transformSrc = (float *)( ( *(int *)( (*(int *)( *(int *)(__readfsdword(0x2c) + 0x2c) + 8) ) ) ) + 0x80 + parentPtr[4] * 4 );
                        float x = transformSrc[0];
                        float y = transformSrc[1];
                        float z = transformSrc[2];
                        float w = transformSrc[3];
                        float *transformDst = (float *)(attachmentPtr + 0x50);
                        transformDst[0] = x;
                        transformDst[1] = y;
                        transformDst[2] = z;
                        transformDst[3] = w;
                        // Clear parent pointer
                        *(Entity ***)(attachmentPtr + 0x7c) = 0;
                    }
                }
                i++;
                attachmentPtr += 0x90; // each attachment is 0x90 bytes
            } while (i < attachmentCount);
        }
    }

    // Step 2: Remove this Entity from the global linked list
    listHead = gEntityListHead;
    listPrev = &gEntityListHead;
    while (true) {
        if (listHead == 0) {
            goto skipUnlink;
        }
        Entity *current = *(Entity **)listPrev;
        if (current == this) {
            *listPrev = *(Entity **)((int)current + 0x24);
            goto skipUnlink;
        }
        listHead = *(int *)((int)current + 0x24);
        listPrev = (int *)current + 9; // next field offset 0x24
    }

skipUnlink:
    // Step 3: Destroy child objects (array at offset 0x34)
    if (this->m_childArray != 0) {
        childIndex = 0;
        if (0 < this->m_childCount) {
            int stride = 0; // actually iVar8
            do {
                helperReleaseChild(); // calls FUN_004fd2c0
                // Release each child element's extra pointer at offset 0x60
                void *childExtra = *(void **)((int)this->m_childArray + 0x60 + stride);
                if (childExtra != 0) {
                    (*(void (__thiscall **)(void *, int))(*(int *)childExtra + 4))(childExtra, 0);
                }
                childIndex++;
                stride += 0x90;
            } while (childIndex < this->m_childCount);
        }
        // Release the array itself
        if (this->m_childArray != 0) {
            (*(void (__thiscall **)(int *, int))(*(int *)this->m_childArray + 4))(this->m_childArray, 0);
        }
    }

    // Step 4: Queue for deferred deletion if flag is set
    if ( *(char *)((int)this + 0x50) != 0 ) {
        // Write to a global byte buffer for later processing
        int *bufferPtr = (int *)(gDeferredDeleteBuffer + 0x14);
        **(int **)(gDeferredDeleteBuffer + 0x14) = (int *)&PTR_LAB_01124eb8; // tag
        *bufferPtr = *bufferPtr + 4;
        *(int *)*bufferPtr = (int)this;
        *bufferPtr = *bufferPtr + 4;
    }

    // Step 5: Change vtable to next base destructor
    this->vtable = &PTR_FUN_00e37110; // next base class vtable

    // Step 6: Release additional allocated memory if present
    if (this->m_extraMem != 0) {
        // Similar deferred deletion for the memory block
        int *bufferPtr = (int *)(gDeferredDeleteBuffer + 0x14);
        **(int **)(gDeferredDeleteBuffer + 0x14) = (int *)&PTR_LAB_01123be8; // tag for memory block
        *bufferPtr = *bufferPtr + 4;
        *(int *)*bufferPtr = this->m_extraMem;
        *bufferPtr = *bufferPtr + 4;
        this->m_extraMem = 0;
        this->m_extraMemSize = 0;
    }
}