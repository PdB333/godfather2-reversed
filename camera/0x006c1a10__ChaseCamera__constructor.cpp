// FUNC_NAME: ChaseCamera::constructor
int __fastcall ChaseCamera::constructor(ChaseCamera* this)
{
    // Call base initializers
    FUN_006da9d0();   // Initialize camera base
    FUN_006daa50();   // Set default camera parameters

    // Global initialization flag
    DAT_00e50df6 = 1;

    // Reset state flags (offsets 0x30-0x3c)
    this->field_0x30 = 1;          // +0x30: active flag
    this->field_0x38 = 1;          // +0x38: interpolation enabled
    this->field_0x34 = 0;          // +0x34: some enum/state
    this->field_0x39 = 0;          // +0x39: flag
    this->field_0x3a = 0;          // +0x3a: flag
    this->field_0x3b = 0;          // +0x3b: flag
    this->field_0x3c = 0;          // +0x3c: flag

    // Zero out position vector (offset 0x40, 0x44, 0x48)
    this->positionX = this->positionX - this->positionX; // = 0
    this->positionY = this->positionY - this->positionY; // = 0
    this->positionZ = this->positionZ - this->positionZ; // = 0

    // Zero out orientation/offset vector (offset 0x4c-0x60)
    this->field_0x4c = 0;
    this->field_0x50 = 0;
    this->field_0x54 = 0;
    this->field_0x58 = 0;
    this->field_0x5c = 0;
    this->field_0x60 = 0;

    // Store global pointer (offset 0x64)
    this->pDefaultTarget = DAT_00d5eea0; // +0x64: target object reference

    // Zero remaining fields (offset 0x68-0x70)
    this->field_0x68 = 0;
    this->field_0x6c = 0;
    this->field_0x70 = 0;

    return this;
}