// FUNC_NAME: ComponentBase::reset
void ComponentBase::reset(ComponentBase* self)
{
    if (self != 0) {
        // Call base or internal initialization routine
        sub_6f5320();
        // Clear a flag or counter at offset 0x24 (e.g., m_flags, m_refCount)
        *(int*)(self + 0x24) = 0;
    }
}