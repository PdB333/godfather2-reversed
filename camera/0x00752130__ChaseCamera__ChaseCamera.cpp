// FUNC_NAME: ChaseCamera::ChaseCamera
ChaseCamera * __thiscall ChaseCamera::ChaseCamera(ChaseCamera *this, void *param2, uint param3)
{
    // Call base class constructor (presumably Camera::Camera or similar)
    FUN_0080e6a0(param2, param3);

    // Set vtable pointer
    *this = (ChaseCamera *)(&PTR_LAB_00d64b08); // vtable

    // Initialize fields
    this->mode = 3;                          // +0x5C: camera mode (e.g., chase)
    this->field_0x60 = 0;                    // +0x60
    this->field_0x64 = 0;                    // +0x64
    this->field_0x68 = 0;                    // +0x68
    this->field_0x6C = 0;                    // +0x6C
    this->field_0x70 = 0;                    // +0x70
    this->field_0x74 = 0;                    // +0x74
    this->field_0x7C = 0;                    // +0x7C
    this->field_0x80 = 0;                    // +0x80
    this->field_0x84 = 0;                    // +0x84
    this->field_0x88 = 0;                    // +0x88
    this->field_0x8C = 0;                    // +0x8C
    this->field_0x90 = 0;                    // +0x90
    this->field_0x98 = 0;                    // +0x98
    this->field_0x9C = 0;                    // +0x9C
    *(byte *)&this->field_0xA0 = 0;          // +0xA0 byte
    this->field_0xCC = 0;                    // +0xCC
    this->field_0xD0 = 0;                    // +0xD0
    this->field_0xE4 = 0;                    // +0xE4
    this->field_0xE8 = 0;                    // +0xE8
    this->field_0xFC = 0;                    // +0xFC
    this->field_0x100 = 0;                   // +0x100

    // Set target-related offset
    if (this->target != NULL) {              // +0x48: target pointer (e.g., player)
        this->targetOffset = (uint)((byte *)this->target - (byte *)this - 0x48); // +0x58: relative offset
    } else {
        this->targetOffset = 0;
    }
    this->field_0x100 = 0;                   // redundant zero (already set)

    return this;
}