// FUNC_NAME: RemoveArrayRange
// Function address: 0x00434f10
// Role: Removes a contiguous range of elements from a dynamic array.
// The array descriptor is a struct with pointer to data (offset 0x00) and element count (offset 0x04).
// __fastcall: param1 (ECX) = start pointer of range to remove, param2 (EDX) = array descriptor, param3 (stack) = end pointer (exclusive)

struct DynamicArrayDescriptor {
    uint32_t* data;   // +0x00
    int count;        // +0x04
};

void __fastcall RemoveArrayRange(uint32_t* start, DynamicArrayDescriptor* arrayDesc, uint32_t* end)
{
    // Remove all elements from 'start' to 'end' (exclusive) from the array.
    if (start != nullptr && start < end)
    {
        do {
            // Compute pointer to last valid element in array
            uint32_t* lastElement = arrayDesc->data + (arrayDesc->count - 1);
            if (start < lastElement)
            {
                // Number of elements to shift left (from start+1 to lastElement inclusive)
                int elementsToMove = (lastElement - start);  // difference in pointer, already elements
                uint32_t* dst = start;
                uint32_t* src = start + 1;
                for (int i = 0; i < elementsToMove; ++i)
                {
                    *dst = *src;
                    ++dst;
                    ++src;
                }
            }
            // Decrement element count
            --arrayDesc->count;
            // Move to next start position (now points to the element that was originally at start+1)
            ++start;
        } while (start != end);
    }
}