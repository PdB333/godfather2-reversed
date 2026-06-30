// FUNC_NAME: SomeClass::release (destructor/cleanup with two embedded components and two owned objects)
void __thiscall SomeClass::release(void) {
    // Release owned object at +0x10 (m_ownedObjectB)
    if (m_ownedObjectB != nullptr) {
        // Virtual call at vtable index 1 (offset 4) – likely a release/delete function with flag 0
        m_embeddedComponentB->releaseObject(m_ownedObjectB, 0);
        m_ownedObjectB = nullptr;
    }
    // Cleanup embedded component at +0xc (m_embeddedComponentB)
    // Virtual call at vtable index 3 (offset 0xc) – likely destructor or cleanup
    m_embeddedComponentB->cleanup();

    // Release owned object at +0x8 (m_ownedObjectA)
    if (m_ownedObjectA != nullptr) {
        m_embeddedComponentA->releaseObject(m_ownedObjectA, 0);
        m_ownedObjectA = nullptr;
    }
    // Cleanup embedded component at +0x4 (m_embeddedComponentA)
    m_embeddedComponentA->cleanup();
}
```