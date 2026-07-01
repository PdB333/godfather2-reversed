// FUNC_NAME: NetMessageReader::readState
// Function at 0x007f8300 - reads a stream of typed data into class fields.
// The magic number 0x55859efa likely identifies the stream format.
// Field offsets: this+0x1b94 = flags, this+0x1cc0..0x1d10 = array of 11 fields (8 bytes each),
// this+0x754 and this+0x758 = two additional fields.
void __thiscall NetMessageReader::readState(void* this, undefined4 streamParam) {
    char cVar1;
    undefined4 uVar2;
    int iVar3;

    // Initialize stream with magic identifier
    streamInit(streamParam, 0x55859efa);
    cVar1 = streamIsDone();
    do {
        if (cVar1 != '\0') {
            return;
        }
        streamAdvance();
        uVar2 = streamGetType();
        switch (uVar2) {
        case 3: // opcode 3: set a flag based on stream data
            iVar3 = streamReadInt();
            if (*(char *)(iVar3 + 8) == '\0') {
                *(int *)((char*)this + 0x1b94) |= 0x20;
            }
            break;
        case 0x2f: // field index 0
            streamReadInt();
            uVar2 = streamReadUint32();
            setFieldInt32((char*)this + 0x1cc0, uVar2);
            break;
        case 0x30: // field index 1
            streamReadInt();
            uVar2 = streamReadUint32();
            setFieldInt32((char*)this + 0x1cc8, uVar2);
            break;
        case 0x31: // field index 2
            streamReadInt();
            uVar2 = streamReadUint32();
            setFieldInt32((char*)this + 0x1cd0, uVar2);
            break;
        case 0x32: // field index 3
            streamReadInt();
            uVar2 = streamReadUint32();
            setFieldInt32((char*)this + 0x1cd8, uVar2);
            break;
        case 0x33: // field index 4
            streamReadInt();
            uVar2 = streamReadUint32();
            setFieldInt32((char*)this + 0x1ce0, uVar2);
            break;
        case 0x34: // field index 5
            streamReadInt();
            uVar2 = streamReadUint32();
            iVar3 = (int)((char*)this + 0x1ce8);
            goto setFieldFloat;
        case 0x35: // field index 6
            streamReadInt();
            uVar2 = streamReadUint32();
            iVar3 = (int)((char*)this + 0x1cf0);
            goto setFieldFloat;
        case 0x36: // field index 7
            streamReadInt();
            uVar2 = streamReadUint32();
            iVar3 = (int)((char*)this + 0x1cf8);
            goto setFieldFloat;
        case 0x37: // field index 8
            streamReadInt();
            uVar2 = streamReadUint32();
            iVar3 = (int)((char*)this + 0x1d00);
            goto setFieldFloat;
        case 0x38: // field index 9
            streamReadInt();
            uVar2 = streamReadUint32();
            iVar3 = (int)((char*)this + 0x1d08);
            goto setFieldFloat;
        case 0x39: // field index 10
            streamReadInt();
            uVar2 = streamReadUint32();
            iVar3 = (int)((char*)this + 0x1d10);
setFieldFloat:
            setFieldFloat(iVar3, uVar2);
            break;
        case 0x3a: // field at +0x754
            iVar3 = streamReadInt();
            *(undefined4 *)((char*)this + 0x754) = *(undefined4 *)(iVar3 + 8);
            break;
        case 0x3b: // field at +0x758
            iVar3 = streamReadInt();
            *(undefined4 *)((char*)this + 0x758) = *(undefined4 *)(iVar3 + 8);
            break;
        }
        streamAdvance();
        cVar1 = streamIsDone();
    } while (true);
}