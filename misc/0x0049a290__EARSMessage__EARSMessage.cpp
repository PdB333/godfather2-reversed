// FUNC_NAME: EARSMessage::EARSMessage
void __thiscall EARSMessage::EARSMessage(EARSMessage *this, int messageType)
{
    // Base class vtable pointer at +0x00
    this->vtable = &PTR_LAB_00e35024; // vtable

    // +0x04: some initialization field (likely size or flags)
    this->field_0x04 = 0;

    // +0x08: short field set to 3 (maybe version or type)
    *(short *)(this + 2) = 3; // offset +8

    // Call base class constructor (likely another EARS class)
    FUN_00499da0(); // baseInit

    // +0x180 (0x60 * 4): store the message type parameter
    this->field_0x180 = messageType; // +0x180

    // +0x188 (0x62 * 4): clear field
    this->field_0x188 = 0; // +0x188

    // +0x18C (99 * 4): clear field
    this->field_0x18C = 0; // +0x18C

    // +0x1BB: clear a byte (maybe a flag)
    *((byte *)this + 0x1BB) = 0;

    // Clear a block of 0x2B bytes starting at +0x190 (100 * 4)
    memset(this + 100, 0, 0x2B); // offset 0x190, 43 bytes

    // +0x04: initialize a sub-object (likely a buffer or state)
    FUN_0049a970(this + 4); // subObjectInit

    return;
}