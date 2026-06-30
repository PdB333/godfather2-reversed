// FUNC_NAME: AudioChannel::setChannelValue
void __thiscall AudioChannel::setChannelValue(int this, char isRightChannel, int value)
{
    // Store value into the appropriate channel field.
    // Offset +0x10c: left channel value (or first channel)
    // Offset +0x110: right channel value (or second channel)
    if (isRightChannel != '\0') {
        *(int *)(this + 0x10c) = value;
    } else {
        *(int *)(this + 0x110) = value;
    }
    return;
}