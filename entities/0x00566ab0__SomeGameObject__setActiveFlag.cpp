// FUNC_NAME: SomeGameObject::setActiveFlag
void __thiscall SomeGameObject::setActiveFlag(int this, char value)
{
    // Check if there's a sub-object at offset +0x8 (likely a component or inner object)
    int *subObject = *(int **)(this + 8);
    if (subObject != 0) {
        // Set byte at +0x33d in the sub-object (possibly an enable/disable flag)
        *(char *)(subObject + 0x33d) = value;
    }
    // Update flags at this+0x2c (bitmask: bit 1 = 0x2)
    if (value != '\0') {
        *(uint *)(this + 0x2c) = *(uint *)(this + 0x2c) | 2;
    } else {
        *(uint *)(this + 0x2c) = *(uint *)(this + 0x2c) & 0xfffffffd;
    }
}