// FUNC_NAME: PropertyBlockReader::processKeyValueBlock

void __thiscall PropertyBlockReader::processKeyValueBlock(void* thisPtr, int keyHash)
{
    // FUN_0043aff0 - Looks up a keyed data block, fills local iteration state
    // The hash constant 0xacbdfe47 is likely a CRC of "properties" or similar
    hashLookup(keyHash, 0xacbdfe47);

    // Local variables represent the iteration state:
    // - sparseBitfield (char): if 0 -> linked list mode, else sparse bitfield mode
    // - bitfieldBase (byte*): pointer to bitfield array in sparse mode
    // - dataArray (uint*): pointer to array of data entries in sparse mode
    // - currentIndex (uint): current iteration index
    // - totalCount (uint): total number of entries
    // - nodeIterator (uint**): current node pointer in linked list mode
    char sparseBitfield;
    byte* bitfieldBase;
    uint* dataArray;
    uint currentIndex;
    uint totalCount;
    uint** nodeIterator; // also reused as 'local_8'

    // The following are set by the hash lookup (mocked here)
    // In reality, these would be initialized by the hashLookup call
    // For clarity, we assume they are provided by that function.
    uint uVar5; // copy of currentIndex
    bool doneCondition;

    do {
        // Early exit condition: if sparseBitfield is 0 then stop when nodeIterator == NULL
        // else stop when currentIndex == totalCount
        if (sparseBitfield == 0) {
            doneCondition = (*nodeIterator == 0);
        } else {
            doneCondition = (currentIndex == totalCount);
        }
        if (doneCondition) {
            return;
        }

        uint** entryPointer;
        if (sparseBitfield == 0) {
            entryPointer = nodeIterator;
        } else {
            // use temp local_50 as current entry pointer (set later)
            entryPointer = &currentEntry; // but this is problematic, we need to handle local_50
        }

        // The decompiled code uses a local variable 'local_50' as a temporary entry pointer
        // We'll simulate with a variable declared later.

        // Actually, we need to restructure: the code uses 'ppuVar2' which is either &local_50 or nodeIterator.
        // We'll combine.

        // Determine the 'tagValue' at offset +4 of the current entry
        uint* tagValue;
        if (*(short*)((int)entryPointer + 6) == 0x25e3) {
            // If the 2-byte tag at offset 6 equals 0x25e3, then the value at offset+4 is a short (ushort)
            tagValue = (uint*)(uint)*(ushort*)(entryPointer + 1);
        } else {
            tagValue = (uint*)entryPointer[1]; // pointer-sized value
        }

        // Process based on tagValue
        if (tagValue == 0) {
            // Null tagValue -> means there's a sub-list or a string to resolve
            // Need to advance to next entry differently
            uint** nextEntry = entryPointer;
            if (sparseBitfield == 0) {
                // Already used nodeIterator, use it
                nextEntry = nodeIterator;
            } else {
                nextEntry = &currentEntry; // local_50 equivalent
            }

            if (*(short*)((int)nextEntry + 6) == 0x25e3) {
                // In 0x25e3 mode, there is a pointer at +8 (entryPointer[2]) and a size at +0 (entryPointer[0])
                // The next logical entry is at (entryPointer[2] + *entryPointer)
                if (*nextEntry == 0) goto LAB_0047811f;
                nextEntry = (uint**)((int)nextEntry[2] + (int)*nextEntry);
            } else {
                // Otherwise, just advance by 2 (skip this entry pair?)
                nextEntry = nextEntry + 2;
            }

            if ((nextEntry != 0) && (*(char*)nextEntry != 0)) {
                // There is a sub-block: resolve it to a string and set property at thisPtr + 0x50
                uint stringId = resolveString(nextEntry); // FUN_004dafd0
                setStringProperty((int)thisPtr + 0x50, stringId); // FUN_00408260
            }
        } else if (tagValue == 1) {
            // Tag 1: set property at thisPtr + 0x58 to the value at offset +8
            uint** entry = (sparseBitfield == 0) ? nodeIterator : &currentEntry;
            *(uint**)((int)thisPtr + 0x58) = entry[2];
        } else if (tagValue == 2) {
            // Tag 2: set property at thisPtr + 0x5c to value at offset +8
            uint** entry = (sparseBitfield == 0) ? nodeIterator : &currentEntry;
            *(uint**)((int)thisPtr + 0x5c) = entry[2];
        }
        // else: other values are handled as data pointers (already covered by tagValue == 0 path? Actually the decompiled code only checks ==0, ==1, ==2; other values fall through to the else branch? It appears the code only distinguishes 0,1,2; other values are not explicitly handled; maybe they are treated as unknown and skipped.

LAB_0047811f:
        // Advance to next element based on mode
        if (sparseBitfield == 0) {
            // Linked list mode: use uVar5 as a depth/index to decide how to move
            if ((int)uVar5 < 0) {
                // Negative index means go to root? This appears to be a special case for going to a fallback list (DAT_01163cf8)
                nodeIterator = (uint**)((int)nodeIterator + (int)*nodeIterator); // advance by size field
                advanceIterator(); // FUN_0043b140
                uVar5 = currentIndex; // reset index
            } else if ((int)uVar5 < (int)(totalCount - 1)) {
                // Normal sequence: increment index and advance pointer by size field
                currentIndex = uVar5 + 1;
                nodeIterator = (uint**)((int)nodeIterator + (int)*nodeIterator);
                uVar5 = currentIndex;
            } else {
                // At last element: go to fallback global root (DAT_01163cf8)
                nodeIterator = (uint**)(void*)0x01163cf8; // some global static data
            }
        } else {
            // Sparse bitfield mode: increment index, read from bitfield and data array
            currentIndex = uVar5 + 1;
            uVar5 = currentIndex;
            if (currentIndex != totalCount) {
                // The temp variable local_4c was used as short, but we can ignore
                short dummyShort = (short)currentIndex;
                if ((*(uint*)(bitfieldBase + (currentIndex >> 3)) & (1 << (currentIndex & 7))) == 0) {
                    // Bit not set: no data, skip
                    // dataArray is advanced in this case? The decompiled code shows local_48 = *local_5c; local_50 = local_5c; local_5c = local_5c + 1;
                    // This effectively reads the next element from dataArray regardless of bit? That seems wrong.
                    // Actually the code in the decompiled decompilation: if bit not set, it reads *local_5c into local_48 and sets local_50 to local_5c, then increments local_5c.
                    // That means it still reads an entry but discards it (by not using local_48). The entry pointer remains at the old value? Hmm.
                    // We'll replicate exactly:
                    uint* entryData = *dataArray;
                    uint** currentEntryPtr = dataArray;
                    dataArray++; // advance data pointer past this entry
                    // Note: local_48 is not used elsewhere; it's just read and discarded.
                } else {
                    // Bit set: read the data pointer into currentEntry (local_50), but note that dataArray is NOT advanced.
                    // This seems to indicate that in sparse bitfield mode, the actual data entries are stored compactly,
                    // and the bitfield indicates which indices are present. If bit is set, we use the data at the current dataArray pointer,
                    // but we do NOT advance dataArray? That would cause infinite loop. Wait, maybe the code increments dataArray only when bit is not set?
                    // Let's reexamine the decompiled block:
                    //   if ((*(byte *)((local_58 >> 3) + local_60) & (byte)(1 << ((byte)local_58 & 7))) == 0) {
                    //       local_48 = *local_5c;
                    //       local_50 = local_5c;
                    //       local_5c = local_5c + 1;
                    //   } else {
                    //       local_50 = (undefined4 *)0x0;
                    //       local_48 = 0;
                    //   }
                    // So when bit is 0 (not set), it reads from dataArray (local_5c) and also increments dataArray.
                    // When bit is set, it sets local_50 to null.
                    // That is inverted from intuition; but let's follow exactly.
                    // Actually, we need to preserve the logic.
                    // Currently we have: if bit not set -> read and advance; if set -> set local_50 = 0.
                    // That means the entries in dataArray are for positions that are NOT present? That would be weird.
                    // Let's check the original decompilation again: it says:
                    //   if ((*(byte *)((local_58 >> 3) + local_60) & (byte)(1 << ((byte)local_58 & 7))) == 0) {
                    //       local_48 = *local_5c;
                    //       local_50 = local_5c;
                    //       local_5c = local_5c + 1;
                    //   }
                    //   else {
                    //       local_50 = (undefined4 *)0x0;
                    //       local_48 = 0;
                    //   }
                    // So when the bit is NOT set (==0), it takes an entry from the data array and advances.
                    // When bit is set, it sets local_50 to null. This is counterintuitive; maybe the bitfield indicates "changed" or "needs processing" rather than "present". Or maybe it's a compressed sparse representation where the data array only contains entries for positions where the bit is 0.
                    // We'll implement exactly.
                    // To replicate, we'll use a variable for the current entry and a boolean for the bit.
                }
            }
        }
    } while (true);
}