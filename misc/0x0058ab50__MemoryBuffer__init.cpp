// FUNC_NAME: MemoryBuffer::init
void __thiscall MemoryBuffer::init(void)
{
    int *pResourceMgr; // DAT_0120556c - global resource manager pointer
    undefined4 allocResult; // return from resource manager call
    undefined4 *tempPtr; // temporary pointer for default resource

    // Initialize local variables to zero (likely an ID or handle)
    undefined4 local_c = 0;
    undefined4 local_8 = 0;
    undefined4 local_4 = 0;

    pResourceMgr = DAT_0120556c; // +0x10 in this object will store this

    this->field_0x04 = 0;                // +0x04 - state/type
    this->field_0x08 = 0x100;            // +0x08 - buffer size (256)

    // Get an allocator or stream handle from the resource manager
    allocResult = FUN_004265d0(&local_c, pResourceMgr);
    this->field_0x0C = allocResult;      // +0x0C - handle/allocator

    this->field_0x10 = pResourceMgr;     // +0x10 - save resource manager pointer

    // Call virtual function at offset 8 of the resource manager's vtable
    // (probably release() or lock())
    (**(code **)(*pResourceMgr + 8))();

    // Determine the allocator to use: if allocResult is null, use a default
    tempPtr = (undefined4 *)this->field_0x0C;
    if (tempPtr == (undefined4 *)0x0) {
        tempPtr = &DAT_01218a14; // global default allocator/resource
    }

    // Call virtual function of the resource manager (vtable[0]) to allocate memory
    // Parameters: size 0x400 (1024 bytes), and allocator/resource tag
    this->field_0x00 = (*(code *)**(undefined4 **)this->field_0x10)(0x400, tempPtr); // +0x00 - buffer pointer

    return;
}