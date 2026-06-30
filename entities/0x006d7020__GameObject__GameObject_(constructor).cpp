// FUNC_NAME: GameObject::GameObject (constructor)

class GameObject {
public:
    // Offset comments in 4-byte units (except where noted)
    // +0x00: vtable pointer for primary interface (PTR_FUN_00d5f500)
    // +0x08: vtable pointer for secondary interface (PTR_LAB_00d5f4f8)
    // +0x1D8 (0x76*4): some integer flag
    // +0x1DC (0x77*4): ...
    // ... many zero-initialized fields
    // +0x22C (0x8b*4): first of a triple (field_0x8b, field_0x8c, field_0x8d)
    // +0x230 (0x8c*4): initialized from global DAT_00d5d740
    // +0x238 (0x8e*4): byte field (zeroed as byte)
    // +0x260 (0x98*4): pointer to a sub-object (checked and cleaned)

    // Constructor: takes a parameter (likely a name or config)
    GameObject(void* param2) {
        // Copy or initialize internal name using global string
        FUN_006c9760(param2, DAT_00d5cf70);

        // Set vtable pointers
        this->vtable[0] = &PTR_FUN_00d5f500;   // primary vtable
        this->vtable[2] = &PTR_LAB_00d5f4f8;   // secondary vtable

        // Construct two internal sub-objects
        FUN_006d69c0();
        FUN_006d69c0();

        // Capture global value for field_0x8c
        int uVar2 = DAT_00d5d740;

        // Zero-initialize many status/configuration fields
        field_0x8b = 0;            // +0x22C
        field_0x8c = uVar2;        // +0x230
        field_0x8d = 0;            // +0x234
        field_0x76 = 0;            // +0x1D8
        *(uint8*)((uint8*)this + 0x238) = 0; // byte at +0x238 (0x8e*4)

        field_0x98 = 0;            // +0x260
        field_0x99 = 0;            // +0x264

        // Zero-initialize many more fields (offsets in 4-byte units)
        this->data[0x3e] = 0;      // +0xF8
        this->data[0x3f] = 0;      // +0xFC
        this->data[0x40] = 0;      // +0x100
        this->data[0x41] = 0;      // +0x104
        this->data[0x42] = 0;      // +0x108
        this->data[0x4d] = 0;      // +0x134
        this->data[0x4e] = 0;      // +0x138
        this->data[0x51] = 0;      // +0x144
        this->data[0x50] = 0;      // +0x140
        this->data[0x4f] = 0;      // +0x13C
        this->data[0x79] = 0;      // +0x1E4
        this->data[0x78] = 0;      // +0x1E0
        this->data[0x77] = 0;      // +0x1DC
        this->data[0x7c] = 0;      // +0x1F0
        this->data[0x7b] = 0;      // +0x1EC
        this->data[0x7a] = 0;      // +0x1E8
        this->data[0x7f] = 0;      // +0x1FC
        this->data[0x7e] = 0;      // +0x1F8
        this->data[0x7d] = 0;      // +0x1F4
        // piVar1 = &field_0x98  (was used for cleanup)
        this->data[0x82] = 0;      // +0x208
        this->data[0x81] = 0;      // +0x204
        this->data[0x80] = 0;      // +0x200
        this->data[0x8f] = 0;      // +0x23C
        this->data[0x90] = 0;      // +0x240
        this->data[0x91] = 0;      // +0x244
        *(uint8*)((uint8*)this + 0x248) = 0; // byte at +0x248 (0x92*4)
        this->data[0x89] = 0;      // +0x224
        this->data[0x8a] = 0;      // +0x228
        this->data[0x93] = 0;      // +0x24C
        this->data[0x94] = 0;      // +0x250
        this->data[0x96] = 0;      // +0x258
        this->data[0x97] = 0;      // +0x25C

        // If pointer at offset 0x98 is non-null, free and clear it
        if (field_0x98 != 0) {
            FUN_004daf90(&field_0x98);  // custom deallocation function
            field_0x98 = 0;
        }

        // More zeroing after the cleanup
        this->data[0x83] = 0;      // +0x20C
        this->data[0x84] = 0;      // +0x210
        this->data[0x85] = 0;      // +0x214
        this->data[0x86] = 0;      // +0x218
        this->data[0x87] = 0;      // +0x21C
        this->data[0x88] = 0;      // +0x220
    }

private:
    // Simplified representation – actual layout is large
    // In real code, these would be structured members
    int* vtable[3];                // at least 3 vtable slots used
    int data[0x100];               // placeholder for many fields

    // Named fields for clarity (offsets from this)
    int& field_0x8b = data[0x8b]; // +0x22C
    int& field_0x8c = data[0x8c]; // +0x230
    int& field_0x8d = data[0x8d]; // +0x234
    int& field_0x76 = data[0x76]; // +0x1D8
    int& field_0x98 = data[0x98]; // +0x260 (pointer)
    int& field_0x99 = data[0x99]; // +0x264
};

// External functions and globals referenced
extern void FUN_006c9760(void*, int); // initialize from global string
extern int DAT_00d5cf70;              // global string/path
extern int DAT_00d5d740;              // global value for field_0x8c
extern int PTR_FUN_00d5f500;          // primary vtable symbol
extern int PTR_LAB_00d5f4f8;          // secondary vtable symbol
extern void FUN_006d69c0();           // sub-object constructor
extern void FUN_004daf90(int*);       // deallocation/cleanup function