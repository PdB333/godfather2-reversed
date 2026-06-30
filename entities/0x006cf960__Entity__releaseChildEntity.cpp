// FUNC_NAME: Entity::releaseChildEntity
// Address: 0x006cf960
// Checks if the child entity pointer at offset 0xd0 is non-null, and if so, releases it.
void __fastcall Entity::releaseChildEntity(int thisPtr)
{
    // +0xd0: pointer to child entity (m_pChildEntity)
    if (*(int*)(thisPtr + 0xd0) != 0) {
        releaseEntity(); // FUN_004df6e0 - releases the child entity
    }
}