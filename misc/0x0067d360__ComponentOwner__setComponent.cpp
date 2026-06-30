// FUNC_NAME: ComponentOwner::setComponent
void __thiscall ComponentOwner::setComponent(int *param_2)
{
    // Release the old component if it exists (vtable+0x0c = Release)
    if (this->m_component != (int *)0x0) {
        (*(void (__thiscall**)(int *))(**(int **)(this->m_component) + 0xc))(this->m_component);
    }
    // Store the new component pointer
    this->m_component = param_2;
    // AddRef the new component if it is non-null (vtable+0x08 = AddRef)
    if (param_2 != (int *)0x0) {
        (*(void (__thiscall**)(int *))(*param_2 + 8))(param_2);
    }
}