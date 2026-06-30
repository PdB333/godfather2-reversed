// FUNC_NAME: DataBuffer::~DataBuffer (destructor/cleanup at 0x00696810)
void __thiscall DataBuffer::~DataBuffer(void) {
    // local buffer (8 bytes) used for temporary storage or swap
    char local_8[8];

    // Perform potential swap or assignment before cleanup
    // Call to unknown function (likely a move or release helper)
    FUN_00695e30(local_8, this, **(int**)(this + 4), this, *(int**)(this + 4));

    // Free the data pointer at offset +4
    FUN_009c8eb0(*(int*)(this + 4));

    // Clear pointer and size/count fields
    *(int*)(this + 4) = 0;  // +0x04: data pointer
    *(int*)(this + 8) = 0;  // +0x08: size or count
}