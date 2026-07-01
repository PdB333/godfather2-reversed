// FUNC_NAME: ScoreDocument::ScoreDocument
// Function address: 0x00893BD0
// Role: Constructor for ScoreDocument class. Initializes vtable, registers message handlers for score events.
// Class derived from EARS::Framework::Object or similar message handler base.

typedef unsigned int uint;
typedef unsigned char uchar;

// Forward declares
class ScoreDocument;

// Global pointer to the singleton ScoreDocument instance
ScoreDocument* g_pScoreDocument = nullptr; // DAT_01129884

// Base vtable pointers (from PTR_FUN_00e2f19c and others)
extern void* PTR_FUN_00e2f19c;  // Base class vtable (e.g. Framework::Object)
extern void* PTR_LAB_00e30fe0;  // Secondary vtable
extern void* PTR_LAB_00d7782c;  // Another vtable
extern void* PTR_FUN_00d778a0;  // Derived class vtable (ScoreDocument)
extern void* PTR_LAB_00d77894;
extern void* PTR_LAB_00d77884;
extern void* PTR_LAB_00d77880;

// External functions (stubs - actual implementation unknown)
void __thiscall BaseObjectInit(); // FUN_0049c610 - initializes base object
void __cdecl RegisterMessageHash(void* callback, uint hash, uint param); // FUN_00463980
void __cdecl SetScoreCategory(const char* name, int weight); // FUN_0049c6e0
uint __cdecl GetMessageInterface(uint* outHandle, const char* messageName); // FUN_00408240 - returns handle
void __thiscall AddMessageListener(ScoreDocument* this, uint* handle, uint flags); // FUN_00408900

class ScoreDocument {
public:
    // Vtable pointer at +0x00 (multiple vtable assignments during construction)
    // Member fields:
    // +0x04: int field_4; set to 1 then later to 0? Actually after base init it's set to 1, then after derived init it's overwritten.
    // Better to treat as union or sequential assignments.
    // The decompiler shows param_1[1]=1 initially, then later *param_1 is overwritten but param_1[1] is not changed? Actually after setting *param_1 to new vtable, param_1[3] etc are set but param_1[1] remains 1? Possibly field_4 is an int flag.

    // Offsets based on assignment order:
    // +0x00: vtable (void*)
    // +0x04: some int (initially 1, then later? not overwritten)
    // +0x08: some int (0)
    // +0x0C: void* (set to PTR_LAB_00d77894 after derived init)
    // +0x10: void* (set to PTR_LAB_00d77884)
    // +0x14: void* (set to PTR_LAB_00d77880)
    // +0x18: int field_18 (0)
    // +0x1C: int field_1C (0)
    // +0x20: int field_20 (0)
    // +0x24: void* field_24 = param_2 (some parent/delegate)
    // +0x28: int field_28 (0)
    // +0x30: int field_30 (0) ??? actually param_1[0xb]=0 => offset 0x2C? Wait: param_1[0xb] is 11th element, offset 0x2C (11*4). But then later param_1[0xe] etc. Let's list:
    // param_1[0] = vtable
    // param_1[1] = 1
    // param_1[2] = 0
    // param_1[5] = PTR_LAB_00e30fe0 (before base init? Actually before base init)
    // param_1[6] = PTR_LAB_00d7782c
    // Then after base init:
    // *param_1 = PTR_FUN_00d778a0 (overwrites vtable)
    // param_1[3] = PTR_LAB_00d77894
    // param_1[5] = PTR_LAB_00d77884
    // param_1[6] = PTR_LAB_00d77880
    // param_1[7] = 0
    // param_1[8] = 0
    // param_1[9] = 0
    // param_1[10] = param_2
    // param_1[0xb] = 0  (0x2C)
    // param_1[0xe] = 0  (0x38)
    // param_1[0xf] = 0  (0x3C)
    // param_1[0x10] = 0 (0x40)
    // *(uint8*)(param_1+0x11) = 0  (0x44) - single byte
    // param_1[0x12] = 0 (0x48)
    // param_1[0x13] = 0 (0x4C)
    // param_1[0x14] = 0 (0x50)
    // then later:
    // param_1[0xd] = param_4 (0x34)
    // param_1[0xc] = 0 (0x30)

