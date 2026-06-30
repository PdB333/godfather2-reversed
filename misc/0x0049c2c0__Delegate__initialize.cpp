// FUNC_NAME: Delegate::initialize
// Function address: 0x0049c2c0
// Role: Initializes a delegate/callback object, storing object pointer, function pointer,
// user parameter, and registering the callback via virtual functions on the target object.

// The delegate vtable at 0x00e35228 is assumed to be defined elsewhere.
extern void* g_delegateVTable;

// Target object vtable: index 0 -> registerCallback(function, paramPtr)
//                      index 2 -> some prepare/validate step
struct IEventTarget {
    void** vtable; // +0x00
};

// Delegate struct (likely 28 bytes)
struct Delegate {
    void** vtable;       // +0x00
    IEventTarget* m_pTarget; // +0x04
    void* m_pFunction;   // +0x08 (passed in EAX)
    unsigned int m_param; // +0x0C
    int m_handle0;       // +0x10
    int m_handle1;       // +0x14
    int m_handle2;       // +0x18
};

void __thiscall Delegate::initialize(int* pTarget, unsigned int param)
{
    // In the actual code, the function pointer (m_pFunction) was passed in EAX.
    // We model it as a third parameter for clarity.
    // Since the decompiler lacks this, we declare it as a local that would be set by the caller.
    void* pFunction = (void*)0; // placeholder for the register value

    this->vtable = &g_delegateVTable;
    this->m_pTarget = (IEventTarget*)pTarget;
    this->m_pFunction = pFunction;
    this->m_param = param;

    if (pTarget != 0) {
        // Call virtual function at vtable offset 8 (third entry) on the target.
        // This might be a prepare/validate step.
        (*(void (__thiscall**)(IEventTarget*))((IEventTarget*)pTarget)->vtable[2])((IEventTarget*)pTarget);
    }

    if ((pFunction != 0) && (pTarget != 0)) {
        int local_c = 2; // Likely an enum: eRegisterCallback = 2
        int local_4 = 0;
        int local_8 = param;

        // Call virtual function at vtable offset 0 (first entry) on the target.
        // This registers the callback and returns a handle.
        int uVar1 = (*(int (__thiscall**)(IEventTarget*, void*, int*))((IEventTarget*)pTarget)->vtable[0])(
            (IEventTarget*)pTarget, pFunction, &local_c);

        this->m_handle0 = uVar1;
        this->m_handle1 = uVar1;
        this->m_handle2 = uVar1;
    } else {
        this->m_handle0 = 0;
        this->m_handle1 = 0;
        this->m_handle2 = 0;
    }
}