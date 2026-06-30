// FUN_00478620: IntArray::remove
int IntArray::remove(int value)
{
    int count = this->count; // +0x5c
    if (count > 0)
    {
        int* items = this->items; // +0x60
        int i = 0;
        do
        {
            if (value == items[i])
            {
                // Remove the element at index i
                count--;
                this->count = count;
                // If there are more elements after the removed one, shift them left
                if (count > i)
                {
                    do
                    {
                        items[i] = items[i + 1];
                        i++;
                    } while (i < count);
                }
                return count;
            }
            i++;
        } while (i < count);
    }
    return count;
}