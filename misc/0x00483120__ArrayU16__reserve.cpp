// FUNC_NAME: ArrayU16::reserve
void __thiscall ArrayU16::reserve(unsigned int newCapacity)
{
    unsigned short* newBuffer;
    unsigned int idx;
    unsigned short* dst;

    if (this->capacity < newCapacity) {
        newBuffer = (unsigned short*)EAHeapAlloc(newCapacity * 2);
        if (this->data != nullptr) {
            idx = 0;
            dst = newBuffer;
            if (this->size != 0) {
                do {
                    if (dst != nullptr) {
                        *dst = *(unsigned short*)((int)this->data + idx * 2);
                    }
                    idx++;
                    dst++;
                } while (idx < this->size);
            }
            EAHeapFree(this->data);
        }
        this->data = newBuffer;
        this->capacity = newCapacity;
    }
}