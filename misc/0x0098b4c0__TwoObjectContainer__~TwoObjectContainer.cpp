// FUNC_NAME: TwoObjectContainer::~TwoObjectContainer
void __fastcall TwoObjectContainer::~TwoObjectContainer(int* thisPtr)
{
    // Destructor: calls custom destructors on two owned objects if non-null.
    // Structure layout:
    // +0x00: firstObject (pointer to first sub-object)
    // +0x04: (padding or other field)
    // +0x08: (padding or other field)
    // +0x0C: firstDestructor (function pointer to delete firstObject)
    // +0x10: secondObject (pointer to second sub-object)
    // +0x14: (padding or other field)
    // +0x18: (padding or other field)
    // +0x1C: secondDestructor (function pointer to delete secondObject)

    int* firstObject = (int*)thisPtr[0];        // offset 0x00
    int* secondObject = (int*)thisPtr[4];       // offset 0x10

    if (secondObject != 0) {
        // Call destructor for second object via function pointer at offset 0x1C
        void (*secondDestructor)(int*) = (void (*)(int*))thisPtr[7];
        secondDestructor(secondObject);
    }

    if (firstObject != 0) {
        // Call destructor for first object via function pointer at offset 0x0C
        void (*firstDestructor)(int*) = (void (*)(int*))thisPtr[3];
        firstDestructor(firstObject);
    }
}