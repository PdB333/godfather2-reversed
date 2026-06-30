// FUNC_NAME: Entity::Entity
// Function at 0x00694ab0: Constructor wrapper that calls base class constructor (FUN_00694160)
// Returns the 'this' pointer unchanged (typical __fastcall constructor pattern)

class Entity {
public:
    __thiscall Entity() {
        // Call base class constructor (likely EARSObject or similar)
        FUN_00694160();
        // Return this (implicit in __thiscall, but shown for clarity)
        return this;
    }
};