// FUNC_NAME: SmallBuffer::swap
void __fastcall SmallBuffer::swap(SmallBuffer* this, SmallBuffer* other)
{
    // Swap the first two fields (likely length/size and capacity/flags)
    unsigned int temp = this->field_0;
    this->field_0 = other->field_0;
    other->field_0 = temp;

    temp = this->field_4;
    this->field_4 = other->field_4;
    other->field_4 = temp;

    // Save pointers to the inline data regions (after the 12-byte header)
    unsigned int* thisInline = &this->field_8;  // Actually offset 12? Wait, field_8 is a pointer, but inline data starts at offset 12 (this+3)
    // Structure layout:
    // +0x00: field_0 (unsigned int)
    // +0x04: field_4 (unsigned int)
    // +0x08: dataPtr (char*)
    // +0x0C: inlineData[16] (4 dwords)
    unsigned int* otherInline = &other->field_8; // Similarly

    // Save original data pointers
    unsigned int* thisOldPtr = this->dataPtr;
    unsigned int* otherOldPtr = other->dataPtr;

    // Swap data pointers, but adjust for inline buffers
    if (thisOldPtr == thisInline)
    {
        other->dataPtr = otherInline;
    }
    else
    {
        other->dataPtr = thisOldPtr;
    }

    if (otherOldPtr == otherInline)
    {
        this->dataPtr = thisInline;
    }
    else
    {
        this->dataPtr = otherOldPtr;
    }

    // If either used inline buffer, we must swap the actual inline data
    if ((thisOldPtr == thisInline) || (otherOldPtr == otherInline))
    {
        // Temporary buffer for the swap
        unsigned int tempData[4];
        tempData[0] = otherInline[0];
        tempData[1] = otherInline[1];
        tempData[2] = otherInline[2];
        tempData[3] = otherInline[3];

        // Copy this's inline data to other's inline
        otherInline[0] = thisInline[0];
        otherInline[1] = thisInline[1];
        otherInline[2] = thisInline[2];
        otherInline[3] = thisInline[3];

        // Copy temporary to this's inline
        thisInline[0] = tempData[0];
        thisInline[1] = tempData[1];
        thisInline[2] = tempData[2];
        thisInline[3] = tempData[3];
    }
}