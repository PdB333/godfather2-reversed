// FUNC_NAME: DeltaArrayReader::readCompressedArray
void DeltaArrayReader::readCompressedArray(byte*& stream, byte flags, ushort defaultVal)
{
    byte* pbStream = *stream; // current read position
    int* pEntryArray = allocateMemory(); // FUN_00673070
    this->entryArray = pEntryArray; // +0x0C

    // Initialize entry array with defaults
    short count = this->count; // +0x42
    for (int i = 0; i < count; i++)
    {
        *(short*)(pEntryArray + i * 2) = 0xFFFF; // index
        *(short*)(pEntryArray + i * 2 + 1) = 0;   // value
        *(int*)(pEntryArray + i * 2 + 2) = 0;     // extra
    }

    // Initialize min/max
    this->minIndex = 0xFFFF; // +0x7a
    this->maxIndex = 0;      // +0x1ea

    // Allocate delta state structure
    int* pDeltaState = allocateMemory(); // FUN_00673070
    pDeltaState[0] = this->someValue; // *this (first field)
    pDeltaState[1] = count;
    pDeltaState[2] = count;
    pDeltaState[3] = allocateMemory(); // pointer to array of shorts
    pDeltaState[4] = allocateMemory(); // pointer to another array
    this->deltaState = pDeltaState; // +0x40
    this->deltaState2 = pDeltaState; // +0x41

    int prevIndex = 0;
    short prevValue = 0;
    int prevExtra = 0;
    int maxValue = 0;

    for (int i = 0; i < count; i++)
    {
        if (this->flag == 0) // +0x02 (some flag)
        {
            // Raw encoding based on flags
            ushort index;
            if ((flags & 2) == 0)
            {
                index = *pbStream;
                pbStream++;
            }
            else
            {
                index = *(ushort*)pbStream;
                pbStream += 2;
            }
            *(short*)(pEntryArray + i * 2) = index;

            ushort value = defaultVal;
            if ((flags & 4) != 0)
            {
                value = *(ushort*)pbStream;
                pbStream += 2;
            }
            *(short*)(pDeltaState[3] + i * 2) = value;
            prevValue = *(short*)(pDeltaState[3] + i * 2);

            if ((flags & 8) != 0)
                pbStream++;

            ushort extra;
            if ((flags & 0x10) == 0)
            {
                extra = *pbStream;
                pbStream++;
            }
            else
            {
                extra = *(ushort*)pbStream;
                pbStream += 2;
            }
            *(short*)(pEntryArray + i * 2 + 1) = extra;

            uint extra2;
            if ((flags & 0x20) == 0)
            {
                extra2 = *(ushort*)pbStream;
                pbStream += 2;
            }
            else
            {
                extra2 = *(uint*)pbStream;
                pbStream += 3;
            }
            *(int*)(pEntryArray + i * 2 + 2) = extra2;

            goto updateMinMax;
        }

        // Compressed delta encoding
        byte control = *pbStream;
        pbStream++;

        // Decode index delta
        switch (control & 3)
        {
        case 0:
            *(short*)(pEntryArray + i * 2) = prevIndex;
            break;
        case 1:
            *(ushort*)(pEntryArray + i * 2) = *pbStream + prevIndex;
            pbStream++;
            break;
        case 2:
            *(ushort*)(pEntryArray + i * 2) = (*(ushort*)pbStream) + prevIndex;
            pbStream += 2;
            break;
        }
        prevIndex = *(short*)(pEntryArray + i * 2) + 1;

        // Decode value delta
        switch ((control >> 2) & 3)
        {
        case 0:
            *(short*)(pDeltaState[3] + i * 2) = prevValue;
            break;
        case 1:
            prevValue = *pbStream + prevValue;
            pbStream++;
            *(short*)(pDeltaState[3] + i * 2) = prevValue;
            break;
        case 2:
            *(ushort*)(pDeltaState[3] + i * 2) = prevValue - *pbStream;
            pbStream++;
            break;
        case 3:
            prevValue = *(ushort*)pbStream;
            pbStream += 2;
            *(short*)(pDeltaState[3] + i * 2) = prevValue;
            break;
        }
        prevValue = *(short*)(pDeltaState[3] + i * 2);

        // Decode extra field
        ushort extra;
        switch ((control >> 4) & 3)
        {
        case 0:
            extra = *pbStream;
            pbStream++;
            break;
        case 1:
            extra = *pbStream + 0x100;
            pbStream++;
            break;
        case 2:
            extra = *pbStream + 0x200;
            pbStream++;
            break;
        case 3:
            extra = *(ushort*)pbStream;
            pbStream += 2;
            break;
        }
        *(ushort*)(pEntryArray + i * 2 + 1) = extra;

        // Decode extra2 field
        switch (control >> 6)
        {
        case 0:
            *(int*)(pEntryArray + i * 2 + 2) = prevExtra;
            break;
        case 1:
            prevExtra = *pbStream + prevExtra;
            pbStream++;
            *(int*)(pEntryArray + i * 2 + 2) = prevExtra;
            break;
        case 2:
            prevExtra = *pbStream * 0x100 + *(pbStream+1);
            pbStream += 2;
            *(int*)(pEntryArray + i * 2 + 2) = prevExtra;
            break;
        case 3:
            prevExtra = *(ushort*)pbStream;
            pbStream += 3;
            *(int*)(pEntryArray + i * 2 + 2) = prevExtra;
            break;
        }
        prevExtra = *(ushort*)(pEntryArray + i * 2 + 1) + *(int*)(pEntryArray + i * 2 + 2);

updateMinMax:
        // Update max value
        if (maxValue < prevValue)
            maxValue = prevValue;
        this->maxValue = maxValue; // +0x48

        // Update min/max index
        ushort idx = *(ushort*)(pEntryArray + i * 2);
        if (idx < this->minIndex)
            this->minIndex = idx;
        if (this->maxIndex < idx)
            this->maxIndex = idx;
    }

    // Update stream pointer
    *stream = pbStream;
}