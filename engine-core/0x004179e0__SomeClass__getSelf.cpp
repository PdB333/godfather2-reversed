// FUNC_NAME: SomeClass::getSelf
// Function at 0x004179e0: Trivial getter returning the 'this' pointer. Likely used as a virtual function that returns the current object (e.g., for interface casting or covariant return types).
int __fastcall SomeClass::getSelf()
{
    return reinterpret_cast<int>(this); // Returns the address of the object itself
}