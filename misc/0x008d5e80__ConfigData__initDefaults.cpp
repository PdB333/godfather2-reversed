// FUNC_NAME: ConfigData::initDefaults
void __thiscall ConfigData::initDefaults(ConfigData* this)
{
    // Initializes a ConfigData struct with 5 fields (offsets 0x00, 0x04, 0x08, 0x0C, 0x10)
    // Values come from global constants _DAT_00d5c458 and _DAT_00d5780c
    this->field0 = 0;                     // +0x00
    this->field1 = 0;                     // +0x04
    this->field2 = _DAT_00d5c458;         // +0x08 (global constant)
    this->field3 = 0;                     // +0x0C
    this->field4 = _DAT_00d5780c;         // +0x10 (global constant)
}