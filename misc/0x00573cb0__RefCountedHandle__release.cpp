// FUNC_NAME: RefCountedHandle::release
// Address: 0x00573cb0
// Decrements reference count, releases managed object if count reaches zero.
class RefCountedHandle {
public:
    // Vtable layout:
    // +0: virtual void release() = 0; (vfunc1)
    // +4: virtual void destroy(int free) = 0; (vfunc2)
    // +8: maybe more
    // +12: virtual ~RefCountedHandle() = 0; (destructor)

    // Offsets in this class:
    // +0x00: int* m_pManagedObject;   // pointer to managed object
    // +0x04: int m_refCount;          // reference count
    // +0x08: int* m_pSomething;       // another managed pointer (e.g., sub-handle)
    // +0x0C: void** m_vtable;         // vtable pointer

    // Release the managed object and decrement reference count.
    void release() {
        int* managedObj = m_pManagedObject;
        if (managedObj != nullptr) {
            // Release sub-objects within the managed object.
            // At offsets +0x08 and +0x0C in the managed object are pointers to sub-objects.
            int* subObj1 = *(int**)(managedObj + 2); // +0x08
            int* subObj2 = *(int**)(managedObj + 3); // +0x0C
            if (subObj1 != nullptr) {
                FUN_00573f70(subObj1); // call release on sub-object
            }
            if (subObj2 != nullptr) {
                FUN_00573f70(subObj2);
            }

            // Call destroy on the managed object with flag 0 (don't free memory?).
            // The vtable of managedObj is at *managedObj.
            void (**vtableManaged)(int*, int) = *(void (***)(int*, int))managedObj;
            vtableManaged[1](managedObj, 0); // vfunc2 (destroy)

            // Decrement reference count.
            m_refCount--;
        }
        m_pManagedObject = nullptr;

        // If there is another managed pointer, release it as well.
        if (m_pSomething != nullptr) {
            // Call destroy on it with flag 0.
            void (**vtableSomething)(int*, int) = *(void (***)(int*, int))m_pSomething;
            vtableSomething[1](m_pSomething, 0);
        }

        // If reference count reaches zero, call this handle's destructor.
        // Ghidra warning: Could not recover jumptable at 0x00573d09.
        // The actual check is missing in decompilation, but logic implies:
        if (m_refCount == 0) {
            this->~RefCountedHandle(); // vtable[3] - destructor
        }
    }
};