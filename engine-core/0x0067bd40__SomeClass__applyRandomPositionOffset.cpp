// FUNC_NAME: SomeClass::applyRandomPositionOffset
void __thiscall SomeClass::applyRandomPositionOffset(int* outX, int* outY)
{
    int offsetX1 = generateRandomOffset();
    int offsetX2 = generateRandomOffset();
    *outX = offsetX1 + offsetX2 + *(int*)((char*)this + 0xF0); // +0xF0: base X value

    int offsetY1 = generateRandomOffset();
    int offsetY2 = generateRandomOffset();
    *outY = offsetY1 + offsetY2 + *(int*)((char*)this + 0xF4); // +0xF4: base Y value
}