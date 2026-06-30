// FUNC_NAME: SomeComponent::~SomeComponent
// Address: 0x00728db0
// Destructor: releases child component at offset +8, then sets vtable to base destructor table.

void __fastcall SomeComponent::~SomeComponent(SomeComponent* this)
{
    // Check and destroy child component (e.g., a sub-object or resource) at offset +0x8
    if (this->m_childComp != nullptr) {
        FUN_004daf90(&this->m_childComp); // release/destroy child
        // Note: FUN_004daf90 likely calls the child's destructor or decrements reference count
    }
    // Set vtable pointer to static destructor table (prevents virtual calls after destruction)
    this->vtable = &PTR_LAB_00e2f0c0; // Assign base destructor vtable
}