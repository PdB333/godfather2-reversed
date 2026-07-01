// FUNC_NAME: SentientComponent::constructor(uint8_t param_2)
// Address: 0x00904fe0
// Role: Constructor for SentientComponent (EARS engine component)
// Object size: 100 bytes (0x64) inferred from operator delete call
// Offsets:
//   +0x00: m_vtable (main vtable pointer)
//   +0x20: m_subObject (sub-component, initialized by FUN_00904b60)
//   +0x3C: m_secondaryVtable (vtable pointer for secondary base)
//   +0x48: m_tertiaryVtable (vtable pointer for tertiary base)

extern void* g_someGlobal;    // DAT_01218060
extern void* g_otherGlobal;   // DAT_0112ff38

extern void __stdcall globalInit(void*);   // FUN_004086d0
extern bool  __thiscall initSubObject(void*); // FUN_00904b60
extern void __stdcall cleanupGlobal(void*);  // FUN_00408310
extern void __cdecl doSomethingElse();       // FUN_00477eb0
extern void __cdecl operatorDelete(void*, size_t); // FUN_0043b960

class SentientComponent {
public:
    void* m_vtable;              // +0x00
    // ... other fields ...
    // Sub-object at +0x20
    char m_subObject[12];        // +0x20 placeholder for sub-component
    // ... more fields ...
    void* m_secondaryVtable;     // +0x3C
    void* m_tertiaryVtable;      // +0x48
    // ... remaining data up to 100 bytes
};

void __thiscall SentientComponent::constructor(uint8_t param_2) {
    // Set up virtual function tables
    this->m_vtable = &PTR_FUN_00d82274;          // Main vtable
    this->m_secondaryVtable = &PTR_LAB_00d82264;  // Secondary vtable
    this->m_tertiaryVtable = &PTR_LAB_00d82260;   // Tertiary vtable

    // Initialize global singleton
    globalInit(&g_someGlobal);

    // Initialize sub-object at offset +0x20
    bool success = initSubObject(&this->m_subObject);
    if (success) {
        cleanupGlobal(&g_otherGlobal);
    }

    // Perform additional global initialization
    doSomethingElse();

    // If bit 0 of param_2 is set, free this object using custom operator delete
    if ((param_2 & 1) != 0) {
        operatorDelete(this, 100);
    }
}