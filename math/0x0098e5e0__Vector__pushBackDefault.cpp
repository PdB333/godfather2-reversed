// FUNC_NAME: Vector::pushBackDefault
void __thiscall Vector::pushBackDefault(void)
{
    int oldSize;
    int newCapacity;

    if (size == capacity) {
        newCapacity = (capacity != 0) ? (capacity * 2) : 1;
        reallocate(newCapacity);
    }
    oldSize = size;
    size = oldSize + 1;
    if (array != (void *)0x0) {
        constructElement(oldSize);
    }
    return;
}