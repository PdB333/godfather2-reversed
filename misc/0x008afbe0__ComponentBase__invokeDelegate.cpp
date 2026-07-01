// FUNC_NAME: ComponentBase::invokeDelegate
// Address: 0x008afbe0
// Role: Calls a virtual method at vtable offset 0xB8 on the delegate object pointed to by m_pDelegate (+0x40).
// If the delegate pointer is null, nothing happens.

class ComponentBase {
public:
    // Pointer to a delegate/listener object; null if unset (offset +0x40)
    void* m_pDelegate;  // offset 0x40

    // Invokes the delegate's virtual method at vtable offset 0xB8 (typically an update/tick callback)
    // This method is a thin wrapper that ensures the delegate exists before calling.
    void __fastcall invokeDelegate() {
        if (m_pDelegate != nullptr) {
            // Dereference delegate pointer to get vtable, then call function at offset 0xB8
            // The delegate's virtual function signature is void (*)()
            (**(void (__thiscall**)(void*))((uintptr_t*)m_pDelegate + 0xB8))(m_pDelegate);
        }
    }
};