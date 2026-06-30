// FUNC_NAME: Job::initialize
void Job::initialize() {
    // Read existing members
    int width = *(int *)(this + 0x10);   // +0x10: width or count
    int height = *(int *)(this + 0xc);   // +0x0c: height or size

    // Build a temporary description structure on the stack
    struct Description {
        undefined4 field0_0x0;
        undefined4 field0_0x4;
        undefined4 field0_0x8;
        int field0_0xc;
        undefined1 field0_0x10;
        uint field0_0x14;
        char field0_0x18;
        undefined1 field0_0x19;
        int field0_0x20;
        int field0_0x24;
        undefined4 field0_0x28;
        undefined1 field0_0x2c;
    } desc;

    desc.field0_0x8 = height;
    desc.field0_0xc = width;
    desc.field0_0x20 = width * 8;  // stride or byte count
    desc.field0_0x0 = 0;
    desc.field0_0x4 = 0;
    desc.field0_0x10 = 0;
    desc.field0_0x14 = 0;
    desc.field0_0x18 = '\0';
    desc.field0_0x19 = 0;
    desc.field0_0x2c = 0;
    desc.field0_0x28 = 0;
    desc.field0_0x24 = desc.field0_0x20;

    // Allocate a ref-counted string object (0x18 bytes)
    RefCountedString *newString = (RefCountedString *)operator_new(0x18);
    if (newString != nullptr) {
        newString->refCount = 0;
        newString->length = 0;
        newString->vtable = &PTR_LAB_00e42d64;  // vtable for RefCountedString
        newString->data = nullptr;
        newString->capacity = 0;
        newString->isStatic = 1;
    }

    // Release old string at +0x1c
    RefCountedString *oldString = *(RefCountedString **)(this + 0x1c);
    if (oldString != nullptr) {
        oldString->refCount--;
        if (oldString->refCount == 0) {
            oldString->vtable->destroy(oldString);
        }
    }
    *(RefCountedString **)(this + 0x1c) = newString;
    if (newString != nullptr) {
        newString->refCount++;
    }

    // Initialize the description (likely copies a string or sets up fields)
    FUN_0064bc00(&desc);

    // Allocate a data object (0x24 bytes)
    DataObject *newData = (DataObject *)operator_new(0x24);
    if (newData != nullptr) {
        newData = FUN_00654840(&desc);  // constructor from description
    }

    // Release old data at +0x18
    DataObject *oldData = *(DataObject **)(this + 0x18);
    if (oldData != nullptr) {
        oldData->refCount--;
        if (oldData->refCount == 0) {
            oldData->vtable->destroy(oldData);
        }
    }
    *(DataObject **)(this + 0x18) = newData;
    if (newData != nullptr) {
        newData->refCount++;
    }

    // Allocate another ref-counted string object (0x18 bytes)
    RefCountedString *newString2 = (RefCountedString *)operator_new(0x18);
    if (newString2 != nullptr) {
        newString2->refCount = 0;
        newString2->length = 0;
        newString2->vtable = &PTR_LAB_00e42d64;
        newString2->data = nullptr;
        newString2->capacity = 0;
        newString2->isStatic = 1;
    }

    // Release old string at +0x20
    RefCountedString *oldString2 = *(RefCountedString **)(this + 0x20);
    if (oldString2 != nullptr) {
        oldString2->refCount--;
        if (oldString2->refCount == 0) {
            oldString2->vtable->destroy(oldString2);
        }
    }
    *(RefCountedString **)(this + 0x20) = newString2;
    if (newString2 != nullptr) {
        newString2->refCount++;
    }

    // Align and store count
    uint alignedSize = (desc.field0_0x14 + 7) & 0xfffffff8;
    desc.field0_0x14 = alignedSize;
    *(uint *)(this + 0x28) = alignedSize >> 3;  // +0x28: number of 8-byte units

    // Initialize the description again (maybe finalize)
    FUN_0064bc00(&desc);

    // Set flag if conditions met
    if ((desc.field0_0x18 == '\0') &&
        (*(uint *)(this + 0x10) == (desc.field0_0x14 + 7) >> 3) &&
        (*(char *)(*(int *)(this + 0x18) + 0x20) != '\0')) {
        *(char *)(this + 0x24) = 1;  // +0x24: flag
    }

    // Final cleanup
    FUN_0064b440();
}