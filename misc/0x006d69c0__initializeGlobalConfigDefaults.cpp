// FUNC_NAME: initializeGlobalConfigDefaults
void __fastcall initializeGlobalConfigDefaults(uint32_t* config)
{
    // This function initializes a configuration structure with default values
    // loaded from global data (likely preset constants from game data).
    // Structure size is at least 0x88 bytes (34 * 4).
    
    // Offset +0x28 (10*4) through +0x34 (0xD*4) are zeroed initially
    config[10] = 0;
    config[11] = 0;
    config[12] = 0;
    config[13] = 0;
    
    // Then set from globals at offsets +0x38, +0x3C, +0x40, +0x44, +0x48
    config[14] = DAT_00d5f528;    // +0x38: unknown global
    config[15] = DAT_00d5efd0;    // +0x3C
    config[16] = DAT_00d58cbc;    // +0x40
    config[17] = DAT_00d5eee4;    // +0x44
    config[18] = DAT_00d5efa4;    // +0x48
    
    // Offset +0x4C is zeroed, then +0x54 and +0x58 set from same global
    config[19] = 0;
    config[21] = DAT_00d5d7b8;    // +0x54
    config[22] = DAT_00d5d7b8;    // +0x58 (same value)
    
    // Offset +0x60 zeroed, then base fields set
    config[24] = 0;
    config[0]  = _DAT_00d5780c;   // +0x00: likely a base value
    config[1]  = DAT_00d5ddec;    // +0x04
    config[3]  = _DAT_00d5780c;   // +0x0C: repeats base
    config[4]  = _DAT_00d5780c;   // +0x10: repeats base
    
    // More globals for other offsets
    config[2]  = DAT_00d5f524;    // +0x08
    config[5]  = _DAT_00d5c458;   // +0x14
    config[8]  = _DAT_00d5c458;   // +0x20: repeats
    config[9]  = _DAT_00d5c458;   // +0x24: repeats
    config[6]  = _DAT_00d5ca1c;   // +0x18
    config[29] = DAT_00d5f520;    // +0x74
    config[7]  = DAT_00d5eee0;    // +0x1C
    config[30] = DAT_00d5ef88;    // +0x78
    
    // Offset +0x88 is zeroed
    config[34] = 0;
}