// FUNC_NAME: SomeManager::constructor
void SomeManager::constructor() {
    // Call base class constructor with fields at +4 and +8
    BaseManager::constructor(*(int *)(this + 4), *(int *)(this + 8));

    *(int *)(this + 0xc) = 0;  // m_state

    if (1 < *(unsigned int *)(this + 8)) {
        // If reference count > 1, release previous resource
        releaseResource(*(int *)(this + 4));
    }

    *(int *)(this + 0x10) = _DAT_00d5780c;  // m_globalPtrA
    *(int *)(this + 0x14) = DAT_00d5eee4;   // m_globalPtrB
    *(int *)(this + 0xc) = 0;              // m_state (reset)
    *(int *)(this + 0x18) = 0;             // m_counter

    *(int *)(this + 8) = 1;                // m_refCount
    *(int **)(this + 4) = &DAT_00ef4398;   // vtable pointer
}