// FUNC_NAME: allocateAndConstruct

struct AllocDescriptor {
    int someFlag;           // +0x00: Allocation flag (value 2)
    int alignmentOrSize;    // +0x04: Alignment or sub-size (value 0x10)
    int parentOrFlags;      // +0x08: Parent pointer or additional flags (value 0)
};

int allocateAndConstruct(int objectOwner, int creationParam) {
    AllocDescriptor desc;
    desc.someFlag = 2;
    desc.alignmentOrSize = 0x10;
    desc.parentOrFlags = 0;

    int allocatedMem = FUN_0043b980(0xb0, &desc, creationParam);
    if (allocatedMem != 0) {
        int initResult = FUN_0078e5e0(objectOwner);
        return initResult;
    }
    return 0;
}