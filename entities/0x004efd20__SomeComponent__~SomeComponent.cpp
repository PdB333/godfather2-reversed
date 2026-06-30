// FUNC_NAME: SomeComponent::~SomeComponent
// Address: 0x004efd20
// Destructor: releases a pointer at offset 0x34 (m_pChild), then calls base destructor.

SomeComponent * __thiscall SomeComponent::~SomeComponent(SomeComponent *this, byte destroyFlag)
{
    // Set vtable to derived class destructor vtable
    this->vtable = (void **)&PTR_FUN_00e373a4; // derived destructor vtable

    // If the child pointer at offset 0x34 is non-null, mark it as released and null it
    if (this->m_pChild != nullptr) {
        *(int *)this->m_pChild = 3; // likely sets a "released" flag
        this->m_pChild = nullptr;
    }

    // Set vtable to base class destructor vtable
    this->vtable = (void **)&PTR_LAB_00e37304; // base destructor vtable

    // If destroyFlag indicates delete, free memory
    if ((destroyFlag & 1) != 0) {
        operator delete(this);
    }

    return this;
}