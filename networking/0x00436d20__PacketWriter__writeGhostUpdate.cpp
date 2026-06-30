// FUNC_NAME: PacketWriter::writeGhostUpdate
undefined4 PacketWriter::writeGhostUpdate(void) {
    int *writePtr;
    int *payloadPtr;
    int *endPtr;
    int *chunkType;
    int iVar4;
    int *unaff_EBX;
    int iVar5;
    int *fieldPtr;
    double fVar7;
    double fVar8;
    int *tmpPtr;
    int offsetOrSize;
    longlong longVal;
    int fieldBuffer[8]; // local_28 through local_c (8 ints)

    writePtr = *(int **)(this + 0xC); // current write position in buffer
    endPtr = *(int **)(this + 0x8);  // end of buffer
    iVar5 = 0;

    // Check if there is room for a chunk header (type 4 or 3) and if the chunk data is present
    if ((writePtr < endPtr) && (writePtr != nullptr) && 
        ((chunkType = (int *)*writePtr, *chunkType == 4) || (*chunkType == 3))) 
    {
        // Read the data size from the chunk header
        if (writePtr < endPtr && writePtr != nullptr) {
            if (*chunkType == 4) {
                offsetOrSize = writePtr[1] + 0x10; // +0x10 for some alignment?
            } else { // type 3
                iVar5 = FUN_00633990(this); // check if we can serialize (returns 0 or non-zero)
                if (iVar5 == 0) {
                    offsetOrSize = 0;
                } else {
                    offsetOrSize = writePtr[1] + 0x10;
                }
                if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
                    FUN_00627360(); // some error/assertion
                }
            }
        } else {
            offsetOrSize = 0;
        }

        iVar5 = *(int *)(this + 0xC); // re-read current write position
        endPtr = *(int **)(this + 0x8);
        chunkType = (int *)(iVar5 + 0x20); // next field offset in the source data

        // Check if there is room for a field at offset +0x20 (type 7 or 2)
        if ((endPtr <= chunkType) || (chunkType == nullptr) ||
            ((iVar4 = *chunkType, iVar4 != 7) && (iVar4 != 2))) {
            return 0;
        }

        if ((chunkType < endPtr) && (chunkType != nullptr)) {
            if (iVar4 == 2) {
                fieldPtr = *(int **)(iVar5 + 0x24); // pointer at +0x24
            } else if (iVar4 == 7) {
                fieldPtr = (int *)(*(int *)(iVar5 + 0x24) + 0x10); // pointer + 0x10
            } else {
                fieldPtr = nullptr;
            }
        } else {
            fieldPtr = nullptr;
        }

        chunkType = (int *)(iVar5 + 0x18); // another field offset
        fieldBuffer[0] = 0;
        fieldBuffer[1] = 0;
        fieldBuffer[2] = 0;
        fieldBuffer[3] = 0;
        fieldBuffer[4] = 0;
        fieldBuffer[5] = 0;
        fieldBuffer[7] = 0; // note: local_10 is index 6? Actually order: local_28(0), local_24(1), local_20(2), local_1c(3), local_18(4), local_14(5), local_10(6), local_c(7)
        fieldBuffer[6] = 0;

        // Check field at +0x18 (type 1) and set a flag in fieldBuffer[3]
        if ((((chunkType < endPtr) && (chunkType != nullptr)) && (*chunkType == 1)) &&
            ((chunkType < endPtr && (chunkType != nullptr)))) {
            if ((*chunkType != 0) && ((*chunkType != 1 || (*(int *)(iVar5 + 0x1c) != 0)))) {
                fieldBuffer[3] = 1; // local_1c = 1
            }
        }

        chunkType = (int *)(iVar5 + 0x28); // another field offset
        tmpPtr = fieldPtr;
        if (((chunkType < endPtr) && (chunkType != nullptr)) &&
            ((*chunkType == 3) || ((*chunkType == 4 && 
                                   (iVar5 = FUN_00636850(&longVal), tmpPtr = fieldPtr, iVar5 != 0))))) 
        {
            tmpPtr = fieldPtr;
            fVar7 = (double)FUN_006259b0(this, 6); // get float field (index 6)
            longVal = (longlong)ROUND(fVar7);
            fieldBuffer[0] = (int)longVal; // store in first element of fieldBuffer
        }

        iVar5 = (**(code **)(*tmpPtr + 0xAC))(offsetOrSize, &fieldBuffer); // call virtual function on the source object
        if (iVar5 != 0) {
            // After building the payload, process additional fields
            chunkType = (int *)(*(int *)(this + 0xC) + 0x10);
            if (((chunkType < endPtr) && (chunkType != nullptr)) &&
                ((*chunkType == 3) || ((*chunkType == 4 && 
                                       (iVar4 = FUN_00636850(&tmpPtr), tmpPtr = unaff_EBX, iVar4 != 0))))) 
            {
                fVar7 = (double)FUN_006259b0(this, 3); // get float field (index 3)
                fVar8 = (double)(**(code **)(*tmpPtr + 0x110))(); // call another virtual
                chunkType = DAT_00e2cb90; // some global float?
                if (((float)chunkType < (float)fVar8) &&
                    (fVar8 = (double)(**(code **)(*tmpPtr + 0x110))(), chunkType = DAT_00e2b1a4,
                     fVar8 < 1.0)) {
                    fVar8 = (double)(**(code **)(*tmpPtr + 0x110))();
                    tmpPtr = (int *)(float)fVar8;
                    chunkType = tmpPtr;
                }
                FUN_005e6750(iVar5, (float)chunkType * (float)fVar7); // set some property
            }

            FUN_005e67c0(iVar5, DAT_0110ac04); // set another property

            chunkType = (int *)(*(int *)(this + 0xC) + 8);
            if (((chunkType < endPtr) && (chunkType != nullptr)) &&
                ((*chunkType == 3) || ((*chunkType == 4 && 
                                       (iVar4 = FUN_00636850(&tmpPtr), iVar4 != 0))))) 
            {
                fVar7 = (double)FUN_006259b0(this, 2); // get float field (index 2)
                FUN_005e6700(iVar5, (float)fVar7); // set float property
            }
        }
    }

    // Write the chunk header to the packet buffer
    payloadPtr = *(int **)(this + 0x8); // end pointer (write destination)
    *payloadPtr = 2;                    // chunk type = 2 (ghost update)
    payloadPtr[1] = iVar5;             // store the payload handle
    *(int *)(this + 0x8) = *(int *)(this + 0x8) + 8; // advance end pointer by 8 bytes (chunk header size)
    return 1;
}