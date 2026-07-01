// FUNC_NAME: ResizableBuffer::setSize
void __thiscall ResizableBuffer::setSize(ResizableBuffer* this, uint newSize)
{
    // this->mSize at offset +0x04 (current allocation size)
    if (this->mSize < newSize) {
        resizeBuffer(newSize);  // Reallocate internal memory to newSize
        this->mSize = newSize;
        return;
    }
    if (newSize < this->mSize) {
        this->mSize = newSize;
    }
    return;
}