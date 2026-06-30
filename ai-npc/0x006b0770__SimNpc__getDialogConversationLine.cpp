// FUNC_NAME: SimNpc::getDialogConversationLine
int __thiscall SimNpc::getDialogConversationLine(int this, int lineIndex)
{
    // +0x34: pointer to dialog data array
    // each entry is 8 bytes: 4 bytes for offset/text pointer + 4 bytes for some metadata
    return *(int *)(*(int *)(this + 0x34) + 4 + lineIndex * 8);
}