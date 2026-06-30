// FUNC_NAME: SomeObject::getResourceHandle
// Address: 0x00752dc0
// This function retrieves a resource handle (type 0x2001) from an object's data block.
// Offsets: +0x60 - pointer to internal data block
//          +0x10 - validity check byte/self-pointer within data block

int SomeObject::getResourceHandle()
{
    int* dataBlock = *(int**)(this + 0x60); // +0x60: pointer to data block
    int result = 0;

    if (dataBlock != nullptr)
    {
        // Validity check: reads a char at offset 0x10 and adds the pointer base.
        // If the sum is non-zero, the data block is considered valid.
        // This is likely an EA EARS object integrity check.
        if (*(char*)((int)dataBlock + 0x10) + (int)dataBlock != 0)
        {
            int handleBuffer[2]; // buffer to hold the handle
            // Call helper function to obtain handle of type 0x2001
            // FUN_004af8c0 is assumed to be e.g. "getHandleForType"
            getHandleForType(handleBuffer, 0x2001);
            if (handleBuffer[0] != 0)
            {
                result = handleBuffer[0];
            }
        }
    }
    return result;
}