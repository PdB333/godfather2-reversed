// FUNC_NAME: NetReflectable::registerFields

// External functions for field registration and initialization.
// FUN_005c01d0 likely binds an offset within a class to a global descriptor (field name/type).
// FUN_005c1740 initializes some global state.
void __fastcall FUN_005c1740();
void __fastcall FUN_005c01d0(const void* descriptor, void* fieldPtr, int size, void* callback, int unk1, int unk2);

// External symbol addresses for field descriptors (likely string constants).
extern const char DAT_00d85738[];
extern const char DAT_00d85730[];
extern const char DAT_00d85728[];
extern const char DAT_00d85720[];
extern const char DAT_00d85718[];
extern const char DAT_00d85710[];
extern const char DAT_00d85708[];
extern const char DAT_00d85700[];
extern const char DAT_00d856f8[];
extern const char DAT_00d856f0[];
extern const char DAT_00e41d5c[];
extern const char DAT_00d856e8[];
extern const char DAT_00d856e0[];
extern const char DAT_00d856d8[];
extern const char DAT_00e3d6f8[];
extern const char DAT_00d856d4[];
extern const char DAT_00d856d0[];
extern const char DAT_00d856cc[];
extern const char DAT_00d856c8[];
extern const char DAT_00d856c4[];
extern const char DAT_00d856c0[];
extern const char DAT_00d856bc[];
extern const char DAT_00d83f88[];

// A callback function for the last field (likely change notification or validation).
void __stdcall LAB_009193b0(void* fieldPtr); // placeholder, actual signature may vary

void __fastcall NetReflectable::registerFields(NetReflectable* thisClass)
{
    // Initialization step (possibly entering a registration context).
    FUN_005c1740();

    // Register each field with its descriptor, offset, size, and flags.
    // Offsets are relative to the start of the class instance.
    // Most fields use size=1,2,4,6 and flags=0,0,1 (likely indicating "enabled" or "has default").
    // The last field uses a callback function for custom serialization/validation.

    // +0xbe: 2-byte field (likely a short integer, e.g., type or ID)
    FUN_005c01d0(&DAT_00d85738, (void*)((uint8_t*)thisClass + 0xbe), 2, 0, 0, 1);

    // +0xb4: 1-byte field (e.g., a flag or byte enumeration)
    FUN_005c01d0(&DAT_00d85730, (void*)((uint8_t*)thisClass + 0xb4), 1, 0, 0, 1);

    // +0xe4: 1-byte field
    FUN_005c01d0(&DAT_00d85728, (void*)((uint8_t*)thisClass + 0xe4), 1, 0, 0, 1);

    // +0xc4: 6-byte field (possibly a 3D vector with 2-byte float16, or a custom struct)
    FUN_005c01d0(&DAT_00d85720, (void*)((uint8_t*)thisClass + 0xc4), 6, 0, 0, 1);

    // +0xc8 (200 decimal): 1-byte field
    FUN_005c01d0(&DAT_00d85718, (void*)((uint8_t*)thisClass + 0xc8), 1, 0, 0, 1);

    // +0xcc: 6-byte field
    FUN_005c01d0(&DAT_00d85710, (void*)((uint8_t*)thisClass + 0xcc), 6, 0, 0, 1);

    // +0xc0: 1-byte field
    FUN_005c01d0(&DAT_00d85708, (void*)((uint8_t*)thisClass + 0xc0), 1, 0, 0, 1);

    // +0xd4: 1-byte field
    FUN_005c01d0(&DAT_00d85700, (void*)((uint8_t*)thisClass + 0xd4), 1, 0, 0, 1);

    // +0xd8: 4-byte field (likely an int or float)
    FUN_005c01d0(&DAT_00d856f8, (void*)((uint8_t*)thisClass + 0xd8), 4, 0, 0, 1);

    // +0xb8: 1-byte field
    FUN_005c01d0(&DAT_00d856f0, (void*)((uint8_t*)thisClass + 0xb8), 1, 0, 0, 1);

    // +0xdc: 1-byte field
    FUN_005c01d0(&DAT_00e41d5c, (void*)((uint8_t*)thisClass + 0xdc), 1, 0, 0, 1);

    // +0xe0: 1-byte field
    FUN_005c01d0(&DAT_00d856e8, (void*)((uint8_t*)thisClass + 0xe0), 1, 0, 0, 1);

    // +0xe8: 6-byte field
    FUN_005c01d0(&DAT_00d856e0, (void*)((uint8_t*)thisClass + 0xe8), 6, 0, 0, 1);

    // +0xec: 1-byte field
    FUN_005c01d0(&DAT_00d856d8, (void*)((uint8_t*)thisClass + 0xec), 1, 0, 0, 1);

    // +0xd0: 1-byte field
    FUN_005c01d0(&DAT_00e3d6f8, (void*)((uint8_t*)thisClass + 0xd0), 1, 0, 0, 1);

    // +0xf0: 6-byte field
    FUN_005c01d0(&DAT_00d856d4, (void*)((uint8_t*)thisClass + 0xf0), 6, 0, 0, 1);

    // +0xf4: 6-byte field
    FUN_005c01d0(&DAT_00d856d0, (void*)((uint8_t*)thisClass + 0xf4), 6, 0, 0, 1);

    // +0xf8: 6-byte field
    FUN_005c01d0(&DAT_00d856cc, (void*)((uint8_t*)thisClass + 0xf8), 6, 0, 0, 1);

    // +0xfc: 6-byte field
    FUN_005c01d0(&DAT_00d856c8, (void*)((uint8_t*)thisClass + 0xfc), 6, 0, 0, 1);

    // +0x100: 6-byte field
    FUN_005c01d0(&DAT_00d856c4, (void*)((uint8_t*)thisClass + 0x100), 6, 0, 0, 1);

    // +0x104: 6-byte field
    FUN_005c01d0(&DAT_00d856c0, (void*)((uint8_t*)thisClass + 0x104), 6, 0, 0, 1);

    // +0x108: 6-byte field
    FUN_005c01d0(&DAT_00d856bc, (void*)((uint8_t*)thisClass + 0x108), 6, 0, 0, 1);

    // +0x10c: 1-byte field with a callback (e.g., a change notification or custom serialization handler)
    FUN_005c01d0(&DAT_00d83f88, (void*)((uint8_t*)thisClass + 0x10c), 1, &LAB_009193b0, 0, 0);

    return;
}