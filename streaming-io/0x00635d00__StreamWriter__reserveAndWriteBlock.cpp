// FUNC_NAME: StreamWriter::reserveAndWriteBlock

class StreamWriter {
public:
    // Offsets:
    // +0x08: currentPos (int)
    // +0x14: writeInfo (pointer to struct with writePtr at +0x04)
    // +0x18: endPos
    // +0x1c: basePos
    // +0x31: writeLocked (byte flag)
    // +0x3c: writeCallback (function pointer)
private:
    int currentPos;        // +0x08
    void* writeInfo;       // +0x14
    int endPos;            // +0x18
    int basePos;           // +0x1c
    char writeLocked;      // +0x31
    void (*writeCallback)(); // +0x3c

public:
    void __thiscall reserveAndWriteBlock(void) {
        if (writeCallback != nullptr && writeLocked != '\0') {
            int savedCurrentPos = currentPos;   // iVar2
            int savedBasePos = basePos;         // iVar3
            int savedWritePtr = *(int*)(writeInfo + 4); // iVar4

            // Check if there is enough room for a 0xA0-byte block
            if (endPos - currentPos < 0xa1) {
                flushBuffer(); // FUN_00635c70
            }

            // Reserve 0xA0 bytes at current position
            *(int*)(writeInfo + 4) = currentPos + 0xa0;

            // Clear lock and invoke callback to fill the reserved block
            writeLocked = 0;
            writeCallback();
            writeLocked = 1;

            // Restore write pointer to its original offset from base
            *(int*)(writeInfo + 4) = basePos + (savedWritePtr - savedBasePos);

            // Restore currentPos to its original offset from base
            currentPos = basePos + (savedCurrentPos - savedBasePos);
        }
    }

    void flushBuffer(void); // defined elsewhere (FUN_00635c70)
};