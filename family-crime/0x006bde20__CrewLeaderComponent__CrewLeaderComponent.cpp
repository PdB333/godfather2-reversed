// FUNC_NAME: CrewLeaderComponent::CrewLeaderComponent
void __thiscall CrewLeaderComponent::CrewLeaderComponent(CrewLeaderComponent *this)   // [0x006bde20] Constructor for crew leader component
{
    // Set primary vtable (CrewLeaderComponent virtual table)
    this->vfptr = (CrewLeaderComponent_vtbl *)&PTR_FUN_00d5eaec;

    // Set secondary vtable for a base interface (offset +0x3C)
    *(uint32_t *)((uint8_t *)this + 0x3C) = (uint32_t)&PTR_LAB_00d5eadc;

    // Set tertiary vtable for another interface (offset +0x48)
    *(uint32_t *)((uint8_t *)this + 0x48) = (uint32_t)&PTR_LAB_00d5ead8;

    // Initialize sub-component at offset 0x80 (e.g., base state machine or component data)
    FUN_004086d0((uint8_t *)this + 0x80);
    FUN_00408310((uint8_t *)this + 0x80);

    // Finalize construction (e.g., register with manager)
    FUN_006bcd70();
}