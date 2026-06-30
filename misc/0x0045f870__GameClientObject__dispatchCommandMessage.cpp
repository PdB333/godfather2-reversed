// FUNC_NAME: GameClientObject::dispatchCommandMessage
void __thiscall GameClientObject::dispatchCommandMessage(int* thisPtr, uint param_2, uint param_3, uint param_4)
{
    // Build a temporary command buffer on stack
    // +0x00: CommandHeader data (12 bytes)
    uint8 commandHeader[12];  // offset local_50
    // +0x0C: padding[4] local_44
    // +0x10: padding[4] local_34
    // +0x14: padding[4] local_24
    // +0x18: signature constant local_14
    struct CommandBuffer {
        uint8 header[12];   // 0x00
        uint32 pad0;        // 0x0C
        uint32 pad1;        // 0x10
        uint32 pad2;        // 0x14
        uint32 signature;   // 0x18
    };
    CommandBuffer cmdBuf;
    cmdBuf.pad0 = 0;
    cmdBuf.pad1 = 0;
    cmdBuf.pad2 = 0;
    cmdBuf.signature = DAT_00e2b1a4;  // global constant, likely a magic number
    
    // Call virtual function at vtable offset 0x8c (e.g., preProcessCommand)
    (**(code**)(*thisPtr + 0x8c))();
    
    // Process the command with the buffer built from param_2 (e.g., a message type/ID)
    FUN_0044b4e0(param_2, &cmdBuf.header);
}