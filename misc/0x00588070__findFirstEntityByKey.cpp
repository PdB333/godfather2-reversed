// FUNC_NAME: findFirstEntityByKey
// Function at 0x00588070: Binary search on an array of entity pointers, using a key derived from the entity's fields.
// Returns pointer to the first array element whose computed key equals param_2 (key).
// Uses binary search with linear scan backward to find first occurrence.
// Parameters:
//   array: pointer to array of pointers (int**)
//   size: number of elements (passed in EDI in original asm)
//   key: search key (param_2)
// Returns: pointer to the array slot containing the first matching entity, or 0 if not found.

int** __fastcall findFirstEntityByKey(int** array, int size, int key)
{
    int low = 0;
    int high = size;  // high is exclusive upper bound
    
    // Binary search for the key
    while (low < high)
    {
        int mid = low + ((high - low) >> 1);
        int* entity = array[mid];
        
        int entityKey;
        // Determine key based on flags at offset 0x2C (byte) and first int (id)
        if (((*(unsigned char*)(entity + 0x0B) & 0x20) == 0) || (*entity < 2))
        {
            // Use field at offset 0x14 (entity[5])
            entityKey = entity[5];
        }
        else
        {
            // Use field at offset 0x1C (entity[7])
            entityKey = entity[7];
        }
        
        if (entityKey < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }
    
    // If low is within bounds, check equality
    if (low < size)
    {
        int* entity = array[low];
        int entityKey;
        if (((*(unsigned char*)(entity + 0x0B) & 0x20) == 0) || (*entity < 2))
        {
            entityKey = entity[5];
        }
        else
        {
            entityKey = entity[7];
        }
        
        if (entityKey == key)
        {
            // Scan backwards to find the first occurrence (since duplicates are possible)
            while (low > 0)
            {
                int* prevEntity = array[low - 1];
                int prevKey;
                if (((*(unsigned char*)(prevEntity + 0x0B) & 0x20) == 0) || (*prevEntity < 2))
                {
                    prevKey = prevEntity[5];
                }
                else
                {
                    prevKey = prevEntity[7];
                }
                if (prevKey != key)
                    break;
                low--;
            }
            // Return pointer to the array slot
            return &array[low];
        }
    }
    
    // Not found
    return 0;
}