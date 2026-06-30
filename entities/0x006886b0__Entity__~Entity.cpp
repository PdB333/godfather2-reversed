// FUNC_NAME: Entity::~Entity
void __fastcall Entity::~Entity(Entity* this)
{
    // Check if the sub-object pointer at offset 0x140 is non-null
    if (this->m_pSubObject != nullptr) {
        // Call destructor/release on the sub-object (FUN_004daf90)
        SubObject::destructor(this->m_pSubObject);
    }
    // Global cleanup (FUN_00726b40)
    GlobalCleanupFunction();
}