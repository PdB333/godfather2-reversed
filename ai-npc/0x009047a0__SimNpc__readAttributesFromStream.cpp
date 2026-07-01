// FUNC_NAME: SimNpc::readAttributesFromStream
// Address: 0x009047a0
// Reads 4 DWORD attributes from a binary stream (token-based parser) and sets a loaded flag.

void __thiscall SimNpc::readAttributesFromStream(int thisPtr, int stream)
{
    char hasMore;

    // Initialize stream with given source
    streamOpen(stream);
    // Set expected magic/hash for this data block (0xf26bb307)
    streamSetMagic(stream, 0xf26bb307);

    hasMore = streamHasMoreData(stream);
    while (hasMore == 0) { // While there is more data
        int token = streamReadToken(stream);
        int tokenType = streamGetTokenType(stream); // returns 0..3

        switch(tokenType) {
        case 0:
        {
            int valueToken = streamReadToken(stream);
            // Store attribute 0 (offset 0x230)
            *(int *)(thisPtr + 0x230) = *(int *)(valueToken + 8);
            break;
        }
        case 1:
        {
            int valueToken = streamReadToken(stream);
            // Store attribute 1 (offset 0x234)
            *(int *)(thisPtr + 0x234) = *(int *)(valueToken + 8);
            break;
        }
        case 2:
        {
            int valueToken = streamReadToken(stream);
            // Store attribute 2 (offset 0x238)
            *(int *)(thisPtr + 0x238) = *(int *)(valueToken + 8);
            break;
        }
        case 3:
        {
            int valueToken = streamReadToken(stream);
            // Store attribute 3 (offset 0x23c)
            *(int *)(thisPtr + 0x23C) = *(int *)(valueToken + 8);
            break;
        }
        }

        streamAdvanceToken(stream);
        hasMore = streamHasMoreData(stream);
    }

    // Set the loaded flag (bit 0) at offset +0x210
    *(unsigned short *)(thisPtr + 0x210) |= 1;
}