// FUNC_NAME: StreamWriter::writeAlignedData
void __fastcall StreamWriter::writeAlignedData(StreamWriter* this, uint32_t field0, uint32_t field1, const void* data, size_t size, int32_t alignment, uint32_t field2)
{
    uint32_t* ptr;
    void* dst;

    // Align current write pointer to 4 bytes
    ptr = (uint32_t*)((*(int32_t*)((uint8_t*)this + 0x14) + 3) & 0xFFFFFFFC);
    *(uint32_t**)((uint8_t*)this + 0x14) = ptr;
    *ptr = field0;
    *(int32_t*)((uint8_t*)this + 0x14) = (int32_t)(ptr + 1);
    **(uint32_t**)((uint8_t*)this + 0x14) = field1;
    *(int32_t*)((uint8_t*)this + 0x14) += 4;
    **(size_t**)((uint8_t*)this + 0x14) = size;
    *(int32_t*)((uint8_t*)this + 0x14) += 4;
    **(int32_t**)((uint8_t*)this + 0x14) = alignment;
    // Align to user-specified alignment and copy data
    dst = (void*)(~(alignment - 1) & (alignment + 3 + *(int32_t*)((uint8_t*)this + 0x14)));
    *(void**)((uint8_t*)this + 0x14) = dst;
    memcpy(dst, data, size);
    *(int32_t*)((uint8_t*)this + 0x14) = (int32_t)dst + ((size + 3) & 0xFFFFFFFC);
    **(uint32_t**)((uint8_t*)this + 0x14) = field2;
    *(int32_t*)((uint8_t*)this + 0x14) += 4;
}