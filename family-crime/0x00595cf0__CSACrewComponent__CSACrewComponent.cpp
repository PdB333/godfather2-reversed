// FUNC_NAME: CSACrewComponent::CSACrewComponent

// Reconstructed constructor for CSACrewComponent (EA Godfather 2, EARS engine)
// Called with __thiscall; param_3 and param_4 are initialization arguments.

class Component {
public:
    Component(); // base class constructor (FUN_0059b5e0)
};

class CSACrewComponent : public Component {
public:
    CSACrewComponent(int arg2, int arg3, int arg4); // arg2 unused
};

void __thiscall CSACrewComponent::CSACrewComponent(int this, int arg2, int arg3, int arg4) {
    // Call base component constructor
    Component::Component();

    // +0x70: first stored parameter (arg3)
    *(int*)(this + 0x70) = arg3;
    // +0x74: second stored parameter (arg4)
    *(int*)(this + 0x74) = arg4;
    // +0x78: int field, initialised to 0
    *(int*)(this + 0x78) = 0;
    // +0x80: short field, initialised to 0
    *(short*)(this + 0x80) = 0;
    // +0x82: short field, initialised to 0
    *(short*)(this + 0x82) = 0;
    // +0x88: int field, initialised to 0
    *(int*)(this + 0x88) = 0;
    // +0x86: short field, initialised to 0
    *(short*)(this + 0x86) = 0;
    // +0x7c: int field, initialised to 0
    *(int*)(this + 0x7c) = 0;
    // +0x84: short field, set to 4 (likely component type ID)
    *(short*)(this + 0x84) = 4;

    // Initialize two sub‑objects at offsets +0x8c and +0x98
    // The global manager at 0x012055A8 provides an initialisation function at vtable+0x34.
    // Signature: void __stdcall init(int arg1, int arg2, int arg3, void* addr)
    typedef void (__stdcall *SubInitFunc)(int, int, int, void*);
    int* globalVtable = *(int**)0x012055A8;
    SubInitFunc initSub = (SubInitFunc)(*(int*)((int)globalVtable + 0x34));
    initSub(0, 0, 0, (void*)(this + 0x8c));  // first sub‑object
    initSub(0, 0, 0, (void*)(this + 0x98)); // second sub‑object

    // +0xa4, +0xa8, +0xac: all set to 0
    *(int*)(this + 0xa4) = 0;
    *(int*)(this + 0xa8) = 0;
    *(int*)(this + 0xac) = 0;
}