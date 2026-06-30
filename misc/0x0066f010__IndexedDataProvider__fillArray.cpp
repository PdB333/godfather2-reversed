// FUNC_NAME: IndexedDataProvider::fillArray
void __thiscall IndexedDataProvider::fillArray(int *outArray, int count, int context)
{
    int i;
    int value;

    i = 0;
    if (0 < count) {
        do {
            // Virtual function at vtable+0x12 (offset 0xC) is called with (context, 0)
            value = (*(int (**)(int, int))(this->vtable[0] + 0xC))(context, 0);
            outArray[i] = value;
            i++;
        } while (i < count);
    }
    return;
}