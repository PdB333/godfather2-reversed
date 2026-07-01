// FUNC_NAME: StreamManager::constructor
undefined4 * __fastcall StreamManager::constructor(StreamManager *this)
{
    // Store singleton reference in global
    g_pStreamManager = this;

    // Set virtual table pointer
    this->vtable = (StreamManagerVTable *)&PTR_FUN_00d6854c;

    // Initialize 12 internal fields to zero (offsets 0x04 - 0x30? assuming 4-byte each)
    this->field_0x04 = 0;
    this->field_0x08 = 0;
    this->field_0x0c = 0;
    this->field_0x10 = 0;
    this->field_0x14 = 0;
    this->field_0x18 = 0;
    this->field_0x1c = 0;
    this->field_0x20 = 0;
    this->field_0x24 = 0;
    this->field_0x28 = 0;
    this->field_0x2c = 0;
    this->field_0x30 = 0;

    // Initialize 4 sub-buffers of 0x80 bytes each
    this->initSubBuffer(0x80);  // sub-buffer 0
    this->initSubBuffer(0x80);  // sub-buffer 1
    this->initSubBuffer(0x80);  // sub-buffer 2
    this->initSubBuffer(0x80);  // sub-buffer 3

    return this;
}