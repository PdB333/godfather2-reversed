// FUNC_NAME: EARS::Framework::RefCountedPointer::RefCountedPointer
// Address: 0x006235f0
// Constructor for a reference-counted smart pointer. pObject must have a vtable with:
//   [0] +0x00: destructor
//   [0] +0x04: setHandle(uint, int)
//   [0] +0x08: AddRef()
//   [0] +0x0C: Release() or Finalize()
// handle is an optional weak reference handle.

int __thiscall EARS::Framework::RefCountedPointer::RefCountedPointer(void* this, void* pObject, uint handle)
{
    typedef void (__thiscall *AddRefFunc)(void*);
    typedef void (__thiscall *SetHandleFunc)(uint, int);
    typedef void (__thiscall *ReleaseFunc)();

    AddRefFunc addRef = (AddRefFunc)(*(int**)pObject)[2];
    SetHandleFunc setHandle = (SetHandleFunc)(*(int**)pObject)[1];
    ReleaseFunc release = (ReleaseFunc)(*(int**)pObject)[3];

    addRef(pObject);  // Acquire strong reference

    int dupHandle;
    if (handle == 0) {
        dupHandle = 0;
    } else {
        dupHandle = FUN_004265d0(handle, pObject);  // Duplicate or add reference to handle
    }

    FUN_00623ea0(pObject, dupHandle);  // Attach object to this wrapper

    *(void**)((int)this + 0x14) = pObject;  // Store object pointer

    addRef(pObject);  // Another AddRef (maybe for internal use)

    if (handle != 0) {
        dupHandle = FUN_004265d0(handle, *(void**)((int)this + 0x14));
        *(uint*)((int)this + 0x18) = dupHandle;  // Store duplicate handle
        setHandle(handle, 0);  // Notify object of handle
        release();  // Finalize
        return (int)this;
    }

    *(uint*)((int)this + 0x18) = 0;
    release();
    return (int)this;
}