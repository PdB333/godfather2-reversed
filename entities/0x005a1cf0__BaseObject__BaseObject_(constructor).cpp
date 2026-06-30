// FUNC_NAME: BaseObject::BaseObject (constructor)
int __thiscall BaseObject::BaseObject(int this) // Passes this in ECX, uses EAX for derived constructor
{
    // Call base class constructor (likely initializes vtable + common fields)
    FUN_005a0a00(in_EAX); // in_EAX likely contains vtable pointer or derived class parameter

    // Set type/state to 2 (e.g., kTypeActive, kStateInitialized)
    *(int *)(this + 0x1c) = 2;

    return this;
}