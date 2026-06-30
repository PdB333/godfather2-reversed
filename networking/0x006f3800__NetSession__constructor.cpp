// FUNC_NAME: NetSession::constructor
NetSession* __thiscall NetSession::constructor(NetSession* this, int param_2) {
    // vtable at +0x00
    this->vtable = (NetSessionVtable*)&PTR_FUN_00d60690;
    // +0x04: packet window size (0x21 = 33, likely 32 slots + 1 sentinel)
    this->packetWindowSize = 0x21;
    // +0x08: flag or counter
    this->field_0x08 = 0;
    // +0x0C: stored parameter (session ID or connection token)
    this->sessionParam = param_2;
    // Initialize four internal streams (reliable, unreliable, etc.)
    this->initStream();
    this->initStream();
    this->initStream();
    this->initStream();
    // +0xE8 (0x3a * 4): clear a pointer or status field
    this->field_0xE8 = 0;
    return this;
}