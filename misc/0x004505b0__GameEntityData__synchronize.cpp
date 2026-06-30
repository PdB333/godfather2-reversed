// FUNC_NAME: GameEntityData::synchronize

void __thiscall GameEntityData::synchronize(void)
{
    // Clear existing data fields
    this->field_0 = 0;     // +0x00
    this->field_4 = 0;     // +0x04

    // Temporary buffer to receive 8-byte data structure
    int dataBuffer[2];

    // Retrieve synchronized data from helper; returns pointer to the buffer
    int* pData = (int*)FUN_00450c20(dataBuffer);

    // Copy the two DWORDs into the object's fields
    this->field_0 = pData[0];
    this->field_4 = pData[1];
}