// FUNC_NAME: SomeClass::setData4
void __thiscall SomeClass::setData4(int thisPtr, int *data)
{
    // Copies 4 int32 values into object at offsets 0x1cc through 0x1d8
    *(int *)(thisPtr + 0x1cc) = data[0];
    *(int *)(thisPtr + 0x1d0) = data[1];
    *(int *)(thisPtr + 0x1d4) = data[2];
    *(int *)(thisPtr + 0x1d8) = data[3];
}