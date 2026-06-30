// FUNC_NAME: BaseVehicle::BaseVehicle

BaseVehicle * __fastcall BaseVehicle::BaseVehicle(BaseVehicle *this)
{
    // Call base class constructor (likely common engine base)
    EngineBase::constructor();

    // Set vtable pointer for this class
    this->vtable = (void **)&PTR_FUN_00d5f4d4;

    // Set secondary vtable pointers for multiple inheritance
    // Offset +0x3C: second base class vtable
    this->secondaryVTable1 = &PTR_LAB_00d5f4c4;   // +0x3C
    // Offset +0x48: third base class vtable
    this->secondaryVTable2 = &PTR_LAB_00d5f4c0;   // +0x48
    // Offset +0x50: fourth base class vtable
    this->secondaryVTable3 = &PTR_LAB_00d5f4bc;   // +0x50

    // Zero out 4 fields at offsets +0x58, +0x5C, +0x60, +0x64
    this->field_0x58 = 0;    // +0x58
    this->field_0x5C = 0;    // +0x5C
    this->field_0x60 = 0;    // +0x60
    this->field_0x64 = 0;    // +0x64

    // Call specific initialization for this class
    BaseVehicle::subInitialize();

    return this;
}