    // So we have many fields. Not all used. We'll model as a struct with explicit offsets.

    // The key is to reconstruct the constructor logic.

    ScoreDocument(void* parent, uint param3, void* param4) {
        // Initial base class vtable setup
        this->vtable = &PTR_FUN_00e2f19c;
        this->field_4 = 1;
        this->field_8 = 0;

        // Call base class initialization
        BaseObjectInit(); // FUN_0049c610

        // Set more base vtables (for multiple inheritance or interface)
        this->field_14 = &PTR_LAB_00e30fe0;  // Actually param_1[5] = this at offset 0x14
        this->field_18 = &PTR_LAB_00d7782c;  // offset 0x18

        // Store global singleton
        g_pScoreDocument = this;

        // Now set derived class vtable
        this->vtable = &PTR_FUN_00d778a0;    // overwrite vtable
        this->field_C = &PTR_LAB_00d77894;   // offset 0x0C
        this->field_14 = &PTR_LAB_00d77884;  // offset 0x14 (overwrites previous)
        this->field_18 = &PTR_LAB_00d77880;  // offset 0x18 (overwrites)

        // Initialize many fields to zero
        this->field_1C = 0;       // offset 0x1C
        this->field_20 = 0;       // offset 0x20
        this->field_24 = 0;       // offset 0x24
        this->parent = parent;    // offset 0x28 (param_2)
        this->field_2C = 0;       // offset 0x2C (param_1[0xb])
        this->field_38 = 0;       // offset 0x38
        this->field_3C = 0;       // offset 0x3C
        this->field_40 = 0;       // offset 0x40
        this->field_44_byte = 0;  // offset 0x44 (byte)
        this->field_48 = 0;       // offset 0x48
        this->field_4C = 0;       // offset 0x4C
        this->field_50 = 0;       // offset 0x50

        // Call virtual function at index 2 (offset 8) on parent object (assumes parent vtable has function)
        (**(code**)(*(int*)parent + 8))(); // probably "Initialize" or "AddRef"

        // Register message handler for score document
        // This likely registers a callback using the object's own vtable or a member function
        RegisterMessageHash(this->field_14 /* callback? */, 0x23aea276, param_3);

        // Set up "Score" category
        SetScoreCategory("Score", 1);

        // Register for "iMsgScoreDocumentLoaded" message
        uint handleScoreDocLoaded = 0;
        GetMessageInterface(&handleScoreDocLoaded, "iMsgScoreDocumentLoaded");
        if (handleScoreDocLoaded != 0) {
            AddMessageListener(this, &handleScoreDocLoaded, 0x8000);
        }

        // Register for score update messages (DAT_0112fe10 and DAT_0112fe38 are global handles)
        if (g_scoreDocumentLoadedHandle != 0) {  // DAT_0112fe38
            AddMessageListener(this, &g_scoreDocumentLoadedHandle, 0x8000);
        }
        if (g_scoreUpdateHandle != 0) {  // DAT_0112fe10
            AddMessageListener(this, &g_scoreUpdateHandle, 0x8000);
        }

        // Store param4 (likely a callback or initial data)
        this->field_34 = param4;  // offset 0x34 (param_1[0xd])
        this->field_30 = 0;       // offset 0x30 (param_1[0xc])

        // Register for minor accomplishment and discovery accomplishment messages
        uint handleMinor = 0;
        GetMessageInterface(&handleMinor, "iMsgMinorAccomplishment");
        if (handleMinor != 0) {
            AddMessageListener(this, &handleMinor, 0x8000);
        }

        uint handleDiscovery = 0;
        GetMessageInterface(&handleDiscovery, "iMsgDiscoveryAccomplishment");
        if (handleDiscovery != 0) {
            AddMessageListener(this, &handleDiscovery, 0x8000);
        }
    }

private:
    // Field offsets as per decompiler
    // +0x00
    void* vtable;
    // +0x04
    int field_4;
    // +0x08
    int field_8;
    // +0x0C
    void* field_C;
    // +0x10 (not explicitly set, but 0x10 is set from param_1[4]? Actually param_1[4] is never assigned, so maybe padding)
    // +0x14
    void* field_14;
    // +0x18
    void* field_18;
    // +0x1C
    int field_1C;
    // +0x20
    int field_20;
    // +0x24
    int field_24;
    // +0x28
    void* parent;
    // +0x2C
    int field_2C;
    // +0x30
    int field_30;
    // +0x34
    void* field_34;
    // +0x38
    int field_38;
    // +0x3C
    int field_3C;
    // +0x40
    int field_40;
    // +0x44
    uchar field_44_byte;
    // +0x48
    int field_48;
    // +0x4C
    int field_4C;
    // +0x50
    int field_50;
};

