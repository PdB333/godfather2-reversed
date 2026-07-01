// FUNC_NAME: DebugMenu::processCommand

undefined1 __thiscall DebugMenu::processCommand(int *this, undefined4 param2, undefined4 param3, undefined4 param4, int commandId, undefined4 param6)
{
    int iVar1;
    float fVar2;
    undefined1 retVal;
    int entityPtr;
    undefined4 uVar5;
    float fVar6;
    undefined4 soundHash;
    int computedIndex;
    int index2d;
    
    entityPtr = this[0x17]; // offset 0x5C: pointer to some game state object
    retVal = 1;
    
    switch(commandId - 0x25) {
    case 0: // command 0x25 - Play sound based on entity state
        iVar1 = *(int *)(entityPtr + 0x74c); // offset 0x74C: current entity pointer
        if ((((iVar1 != 0) && (iVar1 != 0x48)) && ((*(uint *)(entityPtr + 0x8e0) >> 10 & 1) != 0)) &&
           (*(char *)(iVar1 + 0x160) == '\x02')) {
            // entity is a valid target with flag set, play confirm sound
            (**(code **)(*this + 0x2c))(0x5e9d04d7, 1, 0, 0, 0x3f800000, 0x3f800000);
            return 1;
        }
        // default sound
        (**(code **)(*this + 0x2c))(0x2ca3cff6, 1, 0, 0, 0x3f800000, 0x3f800000);
        return 1;
        
    case 1: // command 0x26 - open level/area selection menu
        FUN_007fff40(entityPtr + 0x1ff0); // offset 0x1FF0: some sub-object
        uVar5 = 0;
        uVar5 = FUN_006fbc40(0, 0);
        FUN_007f96a0(0, 0, uVar5, 0);
        FUN_006fbc70();
        return 1;
        
    case 2: // command 0x27 - spawn object from table A
        FUN_007f63e0(0x37); // set menu mode
        FUN_0076b2a0(); // update preview or similar
        computedIndex = this[0x1e] * 0x2c; // index scaled by 0x2C (stride)
        FUN_0076b680(*(undefined4 *)(&DAT_00d65da0 + computedIndex),
                     *(undefined4 *)(&DAT_00d65da4 + computedIndex),
                     *(undefined4 *)(&DAT_00d65da8 + computedIndex),
                     *(undefined4 *)(&DAT_00d65dac + computedIndex),
                     *(undefined4 *)(&DAT_00d65db0 + computedIndex));
        return 1;
        
    case 3:
    case 8: // commands 0x28 or 0x2D - spawn object from table B
        computedIndex = this[0x1e] * 0x2c;
        FUN_0076b680(*(undefined4 *)(&DAT_00d65db4 + computedIndex),
                     *(undefined4 *)(&DAT_00d65db8 + computedIndex),
                     *(undefined4 *)(&DAT_00d65dbc + computedIndex),
                     *(undefined4 *)(&DAT_00d65dc0 + computedIndex),
                     *(undefined4 *)(&DAT_00d65dc4 + computedIndex));
        return 1;
        
    case 4: // command 0x29 - randomize selection index
        fVar6 = (float)FUN_00427180(); // random float
        fVar2 = (float)DAT_00e445fc; // multiplier (e.g., max index)
        this[0x22] = 0; // reset sub-index
        computedIndex = (int)(longlong)ROUND(fVar6 * fVar2);
        this[0x21] = computedIndex; // set main index
        return 1;
        
    case 5: // command 0x2A - delete selected object
        if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) {
            if (this[0x1c] == 0) {
                entityPtr = 0;
            }
            else {
                entityPtr = this[0x1c] - 0x48;
            }
            iVar1 = FUN_006bc8d0(entityPtr, 0x369ac561); // hash lookup
            if (iVar1 != 0) {
                FUN_00747b80(); // delete object
                return 1;
            }
        }
        break;
        
    case 6: // command 0x2B - play specific sound based on index
        FUN_007f6420(0xe); // open sound submenu
        iVar1 = this[0x1e]; // selection index
        soundHash = 0x2b6e7777;
        if (iVar1 != 10) {
            if (iVar1 == 0xb) {
                soundHash = 0x2b6e7778;
            }
            else if (iVar1 == 0xc) {
                soundHash = 0x2b6e7779;
            }
        }
        (**(code **)(*this + 0x2c))(soundHash, 1, 0, 0, 0x3f800000, 0x3f800000);
        return 1;
        
    case 7: // command 0x2C - select item from 2D list
        FUN_007f6420(0xe); // open list submenu
        index2d = this[0x21]; // row index
        int* listPtr = (&PTR_DAT_00e51c58)[index2d]; // pointer to row list
        iVar1 = listPtr[this[0x22] * 4]; // column item
        this[0x1e] = iVar1;
        if (iVar1 == 0xd) { // special marker: go back one
            this[0x1e] = listPtr[this[0x22] * 4 - 4];
        }
        FUN_0076b7f0(this[0x1e], iVar1 == 0xd); // update selection, bool indicates going back
        return 1;
        
    case 9: // command 0x2E - increment sub-index (next column)
        this[0x22] = this[0x22] + 1;
        return 1;
        
    default:
        retVal = FUN_0073e610(param2, param3, param4, commandId, param6);
    }
    return retVal;
}