// FUNC_NAME: unknown::getComponentByOffset
int __fastcall unknown::getComponentByOffset(int this) {
    // this + 0xe4 likely stores a pointer to a derived class or component.
    // Subtract 0x48 to get the base pointer of the containing object.
    if (*(int *)(this + 0xE4) != 0) {
        return *(int *)(this + 0xE4) - 0x48;
    }
    return 0;
}