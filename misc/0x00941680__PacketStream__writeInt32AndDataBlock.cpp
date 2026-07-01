// FUNC_NAME: PacketStream::writeInt32AndDataBlock
void __thiscall PacketStream::writeInt32AndDataBlock(int firstValue, int data0, int data1, int data2, int data3)
{
    // Pack the four data parameters into a local array for bulk write
    int dataBlock[4];
    dataBlock[0] = data0;
    dataBlock[1] = data1;
    dataBlock[2] = data2;
    dataBlock[3] = data3;

    // Write the first 4‑byte value at the current write position
    *(int*)(this->writePtr) = firstValue;        // +0x14 is a write pointer (char*)
    this->writePtr += sizeof(int);               // advance the write pointer by 4 bytes

    // Write the remaining 16 bytes (4 ints) from the local array
    // FUN_0049c430 copies 'count' elements of 'elementSize' to the stream's internal buffer
    writeDataToStream((const void*)dataBlock, 0x10, 4);
}