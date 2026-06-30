// FUNC_NAME: SomeClass::~SomeClass

// Function at 0x006a1700 - Destructor for SomeClass (complete object destructor with scalar delete)
// Sets vtable to base class, releases owned resources, optionally deletes memory

void* __thiscall SomeClass::~SomeClass(SomeClass* this, byte deleteFlag)
{
    // Set vtable to base class (to ensure correct virtual dispatch during destruction)
    *(void***)this = (void**)&PTR_LAB_00d5d090;

    // Global deinitialization: reset some global count
    DAT_01129bb8 = 0;

    // Perform any static cleanup
    FUN_00498180();

    // Release resource at offset 0x18 (e.g., a child object or buffer)
    FUN_009c8f10(*(int*)((char*)this + 0x18));

    // Check if there is a nested sub-object pointer at offset 0x04
    int* subObject = *(int**)this; // Wait, careful: param_1[1] is at offset 0x04 from 'this'
    // Correctly: int* subObject = *(int**)((char*)this + 4);
    int* subObject = *(int**)((char*)this + 4);
    if (subObject != 0)
    {
        // Release a member of the sub-object at offset 0x30
        FUN_009c8f10(*(int*)((char*)subObject + 0x30));
        // Then free the sub-object itself
        FUN_009c8eb0(subObject);
    }

    // If the delete flag is set (bit 0), free the 'this' object itself
    if ((deleteFlag & 1) != 0)
    {
        FUN_009c8eb0(this);
    }

    return this;
}