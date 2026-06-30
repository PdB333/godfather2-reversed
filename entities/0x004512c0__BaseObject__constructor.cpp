// FUNC_NAME: BaseObject::constructor

void BaseObject::constructor(void)
{
    // +0x00: vtable pointer (set to a global function table)
    this->vtablePtr = &PTR_FUN_00e316f0;

    // +0x04: field set to 1 (likely some flag)
    this->field_04 = 1;

    // +0x08: field set to 0
    this->field_08 = 0;

    // +0x0C: field set to 0x20 (32)
    this->field_0C = 32;

    // +0x90 (0x24*4): clear field
    this->field_90 = 0;

    // +0x114 (0x45*4): clear field
    this->field_114 = 0;

    // +0x198 (0x66*4): clear field
    this->field_198 = 0;

    // +0x19C (0x67): set byte to 1
    this->field_19C_byte = 1;

    // Initialize a subsystem (argument 0: probably null or default)
    SubsystemInit(0);

    // +0x1B0 (0x6C*4): clear field
    this->field_1B0 = 0;

    // +0x1B4 (0x6D*4): clear field
    this->field_1B4 = 0;

    // +0x1B8 (0x6E*4): clear field
    this->field_1B8 = 0;

    // +0x1BC (0x6F*4): clear field
    this->field_1BC = 0;

    // +0x1C0 (0x70): clear byte
    this->field_1C0_byte = 0;

    // +0x1C4 (0x71): initialize string buffer A (size 0x141? up to 0x1B2)
    StringInit(&this->bufferA);

    // +0x6C8 (0x1B2*4): initialize string buffer B (size 0x141)
    StringInit(&this->bufferB);

    // Set magic/canary values for buffer bounds checking
    // (0xbadbadba, 0xbeefbeef, 0xeac15a55, 0x91100911)
    this->magic1 = 0xbadbadba;   // +0xBC8 (0x2F3*4)
    this->magic2 = 0xbeefbeef;   // +0xBCC (0x2F4*4)
    this->magic3 = 0xeac15a55;   // +0xBD0 (0x2F5*4)
    this->magic4 = 0x91100911;   // +0xBD8 (0x2F6*4)

    // Clean up any previous global instances if they still exist
    if (g_globalObjectA != 0) {
        GlobalCleanup();  // FUN_00407e60
    }
    if (g_globalObjectB != 0) {
        GlobalCleanup();
    }
    if (g_globalObjectC != 0) {
        GlobalCleanup();
    }
}