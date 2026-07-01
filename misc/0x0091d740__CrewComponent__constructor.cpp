// FUNC_NAME: CrewComponent::constructor

CrewComponent* __fastcall CrewComponent::constructor(CrewComponent* this) {
    // Call base class constructor
    ComponentBase::constructor((ComponentBase*)this); // FUN_005bf9b0

    // Set virtual function table pointer (vtable)
    this->vtable = (CrewComponentVtable*)&PTR_FUN_00d85a88; // +0x00

    // Set static data pointer (likely shared component data)
    this->sharedData = (CrewComponentData*)&PTR_LAB_00d85a60; // +0x10

    return this;
}