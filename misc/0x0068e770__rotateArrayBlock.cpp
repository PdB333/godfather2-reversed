// FUNC_NAME: rotateArrayBlock
void rotateArrayBlock(uint32_t* start, uint32_t* split, uint32_t* end)
{
    int totalCount = (int)end - (int)start >> 2;          // Number of elements from start to end
    int splitCount = (int)split - (int)start >> 2;        // Number of elements from start to split
    int subSize = splitCount;
    int mod = totalCount;
    
    // GCD of splitCount and totalCount → number of cycles
    while (subSize != 0) {
        int temp = mod % subSize;
        mod = subSize;
        subSize = temp;
    }
    
    // If mod < totalCount (i.e. GCD < totalCount) and mod > 0, perform juggling rotation
    if ((mod < totalCount) && (0 < mod))
    {
        uint32_t* current = start + mod;
        do
        {
            uint32_t saved = *current;
            uint32_t* writePos = current;
            uint32_t* readPos = current + splitCount;
            
            // Wrap around if readPos reaches end
            if (current + splitCount == end)
            {
                readPos = start;
            }
            
            // Chase the cycle
            while (readPos != current)
            {
                *writePos = *readPos;
                int remaining = (int)end - (int)readPos >> 2;
                writePos = readPos;
                if (splitCount < remaining)
                {
                    readPos = readPos + splitCount;
                }
                else
                {
                    readPos = start + (splitCount - remaining);
                }
            }
            
            mod--;
            current--;
            *writePos = saved;
        } while (0 < mod);
    }
}