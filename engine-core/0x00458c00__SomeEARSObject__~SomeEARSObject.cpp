// FUNC_NAME: SomeEARSObject::~SomeEARSObject
// Address: 0x00458c00
// Role: Destructor with heap-deletion flag. Called with a byte flag (bit0 = call operator delete after base destructor).
// This pattern is common in EA EARS engine for objects supporting both stack and heap allocation.

void __thiscall SomeEARSObject::~SomeEARSObject(byte deleteFlag)
{
    // Call base class destructor (likely at 0x458c20)
    // In a full reconstruction, this would be: BaseEARSObject::~BaseEARSObject();
    FUN_00458c20();

    // If the object was dynamically allocated (flag bit 0 set), free its memory
    if (deleteFlag & 1)
    {
        // Custom deallocation function (likely operator delete or memory pool free)
        // In the original binary, this is at 0x009c8eb0.
        FUN_009c8eb0(this);
    }
}