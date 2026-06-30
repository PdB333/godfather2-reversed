// FUNC_NAME: refCountedConditionalRelease
// Function at 0x004feb20: Performs a conditional check on a reference-counted object and releases one reference.
// __fastcall: ecx = unused (maybe this pointer in original), edx = test argument, stack = pointer to intrusive ref-counted object
// The object layout: +0x00 vtable pointer, +0x04 ref count (int), vtable[1] = release/destructor (offset 4), vtable[2] = check method (offset 8)
// Returns a non-null dummy pointer if check succeeds and object was valid, otherwise null.
// Always decrements ref count; if it reaches zero, calls the destructor via vtable[1].

typedef bool (__thiscall *CheckFunc)(void* obj, int arg);       // offset 8
typedef void (__thiscall *ReleaseFunc)(void* obj);              // offset 4

void* __fastcall refCountedConditionalRelease( int unused_ecx, int testArg, void* refCountedObj )
{
    int* piVar1;
    bool checkResult;

    // Local sentinel used as success indicator
    int sentinel = 0;

    if ( refCountedObj != nullptr )
    {
        // Call virtual check method at vtable offset 8
        checkResult = ((CheckFunc)**(int**)refCountedObj + 2)( refCountedObj, testArg ); // +2 in pointer increments
        // Equivalent: checkResult = (*(code**)(*(int*)refCountedObj + 8))(refCountedObj, testArg);

        // Decrement reference count (offset 4)
        piVar1 = (int*)refCountedObj + 1; // ref count at +0x04
        *piVar1 = *piVar1 - 1;
        if ( *piVar1 == 0 )
        {
            // Call release/destructor at vtable offset 4
            ((ReleaseFunc)**(int**)refCountedObj + 1)( refCountedObj ); // +1 in pointer increments
        }

        if ( checkResult )
        {
            // Return non-null dummy pointer as success indicator
            return &sentinel;
        }
    }
    return nullptr;
}