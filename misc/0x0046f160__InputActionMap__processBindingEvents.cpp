// FUNC_NAME: InputActionMap::processBindingEvents
// Address: 0x0046f160
// Role: Processes a list of input binding definitions (events/actions) and updates state flags and triggers virtual callbacks.
// This function iterates over either a compact bit-packed list or a pointer list of binding entries.
// Each entry has a type field (offset +6) and a subtype (puVar1 derived from entry).
// Types 0-4 correspond to different action categories:
//   0 = state/bool flag updates (pressed/released/toggle etc.)
//   1 = action trigger (e.g., button pressed) -> calls virtual[0xf0] to handle
//   2 = axis/movement -> sends to a central manager (DAT_01223414) via FUN_0043c390
//   3 = toggle state
//   4 = modifier application + raw input mask send via virtual[0x5c]
// The function ends with a final check for a deferred action if this->someFlag is zero.

void __thiscall InputActionMap::processBindingEvents(void* this, uint eventHash)
{
    undefined4* currentEntry;
    undefined4** ppuList;
    undefined4 uVar3;
    int iVar4;
    ushort uFlags;
    uint uListIndex;
    undefined4** nextIterator;
    bool bIsCompact;       // local_68: true if using compact bit-packed list
    // Compact iteration context
    int bitArrayBase;      // iStack_64: base address of bit array
    undefined4* compactData; // puStack_60: pointer to compact data
    uint compactIndex;     // local_5c: current index in compact iteration
    uint compactCount;     // local_58: total number of entries in compact list
    undefined4* compactEntry; // local_54: current entry from compact list
    undefined2 compactIndexShort; // uStack_50
    undefined4 compactFlag; // uStack_4c
    undefined4** compactListPtr; // local_c: next compact list pointer

    // Setup iteration context (likely initializes compact/pointer iterators based on eventHash)
    setupIterationContext();  // FUN_0046f500
    // Hash to select binding list (e.g., controller binding group)
    hashToBindingList(eventHash, 0x38523fc3); // FUN_0043aff0(eventHash, constant)

    compactIndex = compactIndex; // initialize from local_5c (uninitialized in decomp, but likely set by hash)
    compactListPtr = compactListPtr;

    do {
        // Determine if we are in compact or pointer iteration mode
        if (bIsCompact == false) {
            bIsCompact = (*compactListPtr == (undefined4*)0x0); // check pointer list end
        } else {
            bIsCompact = (compactIndex == compactCount); // check compact list end
        }

        if (bIsCompact) {
            // End of list reached
            if ((this[0x4c] == 0) && (iVar4 = checkDeferredAction(eventHash), iVar4 != 0)) {
                // If deferred action available, trigger it via virtual call at offset 0xf0
                (**(code**)(*(int*)this + 0xf0))(iVar4);
            }
            return;
        }

        // Get current entry
        if (bIsCompact == false) {
            ppuList = compactListPtr; // pointer list iteration
        } else {
            ppuList = &compactEntry; // from compact list local
        }

        // Get the subtype from entry (+6 field)
        if (*(short*)((int)ppuList + 6) == 0x25e3) { // magic constant? could be type indicator
            uSubType = (undefined4*)(uint)*(ushort*)(ppuList + 1); // low word
        } else {
            uSubType = ppuList[1]; // second dword
        }

        // Dispatch based on subtype
        if (uSubType == (undefined4*)0x1) {
            // ACTION: trigger event
            undefined4** actionData;
            if (bIsCompact == false) {
                actionData = compactListPtr;
            } else {
                actionData = &compactEntry;
            }
            if (*(short*)((int)actionData + 6) == 0x25e3) {
                if (*actionData == (undefined4*)0x0) {
                    actionData = (undefined4**)&DAT_0120e700; // default? global
                } else {
                    actionData = (undefined4**)((int)actionData[2] + (int)*actionData);
                }
            } else {
                actionData = actionData + 2;
            }
            // Check if the action data is non-zero (any of 4 dwords)
            if (((*actionData != (undefined4*)0x0) || (actionData[1] != (undefined4*)0x0)) ||
                (actionData[2] != (undefined4*)0x0) || (actionData[3] != (undefined4*)0x0)) {
                uVar3 = buildActionPayload(actionData); // FUN_00421170
                (**(code**)(*(int*)this + 0xf0))(uVar3); // trigger action
            }
        } else if (uSubType == (undefined4*)0x0) {
            // STATE FLAGS: update bitfield at this+0x15e
            undefined4* stateEntry;
            if (bIsCompact == false) {
                stateEntry = compactListPtr[2];
            } else {
                stateEntry = compactEntry[2];
            }
            // Check bits 0-4 on stateEntry to set/clear flags in this->inputStateFlags (ushort at +0x15e)
            if (((uint)stateEntry & 1) == 0) {
                *(ushort*)((int)this + 0x15e) = *(ushort*)((int)this + 0x15e) & 0xfffd;
            } else {
                *(ushort*)((int)this + 0x15e) = *(ushort*)((int)this + 0x15e) | 2;
            }
            // ... (similar for bits 2, 4, 8)
            // Bit 0x10 special: triggers sound/visual feedback?
            uFlags = *(ushort*)((int)this + 0x15e) >> 0xd;
            if (((uint)stateEntry & 0x10) == 0) {
                if ((uFlags & 1) != 0) {
                    *(ushort*)((int)this + 0x15e) = *(ushort*)((int)this + 0x15e) & 0xdfff;
                    FUN_004086d0(&DAT_0120e944);
                    FUN_004086d0(&DAT_0120e94c);
                }
            } else if ((uFlags & 1) == 0) {
                *(ushort*)((int)this + 0x15e) = *(ushort*)((int)this + 0x15e) | 0x2000;
                if (DAT_0120e944 != 0) {
                    FUN_00407e60(this + 0xf, &DAT_0120e944);
                }
                if (DAT_0120e94c != 0) {
                    FUN_00407e60(this + 0xf, &DAT_0120e94c);
                }
            }
        } else if (uSubType == (undefined4*)0x2) {
            // AXIS: send to axis manager
            undefined4** axisEntry;
            if (bIsCompact == false) {
                axisEntry = compactListPtr;
            } else {
                axisEntry = &compactEntry;
            }
            if (*(short*)((int)axisEntry + 6) == 0x25e3) {
                if (*axisEntry == (undefined4*)0x0) goto LAB_0046f40c;
                axisEntry = (undefined4**)((int)axisEntry[2] + (int)*axisEntry);
            } else {
                axisEntry = axisEntry + 2;
            }
            if ((axisEntry != (undefined4**)0x0) && (*(char*)axisEntry != '\0')) {
                FUN_0043c390(DAT_01223414, this);
            }
        } else if (uSubType == (undefined4*)0x3) {
            // TOGGLE
            undefined4** toggleEntry;
            if (bIsCompact == false) {
                toggleEntry = compactListPtr;
            } else {
                toggleEntry = &compactEntry;
            }
            FUN_00470a10(toggleEntry[2] != (undefined4*)0x0);
        } else if (uSubType == (undefined4*)0x4) {
            // MODIFIER: apply raw input mask
            undefined4** modEntry;
            if (bIsCompact == false) {
                modEntry = compactListPtr;
            } else {
                modEntry = &compactEntry;
            }
            if (modEntry[2] != (undefined4*)0x0) {
                *(ushort*)((int)this + 0x15e) = *(ushort*)((int)this + 0x15e) & 0xefff;
                if (this[0x59] != 0) {
                    uVar9 = getRawInputData(); // FUN_004709e0
                    FUN_0046e3a0((int)((ulonglong)uVar9 >> 0x20), (int)uVar9);
                }
                // Call virtual[0x5c] with mask
                (**(code**)(*(int*)this + 0x5c))
                          (((uint)*(ushort*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 0xe) | this[0x22]) &
                           ~(uint)*(ushort*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 0xc),
                           0xffffffff);
            }
        }

LAB_0046f40c:
        // Advance iterator
        if (bIsCompact == false) {
            if ((int)uListIndex < 0) {
                compactListPtr = (undefined4**)((int)compactListPtr + (int)*compactListPtr);
                FUN_0043b140(); // reset iteration state?
                uListIndex = compactIndex;
                compactListPtr = compactListPtr;
            } else if ((int)uListIndex < (int)(compactCount - 1)) {
                compactIndex = uListIndex + 1;
                compactListPtr = (undefined4**)((int)compactListPtr + (int)*compactListPtr);
                uListIndex = compactIndex;
                compactListPtr = (undefined4**)((int)compactListPtr + (int)*compactListPtr);
            } else {
                compactListPtr = (undefined4**)&DAT_01163cf8; // end sentinel
                compactListPtr = (undefined4**)&DAT_01163cf8;
            }
        } else {
            compactIndex = compactIndex + 1;
            uListIndex = compactIndex;
            if (compactIndex != compactCount) {
                compactIndexShort = (short)compactIndex;
                if ((*(byte*)((compactIndex >> 3) + bitArrayBase) & (byte)(1 << ((byte)compactIndex & 7))) == 0) {
                    compactFlag = *compactData;
                    compactEntry = compactData;
                    compactData = compactData + 1;
                } else {
                    compactEntry = (undefined4*)0x0;
                    compactFlag = 0;
                }
            }
        }
    } while (true);
}