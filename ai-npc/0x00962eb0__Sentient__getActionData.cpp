// FUNC_NAME: Sentient::getActionData
int __thiscall Sentient::getActionData(int this)
{
    int result = 0;
    int combinedIndex = *(int *)(this + 0xc4) + *(int *)(this + 0xd4); // currentAction + currentSubAction
    switch(combinedIndex)
    {
        case 0:
            return *(int *)(this + 0x1a8);
        case 1:
            return *(int *)(this + 0x1b8);
        case 2:
            return *(int *)(this + 0x1b0);
        case 3:
            return *(int *)(this + 0x1dc);
        case 4:
            return *(int *)(this + 0x1cc);
        case 5:
            return *(int *)(this + 0x1d0);
        case 6:
            return *(int *)(this + 0x1bc);
        case 7:
            return *(int *)(this + 0x1c8);
        case 9:
            result = *(int *)(this + 0x1c4);
            break;
    }
    return result;
}