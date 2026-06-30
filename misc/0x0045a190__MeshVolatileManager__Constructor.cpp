// FUNC_NAME: MeshVolatileManager::Constructor
class MeshVolatileManager {
public:
    // +0x00: vtable pointer for primary class
    void* vtable1;
    // +0x04: some flag or counter (initialized to 0)
    int field_04;
    // +0x08: second vtable pointer (multiple inheritance / interface)
    void* vtable2;

    // Static singleton pointer
    static MeshVolatileManager* s_instance; // originally DAT_01223458

    // Constructor (called with this in ECX)
    void __fastcall Constructor() {
        field_04 = 0;                                          // param_1[1] = 0
        vtable2 = &PTR_LAB_00e31b10;                           // initial base vtable at +0x08
        s_instance = this;                                     // store singleton
        vtable1 = &PTR_FUN_00e31b00;                           // primary vtable at +0x00
        vtable2 = &PTR_LAB_00e31b0c;                           // override vtable at +0x08 (derived interface)

        // Register the base class type (DAT_00e31ae4 likely a type descriptor)
        registerClass(&DAT_00e31ae4, 1);                       // FUN_0049c6e0(&DAT_00e31ae4,1)
        // Register the "MeshVolatile" class name with the engine
        registerClass("MeshVolatile", 1);                      // FUN_0049c6e0("MeshVolatile",1)
    }
};

// Static member definition
MeshVolatileManager* MeshVolatileManager::s_instance = nullptr; // corresponds to DAT_01223458

// Function pointer at address 0x0049c6e0 – assumed to register a class/type with the engine
extern void __fastcall registerClass(void* typeInfo, int flag);
extern void __fastcall registerClass(const char* name, int flag);