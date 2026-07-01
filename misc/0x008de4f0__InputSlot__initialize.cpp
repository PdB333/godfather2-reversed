// FUNC_NAME: InputSlot::initialize
void __thiscall InputSlot::initialize(uint deviceId) {
    // +0x18: set to a global constant (likely INVALID_DEVICE or default state)
    this->field_0x18 = DAT_01205228;
    // +0x08: store the device identifier
    this->field_0x08 = deviceId;
}