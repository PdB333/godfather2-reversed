// FUN_004821d0: GameObject::GameObject
class GameObject {
public:
    void** vtable;                // +0x00
    uint32_t field_0x04;          // +0x04
    uint32_t field_0x08;          // +0x08
    uint32_t field_0x0C;          // +0x0C
    uint32_t field_0x10;          // +0x10
    GameObject* selfPtr;          // +0x14 – points to &field_0x28
    uint32_t field_0x18;          // +0x18
    // padding or unused at +0x1C, +0x20
    uint32_t field_0x24;          // +0x24
    void** derivedVtable;         // +0x28 – PTR_LAB_00e33620
    // padding at +0x2C
    void (*funcPtr)(void);        // +0x30 – LAB_00482410
    uint32_t field_0x34;          // +0x34
    // remaining up to size 0x40
};

void* __cdecl operator_new(uint32_t size); // FUN_009c8e50 (heap alloc)
void __cdecl staticInit(uint32_t arg);     // FUN_00452df0

GameObject* __thiscall GameObject::GameObject() {
    GameObject* obj = (GameObject*)operator_new(0x40);
    if (obj != nullptr) {
        obj->vtable = (void**)0x00e317dc;       // base vtable
        obj->field_0x04 = 0;
        obj->field_0x08 = 0;
        obj->field_0x10 = 1;
        obj->field_0x0C = 1;
        obj->selfPtr = (GameObject*)(&obj->derivedVtable); // points to +0x28
        obj->field_0x18 = 0;
        staticInit(0);                          // probably hooks into engine
        obj->field_0x24 = 1;
        obj->vtable = (void**)0x00e335b0;       // final vtable (overwrites base)
        obj->derivedVtable = (void**)0x00e33620;
        obj->funcPtr = (void (*)())0x00482410;
        obj->field_0x34 = 0;
        // field_0x1C, 0x20 left uninitialized (likely zero from allocator)
    }
    return obj;
}