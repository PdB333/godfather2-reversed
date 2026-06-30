// FUNC_NAME: Entity::validate
// Address: 0x005ddc30
// Role: Validates entity state by checking a flag and iterating over two linked lists of sub-objects.

bool __thiscall Entity::validate(int context)
{
    // +0x24: flags byte, bit 0 = active flag
    if ((*(byte *)(this + 0x24) & 1) == 0)
        return false;

    this->preProcess(); // FUN_005ddd30

    // First list: linked list at +0x2c (pointer to first node), count at +0x28
    int firstNode = *(int *)(this + 0x2c);
    if (firstNode != 0)
    {
        uint firstCount = *(uint *)(this + 0x28);
        bool success = true;
        if (firstCount != 0)
        {
            uint i = 0;
            do
            {
                if (firstNode == 0)
                    success = false;
                else
                {
                    char result = this->processFirstElement(context, firstNode); // FUN_005dc6e0
                    if (result == 0)
                        success = false;
                    firstNode = *(int *)(firstNode + 0x28); // next node offset
                }
                i++;
            } while (i < firstCount);
        }

        // Second list: array of pointers at +0x34, count at +0x30
        uint **secondList = *(uint ***)(this + 0x34);
        uint secondCount = *(uint *)(this + 0x30);
        if (secondCount != 0)
        {
            uint j = 0;
            do
            {
                if (secondList == nullptr)
                    success = false;
                else
                {
                    uint *entry = *secondList;
                    int val = this->processSecondElement(entry); // FUN_005dc670
                    if (val == 0)
                    {
                        success = false;
                    }
                    else
                    {
                        char result = this->otherProcess(val, secondList); // FUN_005de000
                        if (result == 0)
                            success = false;
                    }
                    secondList = (uint **)secondList[7]; // skip 7 pointers (28 bytes)
                }
                j++;
            } while (j < secondCount);
        }

        return success;
    }

    return true;
}