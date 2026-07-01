// FUNC_NAME: GameObject::loadReferencedPair
void __fastcall GameObject::loadReferencedPair(int* thisPtr) // actually ECX -> this
{
    // Virtual call to get some progress/state (maybe time or condition)
    float10 fVar4 = (float10)(**(code **)(*(int*)thisPtr + 0xC0))();

    if (fVar4 <= 0.0f)
    {
        // Open a child resource at offset +0x08 (likely a stream or data block)
        // Function signature: int* openChildResource(void* base, int mode); mode=0 for read
        int* pStream = (int*)FUN_004461c0(thisPtr + 8, 0); // offset +8: pointer to stream object

        if (pStream != 0)
        {
            uint uItemCount = 0;
            // Seek to a specific resource identified by hash/ID 0xa7039c8
            FUN_0043aff0(pStream, 0xa7039c8);

            char bEndOfStream = FUN_0043b120(); // returns true if end of stream
            // Read up to 2 items of types 1 and 2
            while (bEndOfStream == '\0' && (uItemCount < 2))
            {
                FUN_0043b210(); // advance to next item (return value not used here)
                int iItemType = FUN_0043ab70(); // returns 1 or 2

                if (iItemType == 1)
                {
                    uItemCount = uItemCount + 1;
                    int iData = FUN_0043b210(); // read the actual data (another pointer?)
                    // Store at offset 0x85 (0x214 if int array)
                    // This is likely a pointer to some resource (e.g., model, texture)
                    thisPtr[0x85] = *(int*)(iData + 8); // dereference data+0x8? Possibly a handle
                }
                else if (iItemType == 2)
                {
                    uItemCount = uItemCount + 1;
                    int iData = FUN_0043b210();
                    thisPtr[0x86] = *(int*)(iData + 8);
                }

                FUN_0043b1a0(); // move to next item in stream
                bEndOfStream = FUN_0043b120();
            }

            // Virtual call with a global variable (probably some manager singleton)
            (**(code **)(*(int*)thisPtr + 0x154))(DAT_00d5e288);

            // If we got a type-1 item, process the pair (FUN_008b8f10)
            if (thisPtr[0x85] != 0)
            {
                FUN_008b8f10(thisPtr[0x85], thisPtr[0x86]);
                return;
            }

            // Otherwise set error flag at offset 99 (0x18c)
            thisPtr[99] |= 0x8000; // Some failure flag
        }
    }
    return;
}