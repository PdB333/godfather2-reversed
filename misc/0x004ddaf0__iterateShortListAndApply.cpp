//FUNC_NAME: iterateShortListAndApply
void iterateShortListAndApply(short* idList, int param)
{
    short currentId;
    while (true)
    {
        currentId = *idList;
        if (currentId == 0)
            break;
        FUN_004dda40(currentId, param);
        idList++;
    }
}