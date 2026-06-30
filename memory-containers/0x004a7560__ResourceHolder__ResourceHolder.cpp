// FUNC_NAME: ResourceHolder::ResourceHolder
ResourceHolder* __thiscall ResourceHolder::ResourceHolder(ResourceHolder* thisObj, int resourceType, void* context)
{
    int hashResult1, hashResult2;
    char* stringPtr;
    bool flag;
    AllocDescriptor desc;
    void* allocatedBlock;
    InnerResource* inner;
    
    // +0x08: context pointer
    // +0x04: resource type identifier (hash?)
    thisObj->context = context;
    thisObj->resourceType = resourceType;   // +0x04
    thisObj->vtable = (void*)&PTR_FUN_00e353e0; // set vtable
    thisObj->innerObject = nullptr;        // +0x0C initially null

    if (resourceType != 0) 
    {
        hashResult1 = FUN_004a3790(0x36e2166c); // lookup global by hash
        hashResult2 = FUN_004a3790(0xd550688c);
        if (hashResult1 != 0) 
        {
            // Try to create a specific resource object via factory
            inner = (InnerResource*)FUN_004a7850(context, hashResult2);
            thisObj->innerObject = inner;
            if (inner != nullptr) 
                return thisObj;
            // failed – allocate a default inner object
            allocatedBlock = FUN_009c8e50(8); // allocate 8 bytes
            if (allocatedBlock == nullptr) 
            {
                thisObj->innerObject = nullptr;
                return thisObj;
            }
            // vtable call on context+8's vtable+4 (get some value)
            hashResult2 = (**(code**)(**(int**)(context+8) + 4))(); 
            inner = (InnerResource*)allocatedBlock;
            inner->vtable = &PTR_LAB_00e354d0;
            inner->someValue = hashResult2; // +0x04
            thisObj->innerObject = inner;
            return thisObj;
        }
        // hashResult1 == 0, alternative path
        hashResult1 = FUN_004a3790(0xd550688c);
        stringPtr = (char*)FUN_004a3790(0x2fd88303);
    }

    // Determine flag: if stringPtr is non-null and first char not null
    flag = false;
    if (stringPtr != nullptr)
        flag = *stringPtr != '\0';

    if (hashResult1 == 0) 
    {
        if (!flag) 
        {
            // No specialized configuration – allocate default inner object
            allocatedBlock = FUN_009c8e50(8);
            if (allocatedBlock == nullptr) 
            {
                thisObj->innerObject = nullptr;
            } 
            else 
            {
                hashResult2 = (**(code**)(**(int**)(context+8) + 4))();
                inner = (InnerResource*)allocatedBlock;
                inner->vtable = &PTR_LAB_00e354d0;
                inner->someValue = hashResult2;
                thisObj->innerObject = inner;
            }
            goto finalize;
        }
        // flag is true – initialize local allocation descriptor array
        // This array describes 4 memory blocks with default alignment
        // Each block is described by 4 dwords (size, alignment, flags, ?)
        // Here we initialize three groups of four entries with a global constant
        // The layout in the stack is as follows (offsets from local base):
        // [0]: local_50 = DAT_00e2b1a4; then zeros
        // [1]: uStack_3c = DAT_00e2b1a4; then zeros
        // [2]: uStack_28 = DAT_00e2b1a4; then zeros
        // [3]: uStack_14 = DAT_00e2b1a4; with zeros around
        // This is a typical initialization of a fixed-size allocation descriptor list.
        {
            // Simulate the stack array as a local struct
            struct AllocBlock {
                int field0; // +0x00
                int field1; // +0x04
                int field2; // +0x08
                int field3; // +0x0C
            };
            AllocBlock blocks[4]; // 64 bytes
            // Initialize each block's first field to the global constant, others zero
            for (int i = 0; i < 4; i++)
            {
                blocks[i].field0 = DAT_00e2b1a4;
                blocks[i].field1 = 0;
                blocks[i].field2 = 0;
                blocks[i].field3 = 0;
            }
            // This part is actually done by the detailed assignments in original
            // but the above loop captures the pattern (the decompilation shows
            // explicit assignments but the effect is same).
        }
    } 
    else 
    {
        // hashResult1 != 0 – initialize the array via setup function
        FUN_004a36a0(&blocks); // likely sets up blocks from some global configuration
    }

    // Use the allocator to allocate 0xA0 bytes with specified flags
    desc.size = 2;    // probably alignment/pool selector
    desc.unk2 = 0x10;
    desc.unk3 = 0;
    allocatedBlock = FUN_009c8f80();
    int iVar4 = (**(code**)*allocatedBlock)(0xA0, &desc); // call alloc function
    if (iVar4 == 0) 
    {
        inner = nullptr;
    } 
    else 
    {
        // vtable call on context+8 to get some value, then construct inner object
        (**(code**)(**(int**)(context+8) + 4))();
        inner = (InnerResource*)FUN_004a7150(iVar4);
    }
    thisObj->innerObject = inner;

finalize:
    // Final initialization of the inner object
    FUN_004a63a0(thisObj->innerObject);
    return thisObj;
}