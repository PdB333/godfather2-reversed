// FUNC_NAME: SomeObject::Create
undefined4* __fastcall SomeObject::Create(undefined4 parentPtr)
{
    undefined4* newObject;
    undefined4 alignment;
    undefined4 size;
    undefined4 flags;
    
    // Get global memory manager
    MemoryManager* memMgr = GetMemoryManager();
    
    alignment = 2;
    size = 0x10;
    flags = 0;
    
    // Allocate 0x80 bytes from custom allocator
    newObject = (undefined4*)memMgr->alloc(0x80, &alignment, &size, &flags);
    if (newObject != nullptr)
    {
        // Call base class constructor (likely passes parent pointer)
        BaseClass::Construct(parentPtr);
        
        // Initialize vtable and member fields
        newObject[0x18] = &VTable_Temp;   // +0x60 temporary vtable? Overwritten later
        newObject[0x19] = 1;               // +0x64 some counter/flag
        newObject[0x1a] = 0;               // +0x68 some value
        newObject[0x1b] = parentPtr;       // +0x6C store parent/owner reference
        *newObject = &VTable_Main;         // +0x00 main vtable
        newObject[2] = &VTable_Secondary;  // +0x08 secondary vtable
        newObject[0x18] = &VTable_Final;   // +0x60 final vtable (overwrites)
        *(byte*)(newObject + 0x1c) = 0;    // +0x70 byte flag
    }
    return newObject;
}