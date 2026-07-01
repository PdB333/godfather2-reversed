// FUNC_NAME: Entity::Entity
// Function address: 0x008a8170
// Constructor for an Entity class that adds the object to a global linked list.
// Fields:
//   +0x00: vtable (void*)
//   +0x04: int field (set from param3)
//   +0x08: int field (set from param5)
//   +0x0C: int field (set from param4)
//   +0x10: int (zeroed)
//   +0x14: int (zeroed)
//   +0x18: int (zeroed)
//   +0x1C: int (zeroed)
//   +0x20: char name[64] (copied from param2)
//   +0x70: Entity* next (linked list pointer)

class Entity {
public:
    void* vtable;        // +0x00
    int field_04;        // +0x04
    int field_08;        // +0x08
    int field_0C;        // +0x0C
    int field_10;        // +0x10
    int field_14;        // +0x14
    int field_18;        // +0x18
    int field_1C;        // +0x1C
    char name[64];       // +0x20 (0x40 bytes)
    // ... padding or other members ...
    Entity* next;        // +0x70

    // Constructor
    __thiscall Entity(const char* nameStr, int param3, int param4, int param5) {
        // Call base Entity constructor (0x0064cc90)
        FUN_0064cc90();

        // Set vtable to specific entry (0x00d79c48)
        vtable = reinterpret_cast<void*>(0x00d79c48);

        // Copy name with null termination (max 63 chars)
        _strncpy(name, nameStr, 0x3f);
        name[0x3f] = '\0';

        // Set integer fields
        field_04 = param3;
        field_0C = param4;
        field_08 = param5;

        // Zero out four fields after name
        field_10 = 0;
        field_14 = 0;
        field_18 = 0;
        field_1C = 0;

        // Insert into global linked list (head stored at DAT_012059ec)
        next = DAT_012059ec;
        DAT_012059ec = this;
    }
};

// External symbols referenced
extern void FUN_0064cc90();
extern int _strncpy(char* dst, const char* src, size_t max);
extern Entity* DAT_012059ec;  // global linked list head