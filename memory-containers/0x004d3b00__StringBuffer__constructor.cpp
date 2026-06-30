// FUNC_NAME: StringBuffer::constructor
int* __fastcall StringBuffer::constructor(int* this)
{
    int size;
    void* buffer;
    char local_20[32]; // temporary buffer used for initialization (likely empty or template)

    size = FUN_004d47e0(); // get the default buffer size
    this[1] = size;       // +4: allocatedSize
    this[2] = size;       // +8: currentSize (initially same as allocated)
    buffer = (void*)FUN_009c8e50(size + 1); // allocate memory for string data (+1 for null)
    this[0] = (int)buffer; // +0: data pointer
    memcpy(buffer, local_20, size); // copy whatever is in local_20 (likely zero) as initial content
    *(char*)(this[0] + this[1]) = 0; // null-terminate at the end of allocated region
    this[3] = (int)thunk_FUN_009c8eb0; // +12: destructor function pointer (deallocation callback)
    return this;
}