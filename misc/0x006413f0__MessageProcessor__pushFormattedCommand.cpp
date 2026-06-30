// FUNC_NAME: MessageProcessor::pushFormattedCommand
void MessageProcessor::pushFormattedCommand(int param)
{
    int formatId;
    char formatBuffer[20];
    char outputBuffer[20];

    // copy previous value to current
    this->previousValue = this->currentValue;

    // check current state/message type
    if (this->messageType == 0x11f) // kMsgTypeFormatted
    {
        // retrieve format identifier from auxiliary data
        formatId = FUN_00639c70(&this->auxData);
        this->result = formatId;
    }
    else
    {
        // save current state and transition to formatted message type
        this->result = this->messageType;
        this->auxData = this->previousMessageType;
        this->messageType = 0x11f;
    }

    // obtain a system value (possibly current timestamp or sequence)
    int systemValue = FUN_00641390();

    // format a message string using the retrieved formatId and parameter
    FUN_0063f080(formatBuffer, systemValue, param);
    FUN_00643090(outputBuffer); // likely copy or finalize formatted string

    // store the parameter into an array indexed by the structure at this+0x1c
    int* array = *(int**)(this + 0x1c);       // pointer to an array structure
    int base = *array;                         // base address for the storage
    int* storage = (int*)(base + 0x14);        // point to the actual array
    int writeIndex = array[6];                 // current write index (element 6)
    storage[writeIndex - 1] = param;           // (-4 + writeIndex*4) -> offset to (writeIndex-1)*4
}