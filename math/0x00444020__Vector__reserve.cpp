// FUNC_NAME: Vector::reserve
void Vector::reserve(uint newCapacity)
{
    // Check if reallocation is needed
    if (newCapacity <= this->capacity)
        return;

    // Get allocator, use default if none set
    Allocator* alloc = this->allocator;
    if (alloc == NULL)
        alloc = &gDefaultAllocator; // 0x01218a14

    // Allocate new block: each element is 8 bytes (a pair)
    void* newData = alloc->vtable->allocate(newCapacity * 8, alloc);

    // Copy existing elements from old array to new
    if (this->size != 0)
    {
        uint count = 0;
        Element* src = (Element*)this->data;
        Element* dst = (Element*)newData;
        do
        {
            if (dst != NULL)
            {
                dst->first  = src[count].first;
                dst->second = src[count].second;
            }
            count++;
            dst++;
        } while (count < this->size);
    }

    // Free old array using allocator's deallocate
    alloc->vtable->deallocate(this->data, 0);

    // Update internal pointers and capacity
    this->data     = newData;
    this->capacity = newCapacity;
}