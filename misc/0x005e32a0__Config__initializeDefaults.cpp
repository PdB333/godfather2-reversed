// FUNC_NAME: Config::initializeDefaults
// Address: 0x005e32a0
// Role: Initializes default values for a configuration structure, likely memory pool sizes or thresholds.
// Offsets: +0x00: byte flag, +0x04: uint, +0x08: uint, +0x0C: uint, +0x10: uint, +0x14: uint,
//          +0x18: uint (zeroed), +0x1C: uint (zeroed), +0x20: uint (zeroed), +0x24: uint (zeroed),
//          +0x28: uint (set to 1)

void __thiscall Config::initializeDefaults(Config* this)
{
    this->flags = 0;                             // +0x00
    this->memoryLimit1 = 0x800000;               // +0x08 - 8 MB
    this->memoryLimit2 = 0x2000000;              // +0x0C - 32 MB
    this->memoryLimit3 = 0xC0000;                // +0x10 - 768 KB
    this->memoryLimit4 = 0x180000;               // +0x14 - 1.5 MB
    this->enableFeature = 1;                     // +0x28 - boolean flag
    this->maxPoolSize = 0x3200000;               // +0x04 - 50 MB
    this->reserved1 = 0;                         // +0x18
    this->reserved2 = 0;                         // +0x1C
    this->reserved3 = 0;                         // +0x20
    this->reserved4 = 0;                         // +0x24
}