// FUNC_NAME: SomeClass::isStateNotFive
bool __thiscall SomeClass::isStateNotFive(int* outState) // outState receives the value at offset +0x04
{
    *outState = *(int*)(this + 4); // +0x04: state/type field
    return *(int*)(this + 4) != 5; // returns true if state is not 5
}