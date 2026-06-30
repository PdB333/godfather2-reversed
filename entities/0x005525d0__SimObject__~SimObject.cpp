// FUNC_NAME: SimObject::~SimObject
void __thiscall SimObject::~SimObject(SimObject* this)
{
    // Vtable pointers set to intermediate base classes during destruction
    this->vtable1 = &PTR_FUN_00e39fb0;  // +0x00
    *(void**)((char*)this + 0x08) = &PTR_LAB_00e39fc8; // +0x08
    *(void**)((char*)this + 0x0C) = &PTR_LAB_00e39fdc; // +0x0C

    // Clear array of sub-objects at offset +0x08 (first count at +0x80)
    int count1 = *(int*)((char*)this + 0x80);
    if (count1 > 0) {
        void** arrayBase1 = (void**)((char*)this + 0x08);
        for (int i = 0; i < count1; i++) {
            clearSubObject1(arrayBase1);  // FUN_009f2410
        }
    }
    *(int*)((char*)this + 0x80) = 0; // reset count

    // Clear array of sub-objects at offset +0x0C (second count at +0x8C)
    int count2 = *(int*)((char*)this + 0x8C);
    if (count2 > 0) {
        void** arrayBase2 = (void**)((char*)this + 0x0C);
        for (int i = 0; i < count2; i++) {
            clearSubObject2(arrayBase2); // FUN_00a0dec0
        }
    }
    *(int*)((char*)this + 0x8C) = 0; // reset count

    // Check if any event ID in an external list matches 0x1300 (likely a shutdown message)
    SimObjectData** externalData = (SimObjectData**)((char*)this + 0x30);
    int dataCount = *(int*)((char*)(*externalData) + 0x78);
    int** dataArray = (int**)((char*)(*externalData) + 0x74);
    for (int i = 0; i < dataCount; i++) {
        if (*dataArray[i] == 0x1300) {
            sendEvent(dataArray[i], 0x1300); // FUN_009f0250
            break;
        }
    }

    finalizeCleanup(); // FUN_009f01a0

    // Deallocate dynamic buffers using thread-local allocator
    int index1 = *(int*)((char*)this + 0x90);
    if (index1 >= 0) {
        void* allocator = TlsGetValue(DAT_01139810);
        deallocate(allocator, *(void**)((char*)this + 0x88), index1 * 4, 0x17); // FUN_00aa26e0
    }

    int index2 = *(int*)((char*)this + 0x84);
    if (index2 >= 0) {
        void* allocator = TlsGetValue(DAT_01139810);
        deallocate(allocator, *(void**)((char*)this + 0x7C), index2 * 4, 0x17);
    }

    int index3 = *(int*)((char*)this + 0x78);
    if (index3 >= 0) {
        void* allocator = TlsGetValue(DAT_01139810);
        deallocate(allocator, *(void**)((char*)this + 0x70), index3 * 4, 0x17);
    }

    int count4 = *(int*)((char*)this + 0x6C);
    if (count4 >= 0) {
        void* allocator = TlsGetValue(DAT_01139810);
        deallocate(allocator, *(void**)((char*)this + 0x64), (count4 & 0x3FFFFFFF) * 0x30, 0x17);
    }

    // Set vtable pointers to final base class vtables (end of destruction)
    *(void**)((char*)this + 0x0C) = &PTR_LAB_00e39f9c;
    *(void**)((char*)this + 0x08) = &PTR_LAB_00dc3dd4;
    this->vtable1 = &PTR_LAB_00d96914;
}