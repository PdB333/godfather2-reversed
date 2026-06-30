// FUNC_NAME: ResourceLoader::loadResourceSet
bool __thiscall ResourceLoader::loadResourceSet(ResourceBlockHeader* this)
{
    bool success = true;
    bool result = true;

    // Null check
    if (this == nullptr) {
        return false;
    }

    // Check type field at +0x00
    if (this->type == 0xb) {
        uint idx;
        int currentOffset = 0x14; // Offset to first array after header (size 0x14)

        // Process array1: each element is 0x64 bytes, count at +0x04
        for (idx = 0; idx < this->array1Count; idx++) {
            void* element = (char*)this + currentOffset;
            currentOffset += 0x64;
            if (element == nullptr) {
                success = false;
            } else {
                // Register or validate element, using global manager at g_manager
                if (FUN_005dc510(g_manager, element) == 0) {
                    success = false;
                }
            }
        }

        // Process array2: each element is 0x28 bytes, count at +0x08
        idx = 0;
        while (idx < this->array2Count) {
            void* element = (char*)this + currentOffset;
            currentOffset += 0x28;

            if (element == nullptr) {
                success = false;
            } else {
                // Global container at g_container (DAT_01223514)
                int* container = g_container;
                int* capacityPtr = (int*)(container + 0x254/4); // +0x254: capacity
                int* sizePtr = (int*)(container + 0x250/4);     // +0x250: size
                int* dataPtrPtr = (int*)(container + 0x24c/4); // +0x24c: data pointer

                // Grow container if needed
                if (*sizePtr == *capacityPtr) {
                    int newCapacity = (*capacityPtr == 0) ? 1 : (*capacityPtr * 2);
                    FUN_005f0dc0(newCapacity); // resize
                }

                int currentSize = *sizePtr;
                int* dataPtr = *(int**)dataPtrPtr;
                dataPtr[currentSize] = (int)element;
                *sizePtr = currentSize + 1;
            }
            idx++;
        }

        // Finalize container
        if (FUN_005f0720(g_container) == 0) {
            success = false;
        }

        // Process array3: each element is 0xb0 bytes, count at +0x0C
        for (idx = 0; idx < this->array3Count; idx++) {
            void* element = (char*)this + currentOffset;
            currentOffset += 0xb0;
            if (element == nullptr) {
                success = false;
            } else {
                FUN_004c9690(element); // load/process element
            }
        }

        // Process final single element (if present) at +0x10
        if (this->hasFinalElement != 0) {
            void* element = (char*)this + currentOffset;
            if (element == nullptr || FUN_005de470(g_manager + 0x48, element) == 0) {
                success = false;
            }
        }

        // Call virtual function on global object (DAT_01223510) at vtable offset 0xd0
        (**(code**)(*g_globalObj + 0xd0))();

        return success;
    }

    return result; // returns true if type != 0xb, false if this == nullptr (already handled)
}

// Field layout of ResourceBlockHeader:
// +0x00 int type (0xb for this handler)
// +0x04 int array1Count (0x64-byte elements)
// +0x08 int array2Count (0x28-byte elements)
// +0x0C int array3Count (0xb0-byte elements)
// +0x10 int hasFinalElement (bool)
// +0x14 start of data (array1, then array2, then array3, then optional final element)