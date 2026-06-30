// FUNC_NAME: PacketBuilder::buildAndSendPacket
void __thiscall PacketBuilder::buildAndSendPacket(PacketBuilder* this, int32_t param_2, int32_t param_3, int32_t param_4) {
    // Temporary buffer for constructing packet data (12 bytes initial, followed by 4 fields)
    uint8_t buffer[12];   // +0x00 buffer start
    int32_t field1 = 0;   // +0x0C offset from buffer start
    int32_t field2 = 0;   // +0x10
    int32_t field3 = 0;   // +0x14
    int32_t field4 = 0;   // +0x18 (not used directly, but set from global)
    uint8_t* pBuffer = buffer; // pointer to the stack buffer

    // Initialize fields
    field1 = 0;
    field2 = 0;
    field3 = 0;
    field4 = DAT_00e2b1a4; // Global constant (probably a packet type or version)

    // Call virtual method at vtable offset 0x90 (e.g., preparePacket)
    (this->vtable[0x90 / 4])();

    // Process the packet buffer via another function (likely serialization or sending)
    FUN_0044b4e0(param_2, &pBuffer); // Pass pointer to pointer so it can modify buffer if needed
}