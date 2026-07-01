// FUNC_NAME: StringBuffer::reserve
void __thiscall StringBuffer::reserve(uint newCapacity)
{
    if (this->capacity < newCapacity) {
        reallocateBuffer(newCapacity);
        this->capacity = newCapacity;
        return;
    }
    if (newCapacity < this->capacity) {
        this->capacity = newCapacity;
    }
}