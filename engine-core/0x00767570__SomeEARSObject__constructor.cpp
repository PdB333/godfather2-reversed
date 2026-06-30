// FUNC_NAME: SomeEARSObject::constructor
void __fastcall SomeEARSObject::constructor(void* thisPtr)
{
    // Set base class vtable (first vtable pointer)
    *((int**)thisPtr) = &PTR_LAB_00d6599c;
    
    // Access member at offset +0x5C (param_1[0x17]), which is a pointer to another object
    // Write a global value (DAT_01205228) to offset +0x220c within that object
    *((int*)(*((int*)((char*)thisPtr + 0x5C)) + 0x220C)) = DAT_01205228;
    
    // Set derived class vtable (override with actual class vtable)
    *((int**)thisPtr) = &PTR_LAB_00d63090;
    
    // Check if sub-object at offset +0x68 (param_1[0x1a]) exists
    if (*((int*)((char*)thisPtr + 0x68)) != 0)
    {
        // Call destructor/cleanup on that sub-object (address of the member itself is passed)
        FUN_004daf90((int*)((char*)thisPtr + 0x68));
    }
    
    // Call global initialization function (likely static init or engine setup)
    FUN_0080ea60();
    
    return;
}