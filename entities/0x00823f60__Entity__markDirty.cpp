// FUNC_NAME: Entity::markDirty
void __thiscall Entity::markDirty(void)
{
    // Offset +0x5c likely points to a replication/network data block (e.g., m_pNetState)
    int* pNetState = *(int**)(this + 0x5c);
    if (pNetState != 0)
    {
        // Likely acquires a mutex or spinlock to avoid race conditions
        SomeLockFunction();
        // Set the dirty flag (bit 0) at offset +0x24 of the net state block
        *(uint*)(pNetState + 0x24) |= 1;
    }
}