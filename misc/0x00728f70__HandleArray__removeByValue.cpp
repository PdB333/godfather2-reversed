// FUNC_NAME: HandleArray::removeByValue
// Function address: 0x00728f70
// Removes first occurrence of a value from the array by swapping with last element (O(n) find, O(1) removal)

class HandleArray {
public:
    // +0x1c: int* array; // pointer to array of ints (handles/IDs)
    // +0x20: int count;   // number of elements
    int* array;
    int count;

    void removeByValue(int value) {
        if (count != 0) {
            int* arr = array;
            for (int i = 0; i < count; i++) {
                if (arr[i] == value) {
                    // Found at index i
                    if (i != count - 1) {
                        // Swap with last element
                        arr[i] = arr[count - 1];
                    }
                    count--;
                    return;
                }
            }
        }
    }
};