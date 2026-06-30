// FUNC_NAME: Entity::setSubObjectPointer
// Function at 0x00542390 in The Godfather 2 (EA EARS engine).
// Manages a pointer member at offset 0x10, detaching old and attaching new sub-object.
// Uses an embedded helper object at offset 0x8 (called m_inner below).
// Assumes __thiscall with unaff_ESI = this, unaff_EDI = newSubObject.
void Entity::setSubObjectPointer(void* newSubObject)
{
    // If we already have a sub-object, detach it
    if (this->m_subObject != 0) // +0x10
    {
        this->detachSubObject();             // FUN_009f1b20: release old sub-object
        this->m_inner.clear();               // FUN_009f1ad0(this+0x8): clear helper struct
        Entity::globalDetachNotification();  // FUN_009f01a0: global detach callback
    }

    // Store the new pointer
    this->m_subObject = newSubObject;

    // If new pointer is valid, attach it
    if (newSubObject != 0)
    {
        this->attachSubObject();             // FUN_009f1f90: attach new sub-object
        this->m_inner.init();                 // FUN_009f24c0(this+0x8): init helper struct
        Entity::globalAttachNotification();   // FUN_009f0190: global attach callback
    }
}