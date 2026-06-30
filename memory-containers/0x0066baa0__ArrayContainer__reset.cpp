// FUNC_NAME: ArrayContainer::reset
void ArrayContainer::reset()
{
    // +0x00: size / count of elements
    this->size = 0;
    // +0x08: some flag or other counter (set to zero on reset)
    this->field8 = 0;
    // +0x04: capacity (number of slots)
    // +0x0C: pointer to allocated buffer (4 bytes per slot)
    // Clear the buffer for the entire capacity
    memset(this->data, 0, this->capacity * 4);
}