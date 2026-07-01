// FUNC_NAME: Component::getOwner
int __thiscall Component::getOwner(void) {
    // +0xec: pointer to owner's component slot (offset 0x48 within owner)
    if (*(int*)(this + 0xec) != 0) {
        return *(int*)(this + 0xec) - 0x48; // return base of owner object
    }
    return 0;
}