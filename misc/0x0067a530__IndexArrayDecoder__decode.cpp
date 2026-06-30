// FUNC_NAME: IndexArrayDecoder::decode
void __thiscall IndexArrayDecoder::decode(uint4 **inputBuffer, byte flags, short defaultShort) {
    byte *dataPtr = (byte *)*inputBuffer; // current position in input stream
    int *pEntries = (int *)FUN_00673070(); // allocate entry array
    this->pEntries = pEntries;

    // Initialize entries to defaults
    short count = *(short *)(this + 0x42);
    for (int i = 0; i < count; i++) {
        *(ushort *)(pEntries + i * 8 + 0) = 0xFFFF; // index
        *(ushort *)(pEntries + i * 8 + 2) = 0;      // some value
        *(int *)(pEntries + i * 8 + 4) = 0;          // data
    }

    short elementCount = *(short *)(this + 0x42); // number of elements
    int handle = *(int *)this;                     // original handle stored at this+0
    *(ushort *)(this + 0x7a) = 0xFFFF;             // minIndex
    *(ushort *)((int)this + 0x1ea) = 0;            // maxIndex

    // Allocate index table
    IndexTable *pTable = (IndexTable *)FUN_00673070();
    pTable->handle = handle;
    pTable->count1 = elementCount;
    pTable->count2 = elementCount;
    pTable->pSomething = (void *)FUN_00673070(); // another allocation
    pTable->pShortArray = (short *)FUN_00673070();
    this->pIndexTable = pTable;
    this->pIndexTableAlt = pTable;

    int currentIndex = 0;   // running index (short)
    short currentValue = 0; // running value (short)
    int currentData = 0;    // running data (int)

    if (elementCount <= 0) {
        *inputBuffer = (uint4 *)dataPtr;
        return;
    }

    for (int i = 0; i < elementCount; i++) {
        if (*(char *)(this + 0x02) == '\0') { // uncompressed format
            ushort index;
            short value;
            int data;
            // Read index based on flags
            if ((flags & 2) == 0) {
                index = (ushort)*dataPtr;
                dataPtr += 1;
            } else {
                index = CONCAT11(dataPtr[0], dataPtr[1]);
                dataPtr += 2;
            }
            *(ushort *)(pEntries + i * 8 + 0) = index;

            // Read value
            if ((flags & 4) != 0) {
                byte b1 = dataPtr[0];
                dataPtr += 1;
                value = CONCAT11(b1, dataPtr[0]);
                dataPtr += 1;
            } else {
                value = defaultShort;
            }
            *(short *)(pTable->pShortArray + i) = value;
            currentValue = *(short *)(pTable->pShortArray + i);

            // Skip optional byte
            if ((flags & 8) != 0) {
                dataPtr += 1;
            }

            // Read data
            if ((flags & 0x10) == 0) {
                data = (ushort)*dataPtr;
                dataPtr += 1;
            } else {
                data = CONCAT11(dataPtr[0], dataPtr[1]);
                dataPtr += 2;
            }
            *(ushort *)(pEntries + i * 8 + 2) = data;

            if ((flags & 0x20) == 0) {
                dataPtr += 2;
                data = (ushort)(dataPtr[-2] * 0x100 + dataPtr[-1]);
            } else {
                dataPtr += 3;
                data = (uint)(CONCAT21(CONCAT11(dataPtr[-3], dataPtr[-2]), dataPtr[-1]));
            }
            *(int *)(pEntries + i * 8 + 4) = data;
            goto updateMinMax;
        } else { // compressed format
            byte control = *dataPtr;
            dataPtr += 1;
            ushort index;
            // Decode index based on control bits [0:1]
            if ((control & 3) == 0) {
                *(short *)(pEntries + i * 8 + 0) = currentIndex;
            } else if ((control & 3) == 1) {
                *(ushort *)(pEntries + i * 8 + 0) = (ushort)*dataPtr + currentIndex;
                dataPtr += 1;
            } else if ((control & 3) == 2) {
                byte b1 = dataPtr[0];
                dataPtr += 1;
                *(ushort *)(pEntries + i * 8 + 0) = (ushort)b1 * 0x100 + dataPtr[0] + currentIndex;
                dataPtr += 1;
            }
            currentIndex = *(short *)(pEntries + i * 8 + 0) + 1;

            // Decode value based on control bits [2:3]
            switch ((control >> 2) & 3) {
            case 0:
                *(short *)(pTable->pShortArray + i) = currentValue;
                break;
            case 1:
                currentValue = (ushort)*dataPtr + currentValue;
                dataPtr += 1;
                goto setValue;
            case 2:
                *(ushort *)(pTable->pShortArray + i) = currentValue - (ushort)*dataPtr;
                dataPtr += 1;
                break;
            case 3:
                byte b1 = dataPtr[0];
                dataPtr += 1;
                currentValue = (ushort)b1 * 0x100 + dataPtr[0];
                dataPtr += 1;
setValue:
                *(short *)(pTable->pShortArray + i) = currentValue;
                break;
            }
            currentValue = *(short *)(pTable->pShortArray + i);

            // Decode data field (stored at offset 2 of entries) based on control bits [4:5]
            ushort dataLow;
            switch ((control >> 4) & 3) {
            case 0:
                dataLow = (ushort)*dataPtr;
                dataPtr += 1;
                break;
            case 1:
                dataLow = *dataPtr + 0x100;
                dataPtr += 1;
                break;
            case 2:
                dataLow = *dataPtr + 0x200;
                dataPtr += 1;
                break;
            case 3:
                byte b1 = dataPtr[0];
                dataPtr += 1;
                dataLow = (ushort)b1 * 0x100 + dataPtr[0];
                dataPtr += 1;
                break;
            }
            *(ushort *)(pEntries + i * 8 + 2) = dataLow;

            // Decode data high (int at offset 4) based on control bits [6:7]
            int dataHigh;
            switch ((control >> 6) & 3) {
            case 0:
                dataHigh = currentData;
                break;
            case 1:
                dataHigh = (uint)*dataPtr + currentData;
                dataPtr += 1;
                goto setData;
            case 2:
                dataHigh = (uint)*dataPtr;
                dataPtr += 2;
                goto setData2;
            case 3:
                byte b1 = dataPtr[0];
                dataPtr += 1;
                dataHigh = (uint)CONCAT11(b1, dataPtr[0]);
                dataPtr += 3;
setData2:
                dataHigh = dataHigh * 0x100 + dataPtr[-1];
setData:
                *(int *)(pEntries + i * 8 + 4) = dataHigh;
                break;
            }
            currentData = *(ushort *)(pEntries + i * 8 + 2) + *(int *)(pEntries + i * 8 + 4);
        }

updateMinMax:
        // Update max delta (offset 0x48)
        if ((int)this[0x48] < currentValue) {
            this[0x48] = currentValue;
        }
        // Update min index (offset +0x7a)
        ushort newIndex = *(ushort *)(pEntries + i * 8 + 0);
        if (newIndex < *(ushort *)(this + 0x7a)) {
            *(ushort *)(this + 0x7a) = newIndex;
        }
        // Update max index (offset +0x1ea)
        if (*(ushort *)((int)this + 0x1ea) < newIndex) {
            *(ushort *)((int)this + 0x1ea) = newIndex;
        }
    }

    *inputBuffer = (uint4 *)dataPtr;
    return;
}