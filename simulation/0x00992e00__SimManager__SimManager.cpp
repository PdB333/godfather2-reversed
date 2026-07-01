// FUNC_NAME: SimManager::SimManager
SimManager* __fastcall SimManager::SimManager(SimManager* this)
{
    uint32_t globalValue = DAT_00d7c2d0;

    // Zero out initial fields
    this->field3 = 0;          // +0x0C
    this->field1 = 0;          // +0x04
    this->field2 = 0;          // +0x08
    this->field4 = 0;          // +0x10
    this->field5 = 0;          // +0x14
    this->field6 = &PTR_LAB_00d9208c; // +0x18, original vtable? overwritten later

    // Store global singleton pointer
    _DAT_0113093c = this;

    // Set vtable pointer (derived class vtable)
    this->vtable = &PTR_LAB_00d92094;  // +0x00

    // Overwrite field6 with another vtable pointer (maybe base class)
    this->field6 = &PTR_LAB_00d92090;  // +0x18

    // Initialize remaining fields to zero
    this->field7 = 0;          // +0x1C
    this->field8 = 0;          // +0x20
    this->field10h = 0;        // +0x40
    this->field0fh = 0;        // +0x3C
    this->field0eh = 0;        // +0x38
    this->field0dh = 0;        // +0x34
    *(byte*)(&this->field11h) = 0;  // +0x44
    *(byte*)(&this->field12h) = 0;  // +0x48
    this->field18h = 0;        // +0x60
    this->field17h = 0;        // +0x5C
    this->field16h = 0;        // +0x58
    this->field15h = 0;        // +0x54
    *(byte*)(&this->field19h) = 0;  // +0x64
    this->field1bh = globalValue;   // +0x6C

    // Allocate internal buffers
    this->buffer1 = (uint32_t*)allocate(0x40);   // +0x24
    this->buffer2 = (uint32_t*)allocate(0x40);   // +0x28
    this->buffer3 = (uint32_t*)allocate(0x20);   // +0x2C
    this->buffer4 = (uint32_t*)allocate(0x20);   // +0x4C
    this->buffer5 = (uint32_t*)allocate(0x100);  // +0x68

    // Clear byte fields in the structure
    *(byte*)((int)this + 0x33) = 0;  // +0x33
    *(byte*)((int)this + 0x32) = 0;  // +0x32
    *(byte*)((int)this + 0x31) = 0;  // +0x31
    *(byte*)(&this->fieldCh) = 0;    // +0x30
    *(byte*)((int)this + 0x53) = 0;  // +0x53
    *(byte*)((int)this + 0x52) = 0;  // +0x52
    *(byte*)((int)this + 0x51) = 0;  // +0x51
    *(byte*)(&this->field14h) = 0;   // +0x50

    return this;
}