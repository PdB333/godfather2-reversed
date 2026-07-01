//FUNC_NAME: ArraySlice::split
void __thiscall ArraySlice::split(int* outPtr, int* outCount, int* outRemainderPtr, int* outRemainderCount)
{
    int start = this->m_start;          // +0x00
    int end = this->m_end;              // +0x04
    int* data = this->m_data;           // +0x08
    int size = this->m_size;            // +0x0C
    int lastIndex = size - 1;

    // Validate indices: start and end must be within [0, lastIndex] and not equal
    if (start < 0 || lastIndex < start || end < 0 || lastIndex < end || start == end)
    {
        *outPtr = 0;
        *outCount = 0;
        *outRemainderPtr = 0;
        *outRemainderCount = 0;
        return;
    }

    if (start != lastIndex)
    {
        if (start == 0)
        {
            // Slice from beginning to end (exclusive)
            *outPtr = data;
            *outCount = end;
            *outRemainderPtr = 0;
            *outRemainderCount = 0;
            return;
        }

        if (end == lastIndex)
        {
            // Slice from start to end of array
            *outPtr = data + start;
            *outCount = end - start;
            *outRemainderPtr = 0;
            *outRemainderCount = 0;
            return;
        }

        if (end == 0)
        {
            // Slice from start to end of array (end==0 means no prefix remainder)
            *outPtr = data + start;
            *outCount = size - start;
            *outRemainderPtr = 0;
            *outRemainderCount = 0;
            return;
        }

        *outPtr = data + start;
        if (end <= start)
        {
            // Slice from start to end of array, remainder is prefix [0, end)
            *outCount = size - start;
            *outRemainderPtr = data;
            *outRemainderCount = end;
            return;
        }

        // Normal case: slice from start to end (exclusive), no remainder
        *outCount = end - start;
        *outRemainderPtr = 0;
        *outRemainderCount = 0;
        return;
    }
    else // start == lastIndex (single element)
    {
        *outPtr = data + start;
        *outCount = 1;
        if (end != 0)
        {
            // Remainder is prefix [0, end)
            *outRemainderPtr = data;
            *outRemainderCount = end;
            return;
        }
    }
    *outRemainderPtr = 0;
    *outRemainderCount = 0;
}