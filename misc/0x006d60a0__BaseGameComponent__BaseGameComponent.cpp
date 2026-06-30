// FUNC_NAME: BaseGameComponent::BaseGameComponent

void __fastcall BaseGameComponent::BaseGameComponent(BaseGameComponent *this)
{
    // Set primary vtable pointer at offset +0x00
    this->vtable = (BaseGameComponentVTable *)&PTR_FUN_00d5f45c;

    // Set secondary vtable pointers for base classes
    // +0x3C (0xF * 4) — likely second base class vtable
    this->base1Vtable = (Base1VTable *)&PTR_LAB_00d5f44c;
    // +0x48 (0x12 * 4) — likely third base class vtable
    this->base2Vtable = (Base2VTable *)&PTR_LAB_00d5f448;

    // Initialize embedded subobject at offset +0x50 (0x14 * 4)
    // Subobject is at this + 0x14 (interpreted as pointer arithmetic on byte offsets)
    BaseGameComponent::initSubObjectPart1(&this->subObject);  // FUN_004086d0
    BaseGameComponent::initSubObjectPart2(&this->subObject);  // FUN_00408310

    // Call global engine initialization routine
    GlobalInitFunction();  // FUN_0046c640
}