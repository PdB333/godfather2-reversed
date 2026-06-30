// FUNC_NAME: HandleBinder::setBinding
void __thiscall HandleBinder::setBinding(int *pObject, int handle) {
    // Store the object pointer at offset +0x4
    this->m_pObject = pObject;

    // Call virtual function at offset 8: likely initialization/reset
    (*(void (__stdcall **)(void*))*pObject + 8)(); // or reinterpret_cast

    if (handle != 0) {
        // Register the binding; returns something stored at +0x8
        this->m_handle = RegisterHandleBinding(handle, this->m_pObject); // FUN_004265d0

        // Call virtual function at offset 4: likely bind/associate
        (*(void (__stdcall **)(void*, int, int))*pObject + 4)(pObject, handle, 0);

        // Call virtual function at offset 12: finalize/complete
        (*(void (__stdcall **)(void*))*pObject + 12)();
    } else {
        this->m_handle = 0;
        // Call virtual function at offset 12
        (*(void (__stdcall **)(void*))*pObject + 12)();
    }
}