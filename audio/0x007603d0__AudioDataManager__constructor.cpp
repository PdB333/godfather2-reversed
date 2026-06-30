// FUNC_NAME: AudioDataManager::constructor
// Function at 0x007603d0 - Constructor for AudioDataManager class.
// Initializes base class, sets vtable pointers, zeros many fields, and allocates a sub-object.

class AudioDataManager {
public:
    // vtable for this class (at +0x00)
    void** vtable;

    // Base class fields up to offset 0x5C (index 0x17) contain a pointer to some structure.
    // That structure has a field at +0x5C4 which is used below.
    void* somePointer; // at +0x5C

    // Fields at offsets 0x70-0x88 (indices 0x1c-0x22) are zeroed.
    int field_0x70;   // +0x70
    int field_0x74;   // +0x74
    int field_0x78;   // +0x78
    int field_0x7C;   // +0x7C
    int field_0x80;   // +0x80
    int field_0x84;   // +0x84
    int field_0x88;   // +0x88

    // Secondary vtable pointer at +0x8C (index 0x23)
    void** secondaryVtable; // +0x8C

    // More fields at +0x90, +0x94, +0x98 (byte), +0x9C, +0xA0, +0xA4
    int field_0x90;   // +0x90
    int field_0x94;   // +0x94
    char field_0x98;  // +0x98
    int field_0x9C;   // +0x9C
    int field_0xA0;   // +0xA0
    int field_0xA4;   // +0xA4

    // Flags (short) at +0xA8 (index 0x2a)
    short flags;      // +0xA8, set to 0xC000

    // Value from somePointer+0x5C4 at +0xAC (index 0x2b)
    uint field_0xAC;  // +0xAC

    // Zeros at +0xB0, +0xB4, +0xB8, +0xBC (indices 0x2c-0x2f)
    int field_0xB0;   // +0xB0
    int field_0xB4;   // +0xB4
    int field_0xB8;   // +0xB8
    int field_0xBC;   // +0xBC

    // Sub-object pointer at +0xC0 (index 0x30)
    void* subObject;  // +0xC0

    // Constructor
    AudioDataManager(uint param_2, uint param_3) {
        // Call base class constructor (address 0x0073e160)
        // Base class takes two parameters (likely related to parent object)
        FUN_0073e160(param_2, param_3);

        // Set vtable for AudioDataManager
        vtable = &PTR_LAB_00d6541c;

        // Zero out fields 0x70-0x88
        field_0x70 = 0;
        field_0x74 = 0;
        field_0x78 = 0;
        field_0x7C = 0;
        field_0x80 = 0;
        field_0x84 = 0;
        field_0x88 = 0;

        // Set secondary vtable pointer at +0x8C
        secondaryVtable = &PTR_FUN_00d64720;

        // Zero more fields
        field_0x90 = 0;
        field_0x94 = 0;
        field_0x98 = 0;
        field_0x9C = 0;
        field_0xA0 = 0;
        field_0xA4 = 0;

        // Set flags short to 0xC000
        flags = 0xC000;

        // Fetch value from somePointer + 0x5C4
        uint uVar1 = *(uint*)((char*)somePointer + 0x5C4);
        field_0xAC = uVar1;

        // Zero remaining fields
        field_0xB0 = 0;
        field_0xB4 = 0;
        field_0xB8 = 0;
        field_0xBC = 0;

        // Allocate and construct a sub-object (0x34 bytes)
        FUN_007f63e0(0x34);  // Likely allocates memory
        subObject = FUN_0072fa80();  // Construct and return pointer
    }
};