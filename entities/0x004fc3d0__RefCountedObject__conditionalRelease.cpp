// FUNC_NAME: RefCountedObject::conditionalRelease
// Address: 0x004fc3d0
// Purpose: Attempt to conditionally release a ref-counted object based on a virtual predicate.
//          The object structure: [0x00] vtable pointer, [0x04] reference count (int).
//          Virtual functions: vtable+4 (index 1) = release/destructor, vtable+8 (index 2) = canRelease(unknown).

typedef unsigned int uint32;

class RefCountedObject
{
public:
    virtual void release() = 0;          // vtable+0x4
    virtual bool canRelease(uint32 context) = 0; // vtable+0x8

    // +0x04: int refCount;
};

// __fastcall: ECX = param_1 (unused, possibly this from some callers), EDX = param_2 (context), stack = param_3 (object pointer)
// Returns nonzero if canRelease returned true, zero otherwise.
bool __fastcall RefCountedObject_conditionalRelease(int unusedParam1, uint32 context, RefCountedObject* obj)
{
    if (obj != nullptr)
    {
        if (obj->canRelease(context))
        {
            // Successfully approved for release
            int* refCountPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(obj) + 4);
            (*refCountPtr)--;                         // order: decrement first
            if (*refCountPtr == 0)
            {
                obj->release();                       // vtable+4 (index 1)
            }
            return true;                              // return nonzero (stack address of local zero in asm)
        }
        else
        {
            // Not allowed to release now, but still decrement refcount
            int* refCountPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(obj) + 4);
            (*refCountPtr)--;
            if (*refCountPtr == 0)
            {
                obj->release();
            }
            return false;                             // return 0
        }
    }
    return false;
}