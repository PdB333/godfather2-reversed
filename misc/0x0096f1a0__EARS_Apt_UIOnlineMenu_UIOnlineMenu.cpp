// Xbox PDB: EARS_Apt_UIOnlineMenu_UIOnlineMenu
// FUNC_NAME: DonMatchManager::DonMatchManager
// Constructor for the Don Match manager (multiplayer matchmaking system)
// Initializes all fields, allocates string buffers, registers callback functions
// Address: 0x0096f1a0

DonMatchManager * __fastcall DonMatchManager::DonMatchManager(DonMatchManager *this)
{
    // Call base class or initialization helper
    FUN_005bf9b0(); // likely memset or base constructor

    // Set vtable pointers (multiple inheritance or interface slots)
    this->vtable1 = &PTR_LAB_00d8de40; // +0x4C (0x13*4)
    g_pDonMatchManager = this; // DAT_01129930 = this

    this->vtable2 = &PTR_FUN_00e2f19c; // +0x50 (0x14*4)
    this->field_0x58 = 0; // +0x58 (0x16*4)
    this->field_0x54 = 1; // +0x54 (0x15*4)
    this->vtable0 = &PTR_FUN_00d8f218; // +0x00 (primary vtable)
    this->vtable3 = &PTR_LAB_00d8f1f4; // +0x10 (0x4*4)
    this->vtable1 = &PTR_LAB_00d8f1f0; // +0x4C (overwritten)
    this->vtable2 = &PTR_LAB_00d8f1e0; // +0x50 (overwritten)
    this->field_0x68 = 0; // +0x68 (0x1A*4)
    this->field_0xAC = 0; // +0xAC (0x2B*4)

    // Allocate a buffer of size 0x40 (64 bytes) - likely for something
    FUN_00968bf0(0x40);

    uVar1 = DAT_00d5c454; // some global value
    this->field_0xC0 = 0; // +0xC0 (0x30*4)
    this->field_0xC4 = 0; // +0xC4 (0x31*4)
    *(byte *)&this->field_0xD0 = 1; // +0xD0 (0x34*4) - byte at offset 0xD0
    this->field_0xD4 = 0; // +0xD4 (0x35*4)
    this->field_0xD8 = 10; // +0xD8 (0x36*4)
    this->field_0xDC = 0; // +0xDC (0x37*4)
    this->field_0xE0 = 0; // +0xE0 (0x38*4)
    this->field_0xF4 = 0; // +0xF4 (0x3D*4)
    this->field_0xF8 = 0; // +0xF8 (0x3E*4)
    this->field_0x108 = 0; // +0x108 (0x42*4)
    this->field_0x10C = 0; // +0x10C (0x43*4)
    this->field_0x110 = 0; // +0x110 (0x44*4)
    *(byte *)&this->field_0x11C = 0; // +0x11C (0x47*4) - byte
    this->field_0x134 = 0; // +0x134 (0x4D*4)
    this->field_0x140 = 0; // +0x140 (0x50*4)
    *(byte *)&this->field_0x144 = 1; // +0x144 (0x51*4) - byte
    *(byte *)((int)this + 0x145) = 0; // +0x145 - byte
    this->field_0x148 = 0; // +0x148 (0x52*4)
    this->field_0x14C = 0; // +0x14C (0x53*4)
    *(byte *)&this->field_0x160 = 0; // +0x160 (0x58*4) - byte
    this->field_0x164 = 0; // +0x164 (0x59*4)
    this->field_0x168 = 0; // +0x168 (0x5A*4)
    this->field_0x178 = 0; // +0x178 (0x5E*4)
    this->field_0x17C = 0; // +0x17C (0x5F*4)
    this->field_0x180 = 0; // +0x180 (0x60*4)

    // Call another initialization with parameter 6 and the global value
    FUN_00968fa0(6, uVar1);

    this->field_0x19C = 0xFFFFFFFF; // +0x19C (0x67*4)
    this->field_0x1A0 = 0xFFFFFFFF; // +0x1A0 (0x68*4)

    // Call some initialization
    FUN_009627b0();

    this->field_0x2B4 = 0; // +0x2B4 (0xAD*4)
    this->field_0x2B8 = 0; // +0x2B8 (0xAE*4)
    this->field_0x2BC = 0; // +0x2BC (0xAF*4)
    this->field_0x2C0 = 0xFFFFFFFF; // +0x2C0 (0xB0*4)
    this->field_0x2C4 = 0; // +0x2C4 (0xB1*4)
    this->field_0x2C8 = 0; // +0x2C8 (0xB2*4)
    this->field_0x2CC = 0; // +0x2CC (0xB3*4)
    this->field_0x2D0 = 0; // +0x2D0 (0xB4*4)
    this->field_0x2D4 = 0; // +0x2D4 (0xB5*4)
    this->field_0x2D8 = 0; // +0x2D8 (0xB6*4)
    this->field_0x2DC = 0; // +0x2DC (0xB7*4)
    *(byte *)&this->field_0x2E0 = 0; // +0x2E0 (0xB8*4) - byte
    this->field_0x2E4 = 6; // +0x2E4 (0xB9*4)
    this->field_0x2E8 = 0; // +0x2E8 (0xBA*4)

    // Call more initialization functions
    FUN_0096ec40();
    FUN_0096ed10();

    // Another memset-like call
    FUN_005bf9b0();

    // Set up more vtable pointers and fields
    this->vtable4 = &PTR_FUN_00d8eb70; // +0x508 (0x142*4)
    this->vtable5 = &PTR_LAB_00d8eb48; // +0x518 (0x146*4)
    this->vtable6 = &PTR_FUN_00d8dde4; // +0x570 (0x15C*4)
    this->field_0x574 = 0; // +0x574 (0x15D*4)
    this->field_0x578 = 0; // +0x578 (0x15E*4)
    this->field_0x57C = 0; // +0x57C (0x15F*4)
    this->field_0x580 = 0; // +0x580 (0x160*4)
    this->field_0x584 = 0; // +0x584 (0x161*4)
    this->field_0x588 = 0; // +0x588 (0x162*4)
    this->field_0x58C = 0; // +0x58C (0x163*4)

    // Another memset
    FUN_005bf9b0();

    this->field_0x638 = 0; // +0x638 (0x18E*4)
    this->vtable7 = &PTR_FUN_00d8ede0; // +0x590 (0x164*4)
    this->vtable8 = &PTR_LAB_00d8edb8; // +0x5A0 (0x168*4)

    // Array initialization: if count < 16, set element and increment
    if ((uint)this->field_0x638 < 0x10) {
        this->array1[this->field_0x638] = 2; // +0x5F8 (0x17E*4) base
        this->field_0x638 = this->field_0x638 + 1;
    }

    // Another memset
    FUN_005bf9b0();

    this->field_0x6E4 = 0; // +0x6E4 (0x1B9*4)
    this->vtable9 = &PTR_FUN_00d8f108; // +0x63C (399*4? Actually 0x18F? Let's compute: 399*4=0x63C, but offset 0x18F? Wait, 0x18F*4=0x63C, yes)
    this->vtable10 = &PTR_LAB_00d8f0e0; // +0x64C (0x193*4)

    // Another array initialization
    if ((uint)this->field_0x6E4 < 0x10) {
        this->array2[this->field_0x6E4] = 0; // +0x6A4 (0x1A9*4) base
        this->field_0x6E4 = this->field_0x6E4 + 1;
    }

    this->field_0x6E8 = 0; // +0x6E8 (0x1BA*4)
    this->field_0x6EC = 0; // +0x6EC (0x1BB*4)
    *(byte *)&this->field_0x6F0 = 0; // +0x6F0 (0x1BC*4) - byte
    *(byte *)((int)this + 0x6F1) = 0; // +0x6F1 - byte
    this->field_0x6F4 = 0; // +0x6F4 (0x1BD*4)
    this->field_0x6F8 = 0; // +0x6F8 (0x1BE*4)
    this->field_0x6FC = 0; // +0x6FC (0x1BF*4)
    this->field_0x700 = 0; // +0x700 (0x1C0*4)
    *(byte *)&this->field_0x704 = 0; // +0x704 (0x1C1*4) - byte

    // Allocate many 0x80-byte buffers (128 bytes each) for string storage
    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer1 = puVar2; // +0xC8 (0x32*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer2 = puVar2; // +0xCC (0x33*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer3 = puVar2; // +0xE4 (0x39*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer4 = puVar2; // +0xE8 (0x3A*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer5 = puVar2; // +0x114 (0x45*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer6 = puVar2; // +0x118 (0x46*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer7 = puVar2; // +0xEC (0x3B*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer8 = puVar2; // +0xF0 (0x3C*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer9 = puVar2; // +0x100 (0x40*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer10 = puVar2; // +0x104 (0x41*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer11 = puVar2; // +0xFC (0x3F*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer12 = puVar2; // +0x120 (0x48*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer13 = puVar2; // +0x124 (0x49*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer14 = puVar2; // +0x128 (0x4A*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer15 = puVar2; // +0x12C (0x4B*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer16 = puVar2; // +0x130 (0x4C*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer17 = puVar2; // +0x138 (0x4E*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer18 = puVar2; // +0x13C (0x4F*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer19 = puVar2; // +0x150 (0x54*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer20 = puVar2; // +0x154 (0x55*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer21 = puVar2; // +0x158 (0x56*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer22 = puVar2; // +0x15C (0x57*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer23 = puVar2; // +0x2B0 (0xAC*4)
    *puVar2 = 0;

    puVar2 = (byte *)FUN_009c8e80(0x80);
    this->buffer24 = puVar2; // +0x16C (0x5B*4)
    *puVar2 = 0;

    *(byte *)&this->field_0x170 = 0; // +0x170 (0x5C*4) - byte
    this->field_0x174 = 0; // +0x174 (0x5D*4)

    DAT_011307f0 = 0; // global flag

    // Register matchmaking message strings (array of 3 char* at offset 0x5C)
    if ((uint)this->stringCount < 3) { // +0x68 (0x1A*4) - count
        this->messageStrings[this->stringCount] = "donmatch/acceptrequest"; // +0x5C (0x17*4) base
        this->stringCount = this->stringCount + 1;
    }
    if ((uint)this->stringCount < 3) {
        this->messageStrings[this->stringCount] = "donmatch/cancelrequest";
        this->stringCount = this->stringCount + 1;
    }
    if ((uint)this->stringCount < 3) {
        this->messageStrings[this->stringCount] = "donmatch/joinrequest";
        this->stringCount = this->stringCount + 1;
    }

    // Set a callback function pointer in some global structure
    *(code **)(DAT_01223484 + 0x20) = FUN_00965330;

    DAT_011308b5 = 0; // another global flag

    return this;
}