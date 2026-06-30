// FUNC_NAME: IntArray::removeElement
// Function address: 0x006e9760
// Removes the first occurrence of a value from a dynamic integer array.
// Structure:
//   +0x18: int* m_array (pointer to array of ints)
//   +0x1c: int m_count (number of elements)

void __thiscall IntArray::removeElement(int thisPtr, int value)
{
    if (value == 0) {
        return;
    }

    int count = *(int*)(thisPtr + 0x1c);
    if (count <= 0) {
        return;
    }

    int* array = *(int**)(thisPtr + 0x18);
    int index = 0;
    while (index < count) {
        if (array[index] == value) {
            // Found the element, shift remaining elements left
            for (int i = index; i < count - 1; i++) {
                array[i] = array[i + 1];
            }
            *(int*)(thisPtr + 0x1c) = count - 1;
            return;
        }
        index++;
    }
}