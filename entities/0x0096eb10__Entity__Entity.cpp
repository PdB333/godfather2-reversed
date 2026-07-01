// FUNC_NAME: Entity::Entity
// Address: 0x0096eb10
// Constructor for Entity class. Initializes dual-vtable object, zeros fields, calls base constructor (0x005bf9b0) and registers with manager (0x00968d80) using global type identifier DAT_00d5c454.

// External vtable symbols (from Ghidra)
extern void *PTR_FUN_00d8ee98;   // primary vtable
extern void *PTR_LAB_00d8ee70;   // secondary vtable (likely for multiple inheritance)
extern int DAT_00d5c454;         // global used as type ID or manager pointer

// Forward declaration of base class constructor and registration function
void __thiscall BaseObject__constructor(void *this);  // FUN_005bf9b0
void __fastcall Entity__RegisterWithManager(int type, int param); // FUN_00968d80

// Entity class definition
class Entity {
public:
    void *vtable1;          // +0x00
    // ... other base members ...
    void *vtable2;          // +0x10
    // ... other members ...
    int field_0x4C;         // +0x4C
    int field_0x50;         // +0x50
    int field_0x54;         // +0x54
    int field_0x70;         // +0x70

    __thiscall Entity();
};

__thiscall Entity::Entity()
{
    // Call base class constructor
    BaseObject__constructor(this);

    // Set vtable pointers
    this->vtable1 = &PTR_FUN_00d8ee98;
    this->vtable2 = &PTR_LAB_00d8ee70;

    // Zero fields at +0x4C, +0x50, +0x54
    this->field_0x4C = 0;
    this->field_0x50 = 0;
    this->field_0x54 = 0;

    // Register with manager (type 6, using global)
    Entity__RegisterWithManager(6, DAT_00d5c454);

    // Zero field at +0x70
    this->field_0x70 = 0;
}