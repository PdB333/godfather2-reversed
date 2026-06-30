// FUNC_NAME: ArrayContainer::addUnique

// Function address: 0x004785e0
// Adds a unique integer value to the internal array if it is not already present and capacity allows.
// Returns the new count (size) after potential addition.
// Field offsets:
//   +0x58 : capacity (maximum number of elements)
//   +0x5c : count (current number of elements)
//   +0x60 : pointer to array of ints

int __thiscall ArrayContainer::addUnique(int value)
{
    int count = *(int *)(this + 0x5c);
    if (count > 0)
    {
        int *data = *(int **)(this + 0x60);
        for (int i = 0; i < count; i++)
        {
            if (data[i] == value)
            {
                // Element already present, return current count
                return count;
            }
        }
    }

    // Check if there is space for a new element
    if (count >= *(int *)(this + 0x58))
    {
        // No space, return current count
        return count;
    }

    // Add the new element at the end
    int *data = *(int **)(this + 0x60);
    data[count] = value;
    *(int *)(this + 0x5c) = count + 1;
    return count + 1;
}