// FUNC_NAME: GhostManager::processPacket
// Function address: 0x004c1550
// Role: Receives and processes incoming network packet for ghost state synchronization.
// Based on decompiled output with meaningful identifiers.

void __thiscall GhostManager::processPacket(int *this, Stream *stream)
{
    undefined4 *dataItem;
    undefined4 **currentList;
    int vtableEntry;
    int flags;
    int canProcess;
    bool isAtEnd;
    bool dataExists;
    char isCompact;
    int bitmaskBuffer; // points to bitmask for compact format
    undefined4 *dataArray; // array of data for pointer-based format
    uint currentIndex;
    uint totalItems;
    undefined4 *currentItem;
    unsigned short compactIndex;
    undefined4 nextData;
    undefined4 **listPtr; // pointer into list during iteration

    // Initialize stream deserialization
    FUN_0046f160(stream); // beginRead
    FUN_0043aff0(stream, 0xb390b11a); // readTag
    FUN_0043af00(1); // readBoolean -> sets isCompact? (stack variable not explicit)

    // Determine iteration format: pointer-based list if compact, else indexed array with bitmask
    if (isCompact == '\0') {
        dataExists = (listPtr != nullptr);
    } else {
        dataExists = (currentIndex == totalItems);
    }

    if (!dataExists) {
        FUN_0043ac60(this + 0x60); // clearList(this->mList +0x60)
    }

    FUN_0043aff0(stream, 0xd16a98a9); // readTag

    listPtr = reinterpret_cast<undefined4**>(stackVar); // from stack
    currentIndex = stackVar.upper;
    do {
        // Check end-of-list condition based on format
        if (isCompact == '\0') {
            isAtEnd = (*listPtr == nullptr);
        } else {
            isAtEnd = (currentIndex == totalItems);
        }

        if (isAtEnd) {
            // End of packet: handle final updates
            currentIndex = this[0x71]; // flags
            if (((currentIndex & 8) != 0) &&
                (canProcess = FUN_0043d0d0(this + 8, 0x9bc8a380, 0xffffffff), canProcess != 0) &&
                (*(int *)(canProcess + 0xc) != 0)) {
                this[0x7e] = *(int *)(canProcess + 0xc); // set some pointer
                FUN_004c14f0((*(uint *)(canProcess + 0x10) ^ currentIndex) & 1 ^ currentIndex); // updateFlags
            }
            if ((!dataExists) && ((**(code **)(*this + 0x154))(this) != 0) && ((this[0x71] & 1) == 0)) {
                FUN_004c2130(); // requestFullUpdate?
            }
            return;
        }

        // Read next item type
        if (isCompact == '\0') {
            currentItem = listPtr; // pointer list
        } else {
            // Compact format: use raw pointer from stack
            currentItem = nullptr; // placeholder, actually set below
        }

        // Determine the type of this data item
        undefined4 *typeId;
        if (isCompact == '\0') {
            if (*(short *)((int)currentItem + 6) == 0x25e3) {
                typeId = (undefined4 *)(uint)*(ushort *)(currentItem + 1);
            } else {
                typeId = currentItem[1];
            }
        } else {
            // Compact format: type comes from nextData (read earlier)
            typeId = (undefined4 *)(uint)(nextData & 0xFF); // not exactly, but simplified
        }

        switch ((int)typeId) {
        case 0: // Ghost pointer 0
            if (isCompact == '\0') {
                if (*(short *)((int)currentItem + 6) == 0x25e3) {
                    if (*currentItem == nullptr)
                        currentItem = (undefined4 *)&DAT_00e2a89b; // null sentinel
                    else
                        currentItem = (undefined4 *)((int)currentItem[2] + (int)*currentItem);
                } else {
                    currentItem += 2;
                }
            } else {
                // Compact: read from bitmask
                // (complex bitmask logic skipped)
            }
            FUN_00473ec0(this + 0x73, currentItem, "BasePtrMsgData*"); // setGhostPtr0
            break;

        case 1: // Ghost pointer 1
            // Similar to case 0 but offset 0x75
            // ... 
            FUN_00473ec0(this + 0x75, currentItem, "BasePtrMsgData*");
            break;

        case 2: // Ghost pointer 2
            // Similar, offset 0x77
            // ...
            FUN_00473ec0(this + 0x77, currentItem, "BasePtrMsgData*");
            break;

        case 3: // Value
            this[0x7f] = (int)currentItem[2]; // set mValue3
            break;

        case 4: // String value
            // From both formats
            if (currentItem != nullptr && *(char *)currentItem != '\0') {
                uint hash = FUN_004dafd0(currentItem); // stringHash
                FUN_00408260(this + 0x79, hash); // setString
            }
            break;

        case 5: // Integer value
            this[0x7d] = (int)currentItem[2];
            break;

        case 6: // Another integer
            this[0x7e] = (int)currentItem[2];
            break;

        case 7: // Another string
            // Similar to case 4 but offset 0x7b
            // ...
            break;

        case 8: // Special flag update
            FUN_004c14f0(currentItem[2]); // setFlag
            currentIndex = currentIndex; // update local
            break;

        case 9: // Toggle streaming flag
            if (currentItem[2] == 1) {
                this[0x71] |= 0x20; // set bit 5
                if (this[0x70] == 0) {
                    int alloc = FUN_009c8e50(0x18); // allocate
                    if (alloc != 0) {
                        int obj = FUN_004c0d70(); // construct
                        this[0x70] = obj;
                    }
                }
            } else {
                this[0x71] &= ~0x20; // clear bit 5
                if (this[0x70] != 0) {
                    FUN_004c1080(); // destroy
                    this[0x70] = 0;
                }
                FUN_004086d0(&DAT_012069c4); // reset buffer
            }
            break;

        case 10: // Another integer
            this[0x72] = (int)currentItem[2];
            break;

        case 11: // Scaled squared value
            this[0x83] = (int)((float)currentItem[2] * _DAT_00e4498c * (float)currentItem[2] * _DAT_00e4498c);
            break;
        }

        // Advance to next item
        if (isCompact == '\0') {
            if ((int)currentIndex < 0) {
                listPtr = (undefined4 **)((int)listPtr + (int)*listPtr);
                FUN_0043b140(); // advance
                uVar6 = currentIndex; // update?
            } else if ((int)currentIndex < (int)(totalItems - 1)) {
                currentIndex++;
                listPtr = (undefined4 **)((int)listPtr + (int)*listPtr);
            } else {
                listPtr = (undefined4 **)&DAT_01163cf8; // end sentinel
            }
        } else {
            // Compact: advance index, read next bitmask entry
            currentIndex++;
            if (currentIndex != totalItems) {
                compactIndex = (short)currentIndex;
                if ((*(byte *)((currentIndex >> 3) + bitmaskBuffer) & (byte)(1 << (currentIndex & 7))) == 0) {
                    nextData = *dataArray; // read from data array
                    // currentItem = dataArray? 
                    dataArray = dataArray + 1;
                } else {
                    // Null entry
                }
            }
        }
    } while (true);
}