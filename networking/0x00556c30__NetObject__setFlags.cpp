// FUNC_NAME: NetObject::setFlags
void __thiscall NetObject::setFlags(NetObject* this, unsigned int param_2, unsigned int param_3)
{
    // Store flags at offset +0x2c: shift param_2 right by 2 and set top two bits
    this->field_0x2c = (param_2 >> 2) | 0xC0000000;

    // Initialize internal state (FUN_00556c80) - likely a member call
    this->init(param_3, 1);

    // Global update/routine (FUN_0043b490)
    globalUpdate();

    // Send network message/event with type 0x2001 (FUN_009f01f0)
    sendEvent(0x2001, param_3, 0);
}