// FUNC_NAME: DynamicArray::removeAt
void DynamicArray::removeAt(uint index)
{
    // The array structure: offset 0 = pointer to data (int*)
    // offset 4 = number of elements (size)
    int* data = *(int**)arrayStruct;
    uint size = *(uint*)(arrayStruct + 4);

    if (index < size - 1)
    {
        do
        {
            data[index] = data[index + 1];
            index++;
        }
        while (index < size - 1);
    }

    // Decrease size after shifting
    --(*(uint*)(arrayStruct + 4));
}