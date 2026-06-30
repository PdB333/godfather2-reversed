// FUNC_NAME: Actor::Actor
// Address: 0x0041c8b0
// Role: Constructor for Actor class - calls base constructor, static initialization, and member initialization
// Parameters: this (ecx), arg1 (edx?), arg2 (stack)
// Calling convention: __thiscall (implied by usage)
void __thiscall Actor::Actor(Actor* this, int arg1, int arg2)
{
    // Call base class constructor (0x0041ad20)
    BaseClass::BaseClass(this, arg1);

    // Static/global initialization hook (e.g., reference counting, singleton access)
    FUN_00491090();  // likely staticInit()

    // Call further member initialization with full argument set
    this->initializeMember(arg1, arg2);  // FUN_004196d0
}