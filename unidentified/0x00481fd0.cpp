// FUN_00481fd0: EARSObject::EARSObject (constructor)
class EARSObject {
public:
    void* vtable;           // +0x00
    uint32_t field_0x04;    // +0x04
    uint32_t field_0x08;    // +0x08
    uint32_t field_0x0C;    // +0x0C
    uint32_t field_0x10;    // +0x10
    EARSObject* selfPtr;    // +0x14 - pointer to itself (offset +0x28)
    uint32_t field_0x18;    // +0x18
    uint32_t field_0x1C;    // +0x1C
    uint32_t field_0x20;    // +0x20
    uint32_t field_0x24;    // +0x24
    void* vtable2;          // +0x28 - secondary vtable or interface ptr
    uint32_t field_0x2C;    // +0x2C
    void* callback;         // +0x30 - function pointer (LAB_00482430)
    uint32_t field_0x34;    // +0x34
    uint32_t field_0x38;    // +0x38
    uint32_t field_0x3C;    // +0x3C

    // __thiscall constructor
    static EARSObject* __thiscall Create() {
        // Allocate 0x40 bytes
        EARSObject* obj = (EARSObject*)FUN_009c8e50(0x40);
        if (obj == nullptr) {
            return nullptr;
        }

        // Initialization
        obj->field_0x04 = 0;
        obj->field_0x08 = 0;
        obj->field_0x10 = 1;
        obj->field_0x0C = 1;

        // Set base vtable
        obj->vtable = &PTR_LAB_00e317dc;

        obj->field_0x18 = 0;

        // Call base class constructor (or some initialization)
        FUN_00452df0(0);

        obj->field_0x24 = 1;

        // Overwrite vtable with derived class vtable
        obj->vtable = &PTR_LAB_00e335dc;
        obj->vtable2 = &PTR_LAB_00e33608;
        obj->callback = &LAB_00482430;
        obj->field_0x34 = 0;

        // self-pointer points to the address of vtable2 (offset +0x28)
        obj->selfPtr = (EARSObject*)(&obj->vtable2);

        return obj;
    }
};