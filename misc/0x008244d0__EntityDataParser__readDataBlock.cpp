// FUNC_NAME: EntityDataParser::readDataBlock
// Function address: 0x008244d0
// Reads a binary data block from a stream, parsing entries of type 0 (float4) or type 1 (integer).
// The object's mFloatData (offset +0x4c) and mIntData (offset +0x64) are set.
void __thiscall EntityDataParser::readDataBlock(void *this, void *dataStream)
{
    bool hasFloatData;
    char done;
    int type;
    undefined4 *floatDataPtr;
    
    // Initialize the stream
    BinaryStream::init(dataStream);
    // Set hash key for lookup (0xe4599969)
    HashTable::setKey(dataStream, 0xe4599969);
    
    hasFloatData = false;
    done = HashTable::isEnd(dataStream); // FUN_0043b120
    if (done == '\0') {
        do {
            // Advance to next entry
            BinaryStream::nextEntry(dataStream); // FUN_0043b210
            type = BinaryStream::getValueType(dataStream); // FUN_0043ab70: returns 0 or 1?
            if (type == 0) {
                // Read float block (4 floats)
                BinaryStream::nextEntry(dataStream); // advance again to float data
                floatDataPtr = (undefined4 *)BinaryStream::getDataPointer(dataStream); // FUN_0043abc0
                *(undefined4 *)((int)this + 0x4c) = floatDataPtr[0]; // mFloatData.x
                *(undefined4 *)((int)this + 0x50) = floatDataPtr[1]; // mFloatData.y
                *(undefined4 *)((int)this + 0x54) = floatDataPtr[2]; // mFloatData.z
                *(undefined4 *)((int)this + 0x58) = floatDataPtr[3]; // mFloatData.w
                hasFloatData = true;
            }
            else if (type == 1) {
                // Read integer from a referenced block
                int temp = BinaryStream::nextEntry(dataStream); // returns a pointer?
                *(undefined4 *)((int)this + 100) = *(undefined4 *)(temp + 8); // mIntData
            }
            // Advance to next element
            BinaryStream::advanceEntry(dataStream); // FUN_0043b1a0
            done = HashTable::isEnd(dataStream);
        } while (done == '\0');
        
        if (hasFloatData) {
            // Callback after float data is set
            EntityDataParser::onFloatDataLoaded(); // FUN_008242d0
        }
    }
    return;
}