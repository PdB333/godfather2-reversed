// FUNC_NAME: SomeManager::initFromDataTable
void __fastcall SomeManager::initFromDataTable(void* this) {
    // this +0x2c points to a data table structure
    // data table +0x2c = count of elements
    // data table +0x30 = array of source elements (each 0xc bytes)
    int count = *(int*)(*(int*)((char*)this + 0x2c) + 0x2c);

    // Allocation info (size, alignment, etc.)
    struct AllocInfo {
        int field0;
        int field4;
        int field8;
    } allocInfo = {0, 0, 0};

    // Function pointer at this+0x28 is an allocator
    typedef void* (__fastcall *AllocFunc)(int size, AllocInfo* info);
    AllocFunc allocFunc = *(AllocFunc*)(*(int*)((char*)this + 0x28));
    void* allocatedArray = allocFunc(count * 8, &allocInfo);
    *(int*)((char*)this + 0x40) = (int)allocatedArray;

    if (count != 0) {
        int srcOffset = 0; // offset into source array (increments by 0xc)
        for (unsigned int i = 0; i < count; i++) {
            // Destination element at allocatedArray + i*8
            struct DestElement {
                int field0;
                short field4;
                short field6;
            };
            DestElement* destElem = (DestElement*)((int)allocatedArray + i * 8);
            DestElement* elemPtr = nullptr;

            if (destElem != nullptr) {
                destElem->field0 = 0;
                destElem->field4 = 0;
                destElem->field6 = 0;
                elemPtr = destElem;
            }

            // Source element from data table array (each 0xc bytes)
            int* srcArray = (int*)(*(int*)(*(int*)((char*)this + 0x2c) + 0x30));
            int srcValue = *(int*)((char*)srcArray + srcOffset);

            // Initialize destination element from source value
            FUN_00408240(elemPtr, srcValue);

            if (elemPtr->field0 != 0) {
                FUN_00408900(this, elemPtr, 0x8000);
            }

            srcOffset += 0xc;
        }
    }
}