// FUNC_NAME: EARSRefCountedObject::releaseReference
// Function address: 0x00500630
// Role: Decrements reference count and conditionally deletes object; returns sentinel pointer indicating alive status.
// This is a helper used by smart pointer implementations.
byte* __fastcall releaseReference(int unusedArg, int checkParam, EARSRefCountedObject* obj)
{
    // Sentinel pointer used as a success token (points to a static zero).
    static byte sentinel = 0;

    if (obj != nullptr)
    {
        // Call virtual function at vtable offset 8 (likely isAlive or isValid) with checkParam.
        typedef char (__thiscall *IsAliveFunc)(EARSRefCountedObject*, int);
        IsAliveFunc isAlive = reinterpret_cast<IsAliveFunc>(obj->vtable[2]); // +8

        if (isAlive(obj, checkParam) != 0)
        {
            // Object is alive, decrement reference count (at offset +4 from vtable pointer).
            // Reference count is stored immediately after vtable pointer: obj[1].
            if (--obj->refCount == 0)
            {
                // Call destructor at vtable offset 4.
                typedef void (__thiscall *DestroyFunc)(EARSRefCountedObject*);
                DestroyFunc destroy = reinterpret_cast<DestroyFunc>(obj->vtable[1]); // +4
                destroy(obj);
            }
            // Return sentinel indicating success and object alive.
            return &sentinel;
        }

        // Object is not alive; still decrement reference and potentially destroy.
        if (--obj->refCount == 0)
        {
            typedef void (__thiscall *DestroyFunc)(EARSRefCountedObject*);
            DestroyFunc destroy = reinterpret_cast<DestroyFunc>(obj->vtable[1]); // +4
            destroy(obj);
        }
    }
    // Return null to indicate failure (object dead or null).
    return nullptr;
}

// Note: The original code likely returns a pointer to a local variable (local_4 = 0) which the compiler
// optimizes to a static address. We use a global sentinel for correctness.
// Exact structure offsets:
// [obj+0x00] = vtable pointer (int*)
// [obj+0x04] = reference count (int)
// vtable[-2] (+8) = isAlive check
// vtable[-3] (+4) = destructor