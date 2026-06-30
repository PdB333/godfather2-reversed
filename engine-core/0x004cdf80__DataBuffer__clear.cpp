// FUNC_NAME: DataBuffer::clear
void __thiscall DataBuffer::clear(void)
{
    uint i = 0;
    // offset +0x00: pointer to data buffer
    // offset +0x08: size as unsigned short
    if (this->size != 0) {
        do {
            *(byte *)(this->data + i) = 0;
            i++;
        } while (i < this->size);
    }
    return;
}