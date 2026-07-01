// FUNC_NAME: Entity::Entity
// Reconstructed constructor for Entity at 0x008a9460
// Object layout:
// +0x00: vtable (first base)
// +0x14: pointer to self+0x28 (second base subobject)
// +0x18: unknown (set to 0)
// +0x24: flag (set to 1)
// +0x28: vtable2 (second base)
// +0x30: function pointer (set to ctor continuation)
// +0x34: unknown (set to 0)

#include <cstdint>

// External functions (names guessed from context)
extern uint32_t* __stdcall getSomeResource();          // FUN_00481610
extern void __cdecl initSomeSystem(uint32_t, uint32_t); // FUN_0064d390
extern void __cdecl registerEntity(uint32_t*);          // FUN_00454a10

// Forward declaration of a function this constructor uses
extern void __thiscall ctorContinuation(Entity*); // LAB_008a8920 - likely part of derived initialization

class Entity {
public:
    // Fields
    uint32_t* vtable;               // +0x00
    // padding from +0x04 to +0x14
    uint32_t pad_0x04[4];           // +0x04..+0x10
    Entity*  m_secondSubobject;     // +0x14: points to &this[0x28]
    uint32_t field_0x18;            // +0x18
    uint32_t pad_0x1c[2];           // +0x1c..+0x20
    uint32_t field_0x24;            // +0x24
    uint32_t* vtable2;              // +0x28
    uint32_t pad_0x2c;              // +0x2c
    void (*m_ctorContinuation)(Entity*); // +0x30
    uint32_t field_0x34;            // +0x34

    // Constructor
    __thiscall Entity(int param_2);
};

__thiscall Entity::Entity(int param_2) {
    uint32_t* res;
    
    if (param_2 != 0) {
        res = getSomeResource();
    } else {
        res = nullptr;
    }
    initSomeSystem(0, 1);
    
    // Set base class vtable (first base)
    vtable = (uint32_t*)0x00e317dc;   // base vtable
    field_0x18 = 0;
    
    registerEntity(res);
    field_0x24 = 1;
    
    // Set derived vtable (overwrites first vtable)
    vtable = (uint32_t*)0x00d79d44;   // derived vtable
    // Set second base vtable
    vtable2 = (uint32_t*)0x00d79bc0;  // second base vtable
    m_ctorContinuation = ctorContinuation;
    field_0x34 = 0;
    
    // Stored pointer to the second subobject (at offset 0x28)
    m_secondSubobject = reinterpret_cast<Entity*>(reinterpret_cast<uint8_t*>(this) + 0x28);
}