// FUNC_NAME: GameStateManager::initialize (or some unknown class constructor)
// Reconstructed from 0x007e2e90
// This function appears to be a constructor for a complex game state manager.
// It initializes multiple subsystems by allocating and storing their pointers,
// sets up virtual function tables, and loads an initial vector data.

undefined4* __thiscall GameStateManager::initialize(GameStateManager* this, undefined4 param2, undefined4 param3)
{
    int* piVar1;
    undefined4 result;
    undefined8* puVar3;
    undefined4 local_14;
    undefined4 local_10;
    undefined4 local_c;

    // Call base class constructor (likely EARSObject or similar)
    BaseClass_Constructor(param2, param3);  // FUN_007ab5e0

    // Setup virtual function table pointers
    this->field_0x74 = &PTR_FUN_00e32808;  // +0x74 (word offset 0x1d)
    this->field_0x78 = 0;                   // +0x78
    *this = &PTR_LAB_00d6f9bc;             // Primary vtable
    this->field_0x74 = &PTR_LAB_00d6f9b8;  // Override +0x74
    this->field_0x7c = 0;                   // +0x7c
    this->field_0x84 = 0;                   // +0x84
    this->field_0x88 = 0;                   // +0x88
    this->field_0x8c = 0;                   // +0x8c
    this->field_0x90 = 0;                   // +0x90
    this->field_0x94 = 0;                   // +0x94
    this->field_0x98 = 0;                   // +0x98

    // Initialize first component (e.g., a transform or state)
    local_14 = 0;
    local_10 = 0;
    local_c = 0;
    piVar1 = (int*)FUN_004dddd0();          // Allocate memory (new? malloc?)
    result = FUN_004265d0(&local_14, piVar1); // Assign reference (maybe from a pool)
    this->field_0xa4 = result;              // +0xa4
    this->field_0xa8 = piVar1;              // +0xa8
    (**(code**)(*piVar1 + 8))();            // Call virtual function at index 2 on the new object

    this->field_0x9c = 0;                   // +0x9c
    this->field_0x98 = 0;                   // +0x98 (overwrites previous? maybe different fields)
    this->field_0xa0 = 0;                   // +0xa0

    // Initialize second component
    local_14 = 0;
    local_10 = 0;
    local_c = 0;
    piVar1 = (int*)FUN_004dddd0();
    result = FUN_004265d0(&local_14, piVar1);
    this->field_0xb8 = result;              // +0xb8
    this->field_0xbc = piVar1;              // +0xbc
    (**(code**)(*piVar1 + 8))();

    this->field_0xb0 = 0;                   // +0xb0
    this->field_0xac = 0;                   // +0xac
    this->field_0xb4 = 0;                   // +0xb4

    // Initialize third component
    local_14 = 0;
    local_10 = 0;
    local_c = 0;
    piVar1 = (int*)FUN_004dddd0();
    result = FUN_004265d0(&local_14, piVar1);
    this->field_0xcc = result;              // +0xcc
    this->field_0xd0 = piVar1;              // +0xd0
    (**(code**)(*piVar1 + 8))();

    this->field_0xc4 = 0;                   // +0xc4
    this->field_0xc0 = 0;                   // +0xc0
    this->field_0xc8 = 0;                   // +0xc8

    // Clear more fields
    this->field_0xd4 = 0;                   // +0xd4
    this->field_0xd8 = 0;                   // +0xd8
    this->field_0xdc = 0;                   // +0xdc
    this->field_0xe0 = 0;                   // +0xe0
    this->field_0xe4 = 0;                   // +0xe4
    this->field_0xe8 = 0;                   // +0xe8
    this->field_0xec = 0;                   // +0xec
    this->field_0xf0 = 0;                   // +0xf0

    // Conditionally assign a value from global data
    if (this->field_0x58 == 0) {            // +0x58 (word offset 0x16)
        result = 0;
    }
    else {
        result = FUN_0043b870(DAT_01130fb0); // Some function with global data
    }
    this->field_0xf4 = result;              // +0xf4

    // Call init functions (maybe start timers or reset states)
    FUN_007e2cc0();
    FUN_007e2cc0();

    // Clear a byte at offset 0x80 and 0x81
    *(undefined1*)(&this->field_0x80) = 0;  // byte at +0x80
    *(undefined1*)((int)this + 0x81) = 0;   // byte at +0x81

    // Free a previously allocated pointer if not null
    piVar1 = &this->field_0x84;             // +0x84 (same as field earlier)
    if (*piVar1 != 0) {
        FUN_004daf90(piVar1);               // Deallocate
        *piVar1 = 0;
    }

    // Set some configuration values
    FUN_007e25b0(0x200);                    // e.g., max units = 512?
    FUN_007e26f0(0x100);                    // e.g., max something = 256?

    // Load initial data from a resource (maybe a vector/quaternion)
    puVar3 = (undefined8*)FUN_00540bf0(2, 0, 0x60736, 0xffffffff, 0, 0); // Load resource ID 0x60736
    *(undefined8*)(&this->field_0xe0) = *puVar3;        // First 8 bytes to +0xe0
    *(undefined8*)(&this->field_0xe8) = puVar3[1];      // Next 8 bytes to +0xe8
    this->field_0xf0 = *(undefined4*)(puVar3 + 2);      // Last 4 bytes to +0xf0

    return this;
}