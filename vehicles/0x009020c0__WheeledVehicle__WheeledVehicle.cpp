// FUNC_NAME: WheeledVehicle::WheeledVehicle
// 0x009020c0 - Constructor for WheeledVehicle (derived from BaseVehicle)
// Initializes vehicle state: calls base constructor, sets up vtables, zeroes physics flags.

WheeledVehicle* __thiscall WheeledVehicle::WheeledVehicle(WheeledVehicle* this, undefined4 baseInitArg)
{
    // Call base class constructor (BaseVehicle)
    BaseVehicle::BaseVehicle(baseInitArg);

    // Clear various 16-bit vehicle state fields (controller flags, physics)
    *(short*)((int)this + 0x15) = 0; // +0x15: e.g., steeringInput
    *(short*)((int)this + 0x17) = 0; // +0x17: throttleInput
    *(short*)((int)this + 0x5e) = 0; // +0x5e: brakeInput
    *(short*)((int)this + 0x19) = 0; // +0x19: handbrake
    *(short*)((int)this + 0x66) = 0; // +0x66: wheelAngle (packed)

    // Set up vtable pointers (derived class and two base sub-objects)
    this->vtable = (void**)&PTR_FUN_00d81c70;      // +0x00: main vtable for WheeledVehicle
    this->subVtable1 = (void**)&PTR_LAB_00d81c60;  // +0x3C: subobject vtable (e.g., IVehiclePhysics)
    this->subVtable2 = (void**)&PTR_LAB_00d81c5c;  // +0x48: subobject vtable (e.g., IBreakable)

    // Zero out additional 32-bit fields (counters, timers, etc.)
    this->field_0x6C = 0; // +0x6C
    this->field_0x50 = 0; // +0x50
    this->field_0x68 = 0; // +0x68
    this->field_0x58 = 0; // +0x58
    this->field_0x60 = 0; // +0x60

    return this;
}