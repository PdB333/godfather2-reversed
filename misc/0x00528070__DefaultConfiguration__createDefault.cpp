// FUNC_NAME: DefaultConfiguration::createDefault
void createDefaultConfiguration(void)
{
    // Allocate a default configuration object (type ID 0xd, alignment 4, flags 0,1,0)
    uint32_t* config = (uint32_t*)FUN_0060cd00(0xd, 4, 0, 1, 0);
    uint32_t globalA = DAT_00e2eff4;  // +0x0 global constant
    uint32_t globalB = DAT_00e2b1a4;  // +0x4 global constant

    if (config != nullptr)
    {
        // Initialize 16 uint32 fields with global constants and zeros
        config[0]  = globalA;  // +0x00
        config[1]  = globalB;  // +0x04
        config[2]  = 0;        // +0x08
        config[3]  = 0;        // +0x0C
        config[4]  = globalB;  // +0x10
        config[5]  = globalB;  // +0x14
        config[6]  = globalB;  // +0x18
        config[7]  = 0;        // +0x1C
        config[8]  = globalB;  // +0x20
        config[9]  = globalA;  // +0x24
        config[10] = globalB;  // +0x28
        config[11] = globalB;  // +0x2C
        config[12] = globalA;  // +0x30
        config[13] = globalA;  // +0x34
        config[14] = 0;        // +0x38
        config[15] = globalB;  // +0x3C

        // Perform post-initialization (likely registration or completion callback)
        FUN_0060cde0();
    }
}