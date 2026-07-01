//FUNC_NAME: StreamReader::readTwoFields
void __thiscall StreamReader::readTwoFields(int this, undefined4 stream)
{
    char isEnd;
    int type;
    undefined4 value;

    streamBeginRead(stream);
    streamSetExpectedValue(stream, 0x41b65f6c); // Expected float constant (22.7...)
    isEnd = streamIsEnd(stream);
    while (isEnd == '\0') {
        streamReadNext(stream);
        type = streamReadType(stream);
        if (type == 0) {
            streamReadNext(stream);
            value = streamReadValue(stream);
            setFloatField(this + 0x50, value); // +0x50: first float field
        }
        else if (type == 1) {
            streamReadNext(stream);
            value = streamReadValue(stream);
            setFloatField(this + 0x58, value); // +0x58: second float field
        }
        streamAdvance(stream);
        isEnd = streamIsEnd(stream);
    }
    return;
}