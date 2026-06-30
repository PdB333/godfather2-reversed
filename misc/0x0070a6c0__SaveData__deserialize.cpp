// FUNC_NAME: SaveData::deserialize

void __thiscall SaveData::deserialize(int thisPtr, int streamHandle)
{
    BinaryReader reader;
    readerInit(&reader, streamHandle, 0xf26fb813);
    
    while (!readerIsFinished(&reader))
    {
        int tokenType = readerGetTokenType(&reader);
        switch (tokenType)
        {
        case 0:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x300) = *(int*)(token + 8);
            break;
        }
        case 1:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x2f8) = *(int*)(token + 8);
            break;
        }
        case 2:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x2e0) = *(int*)(token + 8);
            break;
        }
        case 3:
        {
            Token* token = readerReadToken(&reader);
            int value = *(int*)(token + 8);
            if (value == 0)
                *(int*)(thisPtr + 0x304) = 5;
            else if (value == 1)
                *(int*)(thisPtr + 0x304) = 4;
            else if (value == 2)
                *(int*)(thisPtr + 0x304) = 1;
            break;
        }
        case 4:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x2f0) = *(int*)(token + 8);
            break;
        }
        case 5:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x2e4) = *(int*)(token + 8);
            break;
        }
        case 6:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x2e8) = *(int*)(token + 8);
            break;
        }
        case 7:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x2ec) = *(int*)(token + 8);
            break;
        }
        case 8:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x2f4) = *(int*)(token + 8);
            break;
        }
        case 9:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x354) = *(int*)(token + 8);
            break;
        }
        case 0xa:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x358) = *(int*)(token + 8);
            break;
        }
        case 0xb:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x35c) = *(int*)(token + 8);
            break;
        }
        case 0xc:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x360) = *(int*)(token + 8);
            break;
        }
        case 0xd:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x308) = *(int*)(token + 8);
            break;
        }
        case 0xe:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x30c) = *(int*)(token + 8);
            break;
        }
        case 0xf:
        {
            Token* token = readerReadToken(&reader);
            *(int*)(thisPtr + 0x310) = *(int*)(token + 8);
            break;
        }
        case 0x10:
        {
            Token* token = readerReadToken(&reader);
            *(bool*)(thisPtr + 0x39c) = *(int*)(token + 8) != 0;
            break;
        }
        case 0x11:
        {
            readerReadToken(&reader);
            float* vec = readerReadVector4(&reader);
            *(float*)(thisPtr + 0x314) = vec[0];
            *(float*)(thisPtr + 0x318) = vec[1];
            *(float*)(thisPtr + 0x31c) = vec[2];
            *(float*)(thisPtr + 0x320) = vec[3];
            break;
        }
        case 0x12:
        {
            readerReadToken(&reader);
            float* vec = readerReadVector4(&reader);
            *(float*)(thisPtr + 0x324) = vec[0];
            *(float*)(thisPtr + 0x328) = vec[1];
            *(float*)(thisPtr + 0x32c) = vec[2];
            *(float*)(thisPtr + 0x330) = vec[3];
            break;
        }
        case 0x13:
        {
            readerReadToken(&reader);
            int stringHandle = readerReadString(&reader);
            stringCopy(thisPtr + 0x388, stringHandle);  // string buffer at +0x388
            break;
        }
        case 0x14:
        {
            // sub‑data block at +0x364
            int subDataAddr = thisPtr + 0x364;
            readerReadToken(subDataAddr);                // note: token read into subDataAddr?
            readerReadSubData(subDataAddr);              // parse sub‑structure
            break;
        }
        case 0x15:
        {
            readerReadToken(&reader);
            int stringHandle = readerReadString(&reader);
            stringCopy(thisPtr + 0x390, stringHandle);  // string buffer at +0x390
            break;
        }
        }
        readerAdvance(&reader);
    }
}