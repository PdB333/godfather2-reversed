// FUNC_NAME: SomeContainer::tryFindAndCallOnMatch
// Address: 0x006ea720
// Role: Searches an integer array (this+0x30) with count (this+0x34) for a matching value (param_2).
//       If found, calls a private member function (FUN_006ea530) and returns immediately.

void __thiscall SomeContainer::tryFindAndCallOnMatch(int param_2)
{
    uint index = 0;
    if (*(uint *)(this + 0x34) != 0) // count of array elements
    {
        int *arrayBase = *(int **)(this + 0x30);
        do
        {
            if (*arrayBase == param_2)
            {
                if ((int)index < 0)
                {
                    return;
                }
                // likely a private member function that performs an action on the found item
                onItemFoundAction();
                return;
            }
            index = index + 1;
            arrayBase = arrayBase + 1;
        } while (index < *(uint *)(this + 0x34));
    }
    return;
}