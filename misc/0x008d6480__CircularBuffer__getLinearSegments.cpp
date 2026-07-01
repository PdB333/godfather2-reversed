//FUNC_NAME: CircularBuffer::getLinearSegments
// Function address: 0x008d6480
// Role: Splits a circular buffer range into two linear segments for contiguous access.
// The buffer stores elements of size 0x1c (28 bytes).
// Structure fields:
//   +0x00: m_startIndex (int) - start index of the range
//   +0x04: m_endIndex (int) - exclusive end index of the range (one past last)
//   +0x08: m_buffer (void*) - pointer to the underlying array
//   +0x0C: m_capacity (int) - total number of elements in the buffer

void __thiscall CircularBuffer::getLinearSegments(
    int* thisPtr,          // param_1: this pointer
    void** outPtr1,        // param_2: output pointer to first segment start
    int* outCount1,        // param_3: output count for first segment
    void** outPtr2,        // param_4: output pointer to second segment start (or null)
    int* outCount2)        // param_5: output count for second segment (or 0)
{
    int startIndex = thisPtr[0];          // +0x00
    int endIndex = thisPtr[1];            // +0x04
    void* bufferBase = (void*)thisPtr[2]; // +0x08
    int capacity = thisPtr[3];            // +0x0C
    int lastIndex = capacity - 1;

    // Validate indices: both must be within [0, capacity-1] and not equal
    if ((startIndex >= 0 && startIndex <= lastIndex) &&
        (endIndex >= 0 && endIndex <= lastIndex) &&
        (startIndex != endIndex))
    {
        // Case: start is at the last element
        if (startIndex == lastIndex)
        {
            *outPtr1 = (char*)bufferBase + startIndex * 0x1c;
            *outCount1 = 1;
            if (endIndex != 0)
            {
                *outPtr2 = bufferBase;
                *outCount2 = endIndex;
                return;
            }
        }
        // Case: start is at the first element
        else if (startIndex == 0)
        {
            *outPtr1 = bufferBase;
            *outCount1 = endIndex;
            goto set_rest_null;
        }
        // Case: end is at the last element
        else if (endIndex == lastIndex)
        {
            *outPtr1 = (char*)bufferBase + startIndex * 0x1c;
            *outCount1 = endIndex; // Note: endIndex == lastIndex, so count = lastIndex (not capacity-startIndex)
            // This appears to be a bug or special case; likely intended to be capacity - startIndex
            // but the decompiled code uses endIndex directly.
        }
        // General case: start and end are not at boundaries
        else
        {
            if (endIndex == 0)
            {
                *outPtr1 = (char*)bufferBase + startIndex * 0x1c;
                *outCount1 = capacity - startIndex;
                *outPtr2 = 0;
                *outCount2 = 0;
                return;
            }
            *outPtr1 = (char*)bufferBase + startIndex * 0x1c;
            if (startIndex < endIndex)
            {
                // Non-wrapping: range from startIndex to endIndex-1
                *outCount1 = endIndex - startIndex;
                *outPtr2 = 0;
                *outCount2 = 0;
                return;
            }
            // Wrapping: two segments
            *outCount1 = capacity - startIndex;
            *outPtr2 = bufferBase;
            *outCount2 = endIndex;
            return;
        }
        // Fallthrough for edge cases (startIndex == lastIndex with endIndex==0, or endIndex==lastIndex)
        *outPtr2 = 0;
        *outCount2 = 0;
        return;
    }
    // Invalid indices: return null segments
    *outPtr1 = 0;
    *outCount1 = 0;
set_rest_null:
    *outPtr2 = 0;
    *outCount2 = 0;
    return;
}