// FUNC_NAME: SortedArray::binarySearch
int __thiscall SortedArray::binarySearch(int *this, uint *key) 
{
    int count = this[1]; // +0x04: number of elements in the array
    int result = -1;
    int low = -1;
    
    if (count != 0) 
    {
        int high = count;
        int mid;
        do 
        {
            mid = (high + low) >> 1;
            int candidate = mid;
            uint *arrayBase = (uint *)this[0]; // +0x00: pointer to array of 8-byte entries (uint64)
            if (arrayBase[mid * 2] < *key) // compare the first uint of the entry (key field)
            {
                candidate = high;
                low = mid;
            }
            high = candidate;
        } while (high - low != 1);
        
        if (low < count) 
        {
            uint *arrayBase = (uint *)this[0];
            if (arrayBase[low * 2] == *key) // key found
            {
                result = low;
            }
        }
    }
    return result;
}