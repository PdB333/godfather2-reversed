// FUNC_NAME: SharedPtr::Construct
// Constructor/initializer for a shared pointer class (EARS engine smart pointer).
// Manages a reference-counted object pointed to by param_2.
// Stores the pointer and an optional reference count/cookie at offsets +0x10 and +0x14.

class SharedPtr {
public:
    // Vtable for the managed object (param_2 points to an object with 4 virtual functions at offsets 0,4,8,0xc)
    struct IManagedObject {
        void (__thiscall* queryInterface)(void* self);  // offset 0? (not used)
        void (__thiscall* attachRef)(void* self, int param1, int param2); // offset 4
        void (__thiscall* addRef)(void* self);           // offset 8
        void (__thiscall* release)(void* self);          // offset 0xc
    };

    // Offsets from 'this'
    int* m_pObject;            // +0x10 : pointer to the managed object (param_2)
    int  m_nRefCountOrCookie;  // +0x14 : reference count or cookie (0 if param_3 is 0)

    // External functions (likely within the engine)
    // FUN_004265d0: possibly increments ref count or duplicates handle
    int (*incrementRefOrDuplicate)(int param3, int* objectPtr);
    // FUN_005fa100: sets ref count or associates cookie
    void (*setRefCountOrAttach)(int* objectPtr, int value);

    // Constructor logic
    int __thiscall Construct(int* param_2, int param_3) {
        // param_2 is a pointer to the managed object (has vtable)
        // param_3 is a flag/handle; if non-zero, we attach a reference count

        IManagedObject* obj = reinterpret_cast<IManagedObject*>(*param_2);
        obj->addRef(param_2); // call vtable[2] (addRef) – note: explicit 'this' as param

        int uVar1;
        if (param_3 == 0) {
            uVar1 = 0;
        } else {
            uVar1 = incrementRefOrDuplicate(param_3, param_2);
        }

        setRefCountOrAttach(param_2, uVar1);

        this->m_pObject = param_2;  // +0x10

        // Second addRef? Possibly a no-arg overload or a different function
        // The decompiler shows empty parentheses; likely it's the same addRef with the stored pointer
        // But if it's addRef on the same object, it's a second reference increment.
        // We'll assume it's the same call:
        obj->addRef(this->m_pObject);

        if (param_3 != 0) {
            uVar1 = incrementRefOrDuplicate(param_3, this->m_pObject);
            this->m_nRefCountOrCookie = uVar1; // +0x14

            // vtable[1]: attachRef with param_3 and 0
            obj->attachRef(param_3, 0);

            // vtable[3]: release
            obj->release();
            return reinterpret_cast<int>(this);
        } else {
            this->m_nRefCountOrCookie = 0; // +0x14

            // vtable[3]: release
            obj->release();
            return reinterpret_cast<int>(this);
        }
    }
};