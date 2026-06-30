// FUNC_NAME: RefCountedObject::constructor
class RefCountedObject {
public:
    // +0x10: pointer to reference-counted object (vtable at offset 0)
    void* m_pObject;
    // +0x14: handle or copy of param_3 (0 if null)
    int m_handle;

    // Constructor: initializes with a reference-counted object and optional handle
    // param_2: pointer to object with vtable (AddRef at +8, Release at +4, etc.)
    // param_3: optional data to duplicate (0 if none)
    RefCountedObject(void* pObject, int param_3) {
        // Increment reference count on pObject
        (*(void (**)(void*))(*(int*)pObject + 8))(pObject);

        int handle = 0;
        if (param_3 != 0) {
            // Duplicate param_3 using the object's method (likely a copy/clone function)
            handle = FUN_004265d0(param_3, pObject);
        }

        // Initialize internal state (likely sets up the handle)
        FUN_005f9e00(pObject, handle);

        // Store the object pointer
        m_pObject = pObject;

        // Increment reference count again (second AddRef)
        (*(void (**)(void))(*(int*)pObject + 8))();

        if (param_3 != 0) {
            // Duplicate again and store handle
            handle = FUN_004265d0(param_3, m_pObject);
            m_handle = handle;

            // Release the original param_3 (decrement ref count)
            (*(void (**)(int, int))(*(int*)pObject + 4))(param_3, 0);

            // Final release (decrement ref count)
            (*(void (**)(void))(*(int*)pObject + 0xc))();
        } else {
            m_handle = 0;
            // Final release
            (*(void (**)(void))(*(int*)pObject + 0xc))();
        }
    }
};