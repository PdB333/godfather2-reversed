// FUNC_NAME: EntityDataManager::EntityDataManager
// Function address: 0x008d5670
// Role: Constructor for EntityDataManager (EA EARS engine, Godfather 2). Initialises vtable, secondary vtables, and zeroes member fields.

// Base class constructor (FUN_0046c590) is assumed to be EntityDataManagerBase::EntityDataManagerBase(int arg)
extern void __thiscall EntityDataManagerBase_constructor(int arg);

// Static constant referenced from 0x00d5ccf8 (DAT_00d5ccf8) – likely a colour or default value
extern int g_entityDataManagerDefaultValue;

class EntityDataManager {
public:
    // Vtable pointer at offset 0x00
    void* vtable;

    // Secondary vtables (multiple inheritance)
    void* secondaryVtable;   // +0x3C  (param_1[0xF])
    void* tertiaryVtable;    // +0x48  (param_1[0x12])

    // Fields from offset 0x50 onward
    byte _pad0x10[0x10];     // fill to offset 0x50

    // Member variables (all zeroed by constructor)
    int   field_0x50;        // +0x50  (param_1[0x14])
    uint16 field_0x54;       // +0x54  (param_1[0x15] lower 16 bits)
    uint16 field_0x56;       // +0x56  ((int)this + 0x56)
    int   field_0x58;        // +0x58  (param_1[0x16])
    uint16 field_0x5C;       // +0x5C  (param_1[0x17] lower 16 bits)
    uint16 field_0x5E;       // +0x5E  ((int)this + 0x5E)
    uint8  field_0x60;       // +0x60  (param_1[0x18] as byte)
    int   field_0x64;        // +0x64  (param_1[0x19])
    int   field_0x68;        // +0x68  (param_1[0x1A])
    int   field_0x6C;        // +0x6C  (param_1[0x1B])
    int   field_0x70;        // +0x70  (param_1[0x1C])
    int   field_0x74;        // +0x74  (param_1[0x1D])
    int   field_0x78;        // +0x78  (param_1[0x1E])
    int   field_0x7C;        // +0x7C  (param_1[0x1F])
    int   field_0x80;        // +0x80  (param_1[0x20])
    int   field_0x84;        // +0x84  (param_1[0x21])
    int   field_0x88;        // +0x88  (param_1[0x22])
    int   field_0x8C;        // +0x8C  (param_1[0x23])
    int   field_0x90;        // +0x90  (param_1[0x24])
    int   field_0x94;        // +0x94  (param_1[0x25])
    int   field_0x98;        // +0x98  (param_1[0x26])

    // Two copies of the default value (e.g., a colour or constant)
    int   defaultVal1;       // +0x9C  (param_1[0x27])
    int   defaultVal2;       // +0xA0  (param_1[0x28])

    int   field_0xA4;        // +0xA4  (param_1[0x29])
    uint16 field_0xA8;       // +0xA8  (param_1[0x2A] lower 16 bits)
    uint16 field_0xAA;       // +0xAA  ((int)this + 0xAA)

    // Constructor
    EntityDataManager* __thiscall EntityDataManager(int arg);
};

EntityDataManager* __thiscall EntityDataManager::EntityDataManager(EntityDataManager* this, int arg) {
    // Call base class constructor (assumed to initialise fields up to offset 0x3C)
    EntityDataManagerBase_constructor(arg);

    // Set derived vtable for this class
    this->vtable = (void*)0x00d7d66c;

    // Set secondary vtables (likely for separate interfaces)
    *(void**)((uint8_t*)this + 0x3C) = (void*)0x00d7d65c;
    *(void**)((uint8_t*)this + 0x48) = (void*)0x00d7d658;

    // Zero out member fields from offset 0x50 to end
    *(int*)((uint8_t*)this + 0x50) = 0;
    *(uint16_t*)((uint8_t*)this + 0x54) = 0;
    *(uint16_t*)((uint8_t*)this + 0x56) = 0;
    *(int*)((uint8_t*)this + 0x58) = 0;
    *(uint16_t*)((uint8_t*)this + 0x5C) = 0;
    *(uint16_t*)((uint8_t*)this + 0x5E) = 0;
    *(uint8_t*)((uint8_t*)this + 0x60) = 0;
    *(int*)((uint8_t*)this + 0x64) = 0;
    *(int*)((uint8_t*)this + 0x68) = 0;
    *(int*)((uint8_t*)this + 0x6C) = 0;
    *(int*)((uint8_t*)this + 0x70) = 0;
    *(int*)((uint8_t*)this + 0x74) = 0;
    *(int*)((uint8_t*)this + 0x78) = 0;
    *(int*)((uint8_t*)this + 0x7C) = 0;
    *(int*)((uint8_t*)this + 0x80) = 0;
    *(int*)((uint8_t*)this + 0x84) = 0;
    *(int*)((uint8_t*)this + 0x88) = 0;
    *(int*)((uint8_t*)this + 0x8C) = 0;
    *(int*)((uint8_t*)this + 0x90) = 0;
    *(int*)((uint8_t*)this + 0x94) = 0;
    *(int*)((uint8_t*)this + 0x98) = 0;

    // Initialise two copies of the default value (e.g., a colour/constant)
    int val = g_entityDataManagerDefaultValue;
    *(int*)((uint8_t*)this + 0x9C) = val;
    *(int*)((uint8_t*)this + 0xA0) = val;

    *(int*)((uint8_t*)this + 0xA4) = 0;
    *(uint16_t*)((uint8_t*)this + 0xA8) = 0;
    *(uint16_t*)((uint8_t*)this + 0xAA) = 0;

    return this;
}