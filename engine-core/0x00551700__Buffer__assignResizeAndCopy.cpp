// FUNC_NAME: Buffer::assignResizeAndCopy
int* __thiscall Buffer::assignResizeAndCopy(Buffer* this, Buffer* other)
{
    int currentCapacity = this->mCapacity & 0x3FFFFFFF;
    if (currentCapacity < other->mSize) {
        if ((int)(this->mCapacity) >= 0) {
            TlsGetValue(DAT_01139810);
            FUN_00aa26e0(this->mData, currentCapacity * 0x30, 0x17);
        }
        TlsGetValue(DAT_01139810);
        int newData = FUN_00aa2680(other->mSize * 0x30, 0x17);
        this->mData = newData;
        this->mCapacity = this->mCapacity & 0x40000000 | other->mSize;
    }

    int elemCount = other->mSize;
    int destData = this->mData;
    this->mSize = elemCount;
    int srcData = other->mData;

    int copied = 0;
    if (elemCount > 3) {
        int i = (elemCount - 4 >> 2) + 1;
        copied = i * 4;
        undefined4* dest = (undefined4*)(destData + 0x44);
        undefined4* src = (undefined4*)(srcData + 0x4c);
        do {
            // Copy 4 elements (each 0x30 bytes) in one iteration
            dest[-0x11] = src[-0x13];
            dest[-0x10] = src[-0x12];
            dest[-0x0f] = src[-0x11];
            dest[-0x0e] = src[-0x10];
            dest[-0x0d] = src[-0x0f];
            dest[-0x0c] = src[-0x0e];
            dest[-0x0b] = src[-0x0d];
            dest[-0x0a] = src[-0x0c];
            dest[-0x09] = src[-0x0b];
            dest[-0x08] = src[-0x0a];
            dest[-0x07] = src[-0x09];
            dest[-0x06] = src[-0x08];
            dest[-0x05] = src[-0x07];
            dest[-0x04] = src[-0x06];
            dest[-0x03] = src[-0x05];
            dest[-0x02] = src[-0x04];
            dest[-0x01] = src[-0x03];
            *dest = *(undefined4*)((int)dest + (srcData - destData));
            dest[0x01] = src[-0x01];
            dest[0x02] = *src;
            dest[0x03] = src[0x01];
            dest[0x04] = src[0x02];
            dest[0x05] = src[0x03];
            dest[0x06] = src[0x04];
            dest[0x07] = src[0x05];
            dest[0x08] = src[0x06];
            dest[0x09] = src[0x07];
            dest[0x0a] = src[0x08];
            dest[0x0b] = src[0x09];
            dest[0x0c] = src[0x0a];
            dest[0x0d] = src[0x0b];
            dest[0x0e] = src[0x0c];
            dest[0x0f] = src[0x0d];
            dest[0x10] = src[0x0e];
            dest[0x11] = src[0x0f];
            dest[0x12] = src[0x10];
            dest[0x13] = src[0x11];
            dest[0x14] = src[0x12];
            dest[0x15] = src[0x13];
            dest[0x16] = src[0x14];
            dest[0x17] = src[0x15];
            dest[0x18] = src[0x16];
            dest[0x19] = src[0x17];
            dest[0x1a] = src[0x18];
            dest[0x1b] = src[0x19];
            dest[0x1c] = src[0x1a];
            dest[0x1d] = src[0x1b];
            dest[0x1e] = src[0x1c];
            // Advance pointers by 4 elements (0x30*4 = 0xC0 bytes = 48 dwords)
            dest += 0x30; // 0x30 dwords = 0xC0 bytes
            src += 0x30;
            i--;
        } while (i != 0);
    }

    if (copied < elemCount) {
        int remaining = elemCount - copied;
        undefined4* dest = (undefined4*)(destData + 0x44 + copied * 0x30);
        undefined4* src = (undefined4*)(srcData + 0x4c + copied * 0x30);
        do {
            // Copy one element (0x30 bytes = 12 dwords)
            dest[-5] = src[-7];
            remaining--;
            dest[-4] = src[-6];
            dest[-3] = src[-5];
            dest[-2] = src[-4];
            dest[-1] = src[-3];
            *dest = *(undefined4*)((srcData - destData) - 0x30 + (int)(dest + 0x0c));
            dest[1] = src[-1];
            dest[2] = *src;
            dest[3] = src[1];
            dest[4] = src[2];
            dest[5] = src[3];
            // Advance by 12 dwords (one element)
            dest += 0x0c;
            src += 0x0c;
        } while (remaining != 0);
    }

    return this;
}