// FUNC_NAME: GameObject::~GameObject
// Destructor at 0x00488980. Releases child components, shuts down subsystems, clears global active object pointer.

class GameObject {
public:
    // Vtable structure (first entry at +0)
    void* vtable; // +0x00

    // Member fields
    void* m_pComponent1; // +0x04
    void* m_pComponent2; // +0x08
    int m_nFlags;        // +0x0C
    int m_nRefCount;     // +0x10 (or similar)
    void* m_pComponent3; // +0x14
    void* m_pSubSystem;  // +0x18

    // Virtual function table offsets (example)
    // vtable[0]: unknown
    // vtable[1]: releaseComponent(void* child, int param)
    // vtable[3]: shutdown()

    // Static globals
    static GameObject* s_pActiveObject; // DAT_012234a0

    // Constructor/Destructor
    GameObject();
    ~GameObject();
};

void __fastcall GameObject::~GameObject(void* thisPtr) {
    GameObject* self = (GameObject*)thisPtr;

    // Set vtable to initial destructor vtable (base destructor)
    self->vtable = &PTR_FUN_00e3380c; // Vtable for destructor phase 1

    // Notify some system (possibly object registry)
    registerCallback(0, &LAB_004887a0); // FUN_00607d50(0, &LAB_004887a0)

    // Release component2 (if any)
    if (self->m_pComponent2) {
        // Virtual call: releaseComponent(self->m_pComponent2, 0)
        typedef void (__fastcall* ReleaseFn)(void* child, int zero);
        ReleaseFn releaseFn = (ReleaseFn)(*(int*)(*(int*)self->m_pSubSystem + 4));
        releaseFn(self->m_pComponent2, 0);
    }
    self->m_pComponent2 = nullptr;
    self->m_nRefCount = 0;
    self->m_nFlags = 0;

    // Shutdown component1
    {
        typedef void (__fastcall* ShutdownFn)(void* component);
        ShutdownFn shutdownFn = (ShutdownFn)(*(int*)(*(int*)self->m_pComponent1 + 0xC));
        shutdownFn(self->m_pComponent1);
    }

    // Release component2 again (maybe after shutdown)
    if (self->m_pComponent2) {
        typedef void (__fastcall* ReleaseFn)(void* child, int zero);
        ReleaseFn releaseFn = (ReleaseFn)(*(int*)(*(int*)self->m_pSubSystem + 4));
        releaseFn(self->m_pComponent2, 0);
    }

    // Release component3 if exists
    if (self->m_pComponent3) {
        typedef void (__fastcall* ReleaseFn)(void* child, int zero);
        ReleaseFn releaseFn = (ReleaseFn)(*(int*)(*(int*)self->m_pSubSystem + 4));
        releaseFn(self->m_pComponent3, 0);
    }

    // Shutdown subsystem
    {
        typedef void (__fastcall* ShutdownFn)(void* subsystem);
        ShutdownFn shutdownFn = (ShutdownFn)(*(int*)(*(int*)self->m_pSubSystem + 0xC));
        shutdownFn(self->m_pSubSystem);
    }

    // Switch to finalized vtable (post-destruction)
    self->vtable = &PTR_LAB_00e33810;

    // Clear global active object pointer
    GameObject::s_pActiveObject = nullptr;
}