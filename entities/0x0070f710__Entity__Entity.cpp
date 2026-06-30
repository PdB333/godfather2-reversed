// FUNC_NAME: Entity::Entity
void __fastcall Entity::Entity(int* this)
{
    // Set primary vtable pointer (class hierarchy)
    *this = (int)&PTR_FUN_00d618a4;
    
    // Set secondary vtable pointers for multiple inheritance interfaces
    this[0xF] = (int)&PTR_LAB_00d61894;  // +0x3C
    this[0x12] = (int)&PTR_LAB_00d61890; // +0x48

    // Initialize embedded sub-object at offset 0x50 (this + 0x14)
    FUN_004086d0(this + 0x14);
    FUN_00408310(this + 0x14);

    // Global engine initialization
    FUN_0046c640();
}