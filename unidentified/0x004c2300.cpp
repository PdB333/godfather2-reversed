// FUN_004c2300: IDList::containsID
bool __thiscall IDList::containsID(int this, int id)
{
    // +0x1c0: pointer to IDList structure
    // IDList:
    //   +0x0c: pointer to array of {int idPlusOffset; int extra;}
    //   +0x10: count (uint)
    IDList* list = *(IDList**)(this + 0x1c0);
    uint count = *(uint*)(list + 0x10);
    if (count == 0)
        return false;

    int* pairArray = *(int**)(list + 0xc);
    uint index = 0;
    while (index < count)
    {
        int storedValue = pairArray[index * 2]; // first element of pair
        int decodedId;
        if (storedValue == 0)
            decodedId = 0;
        else
            decodedId = storedValue - 0x48; // IDs stored as (id + 0x48)
        if (decodedId == id)
            return true;
        index++;
    }
    return false;
}