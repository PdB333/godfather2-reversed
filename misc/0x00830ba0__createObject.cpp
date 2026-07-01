// FUNC_NAME: createObject
// Address: 0x00830ba0
// Description: Allocates and initializes an object of size 0xC0 using a factory singleton.

struct AllocationParams {
    int type;       // +0x00
    int alignment;  // +0x04
    int flags;      // +0x08
};

extern void* getFactoryInstance();    // FUN_009c8f80 - returns factory singleton pointer
extern int initializeAllocatedObject(); // FUN_00830ab0 - initializes the object after allocation

int createObject(void) {
    void* factory = getFactoryInstance();
    AllocationParams params;
    params.type = 2;
    params.alignment = 0x10;
    params.flags = 0;

    // Call first virtual function on factory, likely an allocator
    // Signature: int __thiscall allocate(int size, AllocationParams* params)
    typedef int (__thiscall *AllocateFunc)(void*, int, AllocationParams*);
    AllocateFunc allocFunc = *(AllocateFunc*)(*(int*)factory);
    int result = allocFunc(factory, 0xC0, &params);

    if (result != 0) {
        return initializeAllocatedObject();
    }
    return 0;
}