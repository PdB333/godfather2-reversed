// FUNC_NAME: GameObject::constructor
#define VTABLE_PTR 0x00d8314c

struct GameObjectVTable {
    // virtual functions
};

struct GameObject {
    GameObjectVTable* vtable;            // +0x00
    void* field_0x3C;                    // +0x3C
    void* field_0x48;                    // +0x48
    uint8_t byteField50;                 // +0x50
    int intField60;                      // +0x60
    short shortField64;                 // +0x64
    short shortField66;                 // +0x66
};

// External base class constructor
void __thiscall BaseClassConstructor(void* baseObj);

GameObject* __thiscall GameObject::constructor(GameObject* this, void* initParam) {
    BaseClassConstructor(initParam);     // Initialize base object with given parameter
    this->vtable = (GameObjectVTable*)VTABLE_PTR;
    this->field_0x3C = &PTR_LAB_00d8313c;
    this->field_0x48 = &PTR_LAB_00d83138;
    this->intField60 = 0;
    this->shortField64 = 0;
    this->shortField66 = 0;
    this->byteField50 = 0;
    return this;
}