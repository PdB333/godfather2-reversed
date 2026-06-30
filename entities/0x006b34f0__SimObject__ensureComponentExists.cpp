// FUNC_NAME: SimObject::ensureComponentExists

// Address: 0x006b34f0
// Checks if the component pointer at offset +0x16c is null; if so, calls the initialization function.
// Typically used for lazy creation of a sub-object (e.g., AI component, physics body).
void __thiscall SimObject::ensureComponentExists(void)
{
    // m_pComponent is at this+0x16c
    if (this->m_pComponent == 0) {
        this->createComponent(); // FUN_006b3390 – allocates/initializes the component
    }
}