// FUNC_NAME: CSomeClass::setArrayElement
// Sets an element in an integer array at offset +0x04, with index param_2.
// If the value changed, sets a dirty flag at offset +0x1c to 1.
// Called from various functions likely within the same class or related managers.
void __thiscall CSomeClass::setArrayElement(int index, int newValue)
{
    // +0x04: array of ints (size unknown, indexed by param_2)
    // +0x1c: dirty flag (byte)
    if (*(int *)((unsigned char *)this + 4 + index * 4) != newValue) {
        *(int *)((unsigned char *)this + 4 + index * 4) = newValue;
        *(unsigned char *)((unsigned char *)this + 0x1c) = 1;
    }
    return;
}