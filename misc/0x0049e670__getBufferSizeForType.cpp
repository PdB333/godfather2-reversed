// FUNC_NAME: getBufferSizeForType
int getBufferSizeForType(int typeIndex)
{
    switch (typeIndex)
    {
    case 0:
        return 4;
    case 1:
        return 8;
    case 2:
        return 12;
    case 3:
        return 16;
    case 4:
        return 64;
    default:
        return 0;
    }
}