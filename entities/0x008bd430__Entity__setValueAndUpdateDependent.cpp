// FUNC_NAME: Entity::setValueAndUpdateDependent
void __thiscall Entity::setValueAndUpdateDependent(int this, int value)
{
    // +0x100: m_value - primary storage
    *(int *)(this + 0x100) = value;
    // +0x230: m_pDependentValue - pointer to mirrored location (non-null when active)
    if (*(int **)(this + 0x230) != (int *)0x0)
    {
        **(int **)(this + 0x230) = value;
    }
    return;
}