// FUNC_NAME: NetSession::processIncomingBuffer
// Function address: 0x00978250
// Processes a 76-byte buffer from offset +0x110 when a pending flag at +0x104 is set

void __fastcall NetSession::processIncomingBuffer(int this_)
{
    char localBuffer[76];

    // Check if data is available to process (+0x104: count/flag)
    if (*(int *)(this_ + 0x104) != 0)
    {
        // Copy data from the object's buffer at +0x110 into local buffer
        FUN_00977090(this_ + 0x110, localBuffer);

        // Process the filled buffer (likely deserialize/handle packet)
        FUN_004df720(localBuffer);
    }
}