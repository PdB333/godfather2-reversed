// FUNC_NAME: SomeClass::setState
void __thiscall SomeClass::setState(int this, char newState)
{
    // Check if state at +0x58 differs from newState
    if (newState != *(char *)(this + 0x58)) {
        // Set dirty flag at +0x64 to 1
        *(undefined1 *)(this + 100) = 1;
        // Update state at +0x58
        *(char *)(this + 0x58) = newState;
    }
}