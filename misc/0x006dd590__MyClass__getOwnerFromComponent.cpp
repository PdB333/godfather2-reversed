// FUNC_NAME: MyClass::getOwnerFromComponent
int __fastcall MyClass::getOwnerFromComponent(int thisPtr) {
    // Offsets: this + 0x74C is a pointer to a subobject (component)
    int componentPtr = *(int*)(thisPtr + 0x74C);
    if (componentPtr != 0) {
        // Subtract 0x48 to get back to the containing object's base
        return componentPtr - 0x48;
    }
    return 0;
}