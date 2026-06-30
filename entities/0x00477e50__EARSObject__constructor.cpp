// FUNC_NAME: EARSObject::constructor

extern void BaseConstructorCall(uint32_t* global);
extern void SubObjectInit(void* thisSub);
extern void GlobalInitFunc();
extern uint32_t g_globalData; // DAT_01223410
extern uint32_t g_baseGlobal; // DAT_0120e93c
extern void* g_vtableMain;  // PTR_FUN_00e32f6c
extern void* g_vtableExtra1; // PTR_LAB_00e32f88
extern void* g_vtableExtra2; // PTR_LAB_00e32f98

class EARSObject {
public:
    void** vtable;            // +0x00
    char pad_4[0x38];         // +0x04 to +0x3B
    void* extraVtable1;       // +0x3C (param_1[0xF])
    char pad_40[0x08];        // +0x40 to +0x47
    void* extraVtable2;       // +0x48 (param_1[0x12])
    char subObject[4];        // +0x14 sub-object placeholder

    __thiscall EARSObject* constructor(uint8_t flags);
};

__thiscall EARSObject* EARSObject::constructor(uint8_t flags) {
    // Set main vtable pointer
    vtable = &g_vtableMain;

    // Set additional vtable pointers for extended interfaces
    extraVtable1 = &g_vtableExtra1;  // param_1[0xF]
    extraVtable2 = &g_vtableExtra2;  // param_1[0x12]

    // Call base class initializer (global object)
    BaseConstructorCall(&g_baseGlobal);

    // Initialize sub-object at offset 0x14
    SubObjectInit(this->subObject);

    // Global initialization routine
    GlobalInitFunc();

    // If bit 0 of flags is set, call virtual function from global vtable
    if ((flags & 1) != 0) {
        // Get global struct pointer from +0x2D4 offset
        uint32_t* globalStruct = *(uint32_t**)(g_globalData + 0x2D4);
        // Fetch function at index 1 (offset +4) of that struct's vtable
        void (__thiscall *func)(EARSObject*, int) = 
            (void (__thiscall *)(EARSObject*, int))(*(uint32_t*)(*globalStruct) + 4);
        func(this, 0);
    }

    return this;
}