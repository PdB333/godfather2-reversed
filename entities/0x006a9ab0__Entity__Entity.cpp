// FUNC_NAME: Entity::Entity
struct Entity {
    void *m_pVtable;          // +0x00
    // offsets 0x04 to 0x38: unknown
    void *m_pFunc1;           // +0x3C
    void *m_pFunc2;           // +0x48
    void *m_pFunc3;           // +0x50
    // ... many others ...
    void *m_pAllocatedData;   // +0x140
};

void __thiscall Entity::Entity(Entity *this)
{
    this->m_pVtable = (void *)&PTR_FUN_00d5d980;   // vtable for Entity
    this->m_pFunc1  = (void *)&PTR_LAB_00d5d970;   // offset 0x3C function pointer
    this->m_pFunc2  = (void *)&PTR_LAB_00d5d96c;   // offset 0x48 function pointer
    this->m_pFunc3  = (void *)&PTR_LAB_00d5d968;   // offset 0x50 function pointer

    // Free previously allocated sub-object if it exists
    if (this->m_pAllocatedData != 0) {
        FUN_004daf90(this->m_pAllocatedData);      // deallocate internal data
    }

    // Global engine initialization routine
    FUN_00474090();
}