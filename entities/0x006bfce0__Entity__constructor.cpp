// FUNC_NAME: Entity::constructor
void __thiscall Entity::constructor(Entity *this)
{
    // Set vtable pointer to the class's virtual function table
    this->vtable = &PTR_FUN_00d5ee24;          // +0x00: vtable address
    // Set a secondary function pointer (possibly destructor or custom deleter)
    this->m_pDestructorFunc = &PTR_LAB_00d5ee1c; // +0x08: function pointer

    // If a child object exists at offset 0x270, release it before reinitializing
    if (this->m_pChildObject != nullptr) {     // +0x9c * 4 = +0x270
        releaseSubObject(this->m_pChildObject);
    }

    // Perform global initialization (e.g., register with manager)
    postInit();
}