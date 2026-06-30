// FUNC_NAME: StreamBuffer::initialize
int StreamBuffer::initialize(int param1, int param2, int param3)
{
    // Allocate 0x40 bytes for internal buffer (likely ring buffer or state struct)
    void* buffer = _calloc(4, 0x40);
    if (buffer == nullptr)
        return -2; // Allocation failure

    int result = this->internalInit(param1); // FUN_006657c0, perform initial setup
    if (result == 0)
    {
        // Buffer descriptor: start offset=0, size=0x40, flags=0
        int bufferDescriptor[3] = {0, 0x40, 0}; // local_10, local_c, local_8
        result = this->setBuffer(bufferDescriptor, param3); // FUN_00668850
    }
    this->postInit(); // FUN_00665b40, finalize initialization
    return result;
}