// Global handles for score messages
uint g_scoreDocumentLoadedHandle = 0; // DAT_0112fe38
uint g_scoreUpdateHandle = 0;         // DAT_0112fe10
uint g_scoreDocLoadedInterface = 0;   // DAT_0112e308
uint g_minorAccomplishmentHandle = 0; // DAT_0112e300
uint g_discoveryAccomplishmentHandle = 0; // DAT_0112e2f8

// The actual constructor implementation (address 0x00893BD0)
// This is reconstructed based on the decompiled output with meaningful names.
// Note: The exact class layout might vary, but this captures the logic.
undefined4* __thiscall ScoreDocument_constructor(ScoreDocument* this, void* parent, uint param3, void* param4) {
    this->vtable = &PTR_FUN_00e2f19c;
    this->field_4 = 1;
    this->field_8 = 0;
    BaseObjectInit();
    this->field_14 = &PTR_LAB_00e30fe0;
    this->field_18 = &PTR_LAB_00d7782c;
    g_pScoreDocument = this;
    this->vtable = &PTR_FUN_00d778a0;
    this->field_C = &PTR_LAB_00d77894;
    this->field_14 = &PTR_LAB_00d77884;
    this->field_18 = &PTR_LAB_00d77880;
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_24 = 0;
    this->parent = parent;
    this->field_2C = 0;
    this->field_38 = 0;
    this->field_3C = 0;
    this->field_40 = 0;
    this->field_44_byte = 0;
    this->field_48 = 0;
    this->field_4C = 0;
    this->field_50 = 0;
    // Call virtual function on parent (assumed to be a virtual call)
    (**(code**)(*(int*)parent + 8))();
    // Register message handler with hash
    RegisterMessageHash(this->field_14, 0x23aea276, param3);
    SetScoreCategory("Score", 1);
    // Register for score document loaded
    uint handle1 = 0;
    GetMessageInterface(&handle1, "iMsgScoreDocumentLoaded");
    if (handle1 != 0) {
        AddMessageListener(this, &handle1, 0x8000);
    }
    // Register for global score update handles
    if (g_scoreDocumentLoadedHandle != 0) {
        AddMessageListener(this, &g_scoreDocumentLoadedHandle, 0x8000);
    }
    if (g_scoreUpdateHandle != 0) {
        AddMessageListener(this, &g_scoreUpdateHandle, 0x8000);
    }
    this->field_34 = param4;
    this->field_30 = 0;
    // Register for minor accomplishment
    uint handle2 = 0;
    GetMessageInterface(&handle2, "iMsgMinorAccomplishment");
    if (handle2 != 0) {
        AddMessageListener(this, &handle2, 0x8000);
    }
    // Register for discovery accomplishment
    uint handle3 = 0;
    GetMessageInterface(&handle3, "iMsgDiscoveryAccomplishment");
    if (handle3 != 0) {
        AddMessageListener(this, &handle3, 0x8000);
    }
    return (undefined4*)this;
}