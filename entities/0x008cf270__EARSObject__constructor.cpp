// FUNC_NAME: EARSObject::constructor
undefined4* __thiscall EARSObject::constructor(undefined4* this, byte flags)
{
    // Set vtable pointer to class-specific vtable
    *this = &PTR_FUN_00d7ccb0;
    
    // Call base class constructor (likely EARSObjectBase or similar)
    BaseClass::constructor(this);
    
    // If the low bit of flags is set, allocate additional memory and initialize
    if ((flags & 1) != 0) {
        // Allocate memory (likely operator new or custom allocator)
        int* allocation = (int*)MemoryManager::allocate();
        
        // Call virtual function at offset 4 on the allocated object
        // This is typically a placement constructor or initializer
        // passing 'this' and a size (0x80 = 128 bytes)
        (**(code**)(*allocation + 4))(this, 0x80);
    }
    
    return this;
}