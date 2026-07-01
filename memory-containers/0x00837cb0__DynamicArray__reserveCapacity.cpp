// FUNC_NAME: DynamicArray::reserveCapacity
void DynamicArray::reserveCapacity(uint requestedCapacity)
{
    // Check if current capacity is less than requested
    if ((uint)this->capacity < requestedCapacity) {
        // Allocate new buffer of requested size (4 bytes per element)
        int* newData = (int*)FUN_009c8e80(requestedCapacity * 4);
        
        // Copy existing elements if old buffer exists
        if (this->data != 0 && this->count > 0) {
            uint i = 0;
            int* src = this->data;
            int* dst = newData;
            do {
                if (dst != 0) {
                    *dst = *src;
                }
                i++;
                src++;
                dst++;
            } while (i < (uint)this->count);
        }
        
        // Free old buffer if present
        if (this->data != 0) {
            FUN_009c8f10(this->data);
        }
        
        // Update pointers and capacity
        this->data = newData;
        this->capacity = requestedCapacity;
    }
    // If capacity already sufficient, do nothing
}