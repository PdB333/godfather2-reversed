// FUNC_NAME: SomeClass::findFirstActiveObject
void __thiscall SomeClass::findFirstActiveObject(void)
{
    uint index;
    int *arrayPtr;
    int *foundPtr;

    this->currentIndex = 0;      // +0x04
    this->foundObject = 0;       // +0x08

    arrayPtr = this->objectArray; // +0x00
    if (arrayPtr != (int *)0x0) {
        do {
            index = this->currentIndex;
            if (0xfff < index) {
                return;
            }
            foundPtr = *(int **)(arrayPtr + index * 4);
            this->foundObject = foundPtr; // +0x08
            this->currentIndex = index + 1; // +0x04
        } while (foundPtr == (int *)0x0);
    }
    return;
}