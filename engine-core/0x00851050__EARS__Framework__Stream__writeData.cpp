// FUNC_NAME: EARS::Framework::Stream::writeData
void __thiscall Stream::writeData(uint param_1, uint* param_2, uint param_3, uint* param_4, uint param_5)
{
    // TLS context switch (EARS thread storage)
    TlsGetValue(DAT_01139810);
    
    // Allocate small header block (0x20 bytes, allocation tag 0x27)
    int headerBlock = FUN_00aa2680(0x20, 0x27);
    *(uint16*)(headerBlock + 4) = 0x20; // Store allocation size in header
    
    // Retrieve stream buffer from connection/stream manager
    uint* streamBuffer = (uint*)FUN_00a64b00(param_3);
    
    // Build packet header (local buffer represents header structure)
    // Known offsets: +0x00: magic/constant, +0x10: another constant, +0x20: data payload
    uint localHeader[16] = {0};
    localHeader[0] = _DAT_00d5780c;     // +0x00: magic constant
    localHeader[2] = 0;                 // +0x08: reserved
    // ... zeros for intermediate fields ...
    localHeader[3] = _DAT_00d5780c;     // +0x0C: second constant
    localHeader[10] = _DAT_00d5780c;    // +0x28: third constant
    // Copy user data into header (4 words = 16 bytes)
    localHeader[12] = param_4[0];       // +0x30
    localHeader[13] = param_4[1];       // +0x34
    localHeader[14] = param_4[2];       // +0x38
    localHeader[15] = param_4[3];       // +0x3C
    
    // Allocate transmission buffer (0x160 bytes, allocation tag 0x31)
    int dataBlock = FUN_00aa2680(0x160, 0x31);
    *(uint16*)(dataBlock + 4) = 0x160; // Store allocation size
    
    // Serialize header and data into stream buffer (returns handle/token)
    uint resultToken = FUN_009f0c70(streamBuffer, &localHeader, param_5);
    *param_2 = resultToken;  // Return packet handle
    
    // Debug/logging callback
    FUN_0043b490();
    
    // Post event to subsystem (type 0x2001, target object param_1)
    FUN_009f01f0(0x2001, param_1, 0);
    
    // Reference counting on stream buffer
    if (*(int16*)(streamBuffer + 1) != 0)  // Check ref count (at offset +4)
    {
        // Decrement ref count (at offset +6)
        *(int16*)((int)streamBuffer + 6) -= 1;
        if (*(int16*)((int)streamBuffer + 6) == 0)
        {
            // Release stream buffer (call vtable function at offset 0)
            (*(void (__thiscall**)(int))streamBuffer)(1); // parameter 1 = cleanup flag
        }
    }
    return;
}