// FUNC_NAME: RimLightingTODManager::constructor

class RimLightingTODManager {
public:
    // vtable pointer at offset 0x00
    void* vtable;
    
    // Offset 0x04 to 0x1C (7 uint32): flags/state
    uint32 field_04;
    uint32 field_08;
    uint32 field_0C;   // Will be set to string handle
    uint32 field_10;   // String pointer (maybe null)
    uint32 field_14;
    uint32 field_18;
    uint32 field_1C;
    
    // Offset 0x20: byte flag
    uint8 field_20;     // Set to 1
    uint8 pad_21[3];    // padding to align
    
    // Offset 0x24: uint32 flag
    uint32 field_24;    // Set to 1
    
    // Offset 0x28: additional vtable? (0x2C)
    void* vtable2;      // PTR_LAB_00d73454
    
    // Offset 0x30 to 0x3C: four global constants (colors?)
    uint32 constant0;   // DAT_00d5d7b8
    uint32 constant1;   // DAT_00e44620
    uint32 constant2;   // DAT_00d5ef88
    uint32 constant3;   // DAT_00e44980
    
    // Offset 0x40 to 0x5C: array of 8 values (all same global)
    uint32 valueArray[8]; // ._DAT_00d5780c repeated
    
    // Offset 0x60: function pointer
    void* funcPtr;      // PTR_FUN_00d7381c
    
    // Offset 0x64: flag
    uint32 field_64;    // 0
    
    // Offset 0x68: allocated buffer (0x40 bytes)
    void* buffer;       // Allocated by FUN_009c8e80(0x40)
    
    // Offset 0x6C: another flag
    uint32 field_6C;    // 0
    
    // Offset 0x70: buffer size? (0x10)
    uint32 bufferSize;  // 0x10
    
    // Offset 0x74+: possibly more fields (not initialized here)
};

// This is a constructor that initializes a RimLightingTODManager object.
// It sets default values, registers a message handler for "RimLightingTODMessage" with "Sequence" type,
// and allocates a small buffer.
RimLightingTODManager* __fastcall RimLightingTODManager_constructor(RimLightingTODManager* thisPtr) {
    uint32 uVar1;
    uint8* puVar2;
    struct SomeRegistrationStruct { uint32 a, b, c; void* dtor; } reg; // Local struct for registration
    
    // Zero out fields from offset 0x04 to 0x1C (7 dwords)
    thisPtr->field_04 = 0;
    thisPtr->field_08 = 0;
    thisPtr->field_0C = 0;
    thisPtr->field_10 = 0;
    thisPtr->field_14 = 0;
    thisPtr->field_18 = 0;
    thisPtr->field_1C = 0;
    
    // Set byte flag at offset 0x20 to 1
    thisPtr->field_20 = 1;
    
    // Set vtable pointer
    thisPtr->vtable = &PTR_FUN_00d73820;  // Address 0x00d73820
    
    // Set another flag at offset 0x24 to 1
    thisPtr->field_24 = 1;
    
    // Call some initialization function (probably random seeding or time init)
    FUN_008334a0();
    
    // Read global value _DAT_00d5780c (likely a color or light constant)
    uVar1 = _DAT_00d5780c;
    
    // Set vtable2 pointer at offset 0x2C
    thisPtr->vtable2 = &PTR_LAB_00d73454;
    
    // Fill array at offset 0x40 (8 dwords) with the same global value
    thisPtr->valueArray[0] = uVar1;
    thisPtr->valueArray[1] = uVar1;
    thisPtr->valueArray[2] = uVar1;
    thisPtr->valueArray[3] = uVar1;
    thisPtr->valueArray[4] = uVar1;
    thisPtr->valueArray[5] = uVar1;
    thisPtr->valueArray[6] = uVar1;
    thisPtr->valueArray[7] = uVar1;
    
    // Set four constants at offset 0x30-0x3C from global DATs
    thisPtr->constant0 = DAT_00d5d7b8;
    thisPtr->constant1 = DAT_00e44620;
    thisPtr->constant2 = DAT_00d5ef88;
    thisPtr->constant3 = DAT_00e44980;
    
    // Set function pointer at offset 0x60
    thisPtr->funcPtr = &PTR_FUN_00d7381c;
    
    // Clear flag at offset 0x64
    thisPtr->field_64 = 0;
    
    // Allocate a buffer of 0x40 bytes (e.g., for temporary data)
    thisPtr->buffer = FUN_009c8e80(0x40);
    
    // Initialize remaining fields
    thisPtr->field_6C = 0;
    thisPtr->bufferSize = 0x10;  // Possibly maximum size or count
    
    // Prepare registration structure (local stack)
    reg.a = 0;
    reg.b = 0;
    reg.c = 0;
    reg.dtor = nullptr;
    
    // Register a "RimLightingTODMessage" handler of type "Sequence"
    // FUN_004d4ad0 likely constructs a registration object
    FUN_004d4ad0(&reg, &DAT_00e2f0b0, "RimLightingTODMessage", "Sequence");
    // FUN_004d3e20 probably finalizes registration (e.g., insert into linked list)
    FUN_004d3e20(&reg);
    
    // Now read the string pointer at offset 0x10; if null, use a default string constant
    puVar2 = (uint8*)thisPtr->field_10;
    if (puVar2 == nullptr) {
        puVar2 = &DAT_0120546e;  // Default string (maybe an empty string or "default")
    }
    // FUN_004dafd0 likely computes a hash or stores the string; store result at offset 0x0C
    thisPtr->field_0C = FUN_004dafd0(puVar2);
    
    // If registration succeeded (reg.a != 0), call the destructor stored in reg.dtor
    if (reg.a != 0) {
        ((void (*)(uint32))reg.dtor)(reg.a);
    }
    
    return thisPtr;
}