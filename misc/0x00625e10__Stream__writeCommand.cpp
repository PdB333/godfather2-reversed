// FUNC_NAME: Stream::writeCommand
void __thiscall Stream::writeCommand(void *this, int value)
{
    // +0x08: pointer to current write position in buffer
    int *writePos = *(int **)((int)this + 8);
    *writePos = 2;          // command type identifier (e.g., CMD_TYPE_2)
    writePos[1] = value;    // command parameter
    // advance write pointer by 2 ints (8 bytes)
    *(int *)((int)this + 8) = (int)writePos + 8;
}