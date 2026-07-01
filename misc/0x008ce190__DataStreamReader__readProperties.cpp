// FUNC_NAME: DataStreamReader::readProperties
// Address: 0x008ce190
// Reads a stream of typed properties and assigns them to member fields at offsets 0x50, 0x58, 0x68.

void __thiscall DataStreamReader::readProperties(int thisPtr, undefined4 stream)
{
    char hasMore;
    int type;
    undefined4 value;

    beginRead(stream);                          // FUN_0046c710 - initialize stream
    setStreamHash(stream, 0xcc0f5b9e);          // FUN_0043aff0 - set hash for property group

    hasMore = hasMoreData();                    // FUN_0043b120
    while (hasMore == '\0') {
        readNext();                             // FUN_0043b210 - advance to next property
        type = getPropertyType();               // FUN_0043ab70 - returns 0,1,2

        if (type == 0) {
            readNext();                         // FUN_0043b210 - read property name/key?
            value = readPropertyValue();        // FUN_0043ab90 - read value
            setProperty(thisPtr + 0x50, value); // FUN_004089b0 - store at +0x50
        }
        else if (type == 1) {
            int fieldPtr = thisPtr + 0x58;
            readNext(fieldPtr);                 // FUN_0043b210 with arg
            readPropertyData(fieldPtr);         // FUN_0043ad10 - read data into +0x58
        }
        else if (type == 2) {
            int dataPtr = readNext();           // FUN_0043b210 returns pointer
            *(undefined4 *)(thisPtr + 0x68) = *(undefined4 *)(dataPtr + 8); // copy from offset 8
        }

        advanceToNextProperty();                // FUN_0043b1a0
        hasMore = hasMoreData();                // FUN_0043b120
    }
    return;
}