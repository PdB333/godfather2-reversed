// FUNC_NAME: ObjectArray::removeByFourIntKey
int __thiscall ObjectArray::removeByFourIntKey(int *key) // key is pointer to 4 ints
{
    // object layout:
    // this+0x08: pointer to array of pointers (int**)
    // this+0x0C: number of elements (uint)
    uint count = *(uint *)(this + 0x0C);
    if (count == 0)
        return 0;

    int **array = *(int ***)(this + 0x08);
    uint idx = 0;
    do {
        int *obj = array[idx];
        // compare 4 int fields at +0x1C, +0x20, +0x24, +0x28 with key[0..3]
        if (obj[0x07] == key[0] &&     // +0x1C / 4 = 7 (int offset)
            obj[0x08] == key[1] &&     // +0x20 / 4 = 8
            obj[0x09] == key[2] &&     // +0x24 / 4 = 9
            obj[0x0A] == key[3])       // +0x28 / 4 = 10
        {
            // Found match, remove from array (shift left)
            if (idx < count - 1)
            {
                do {
                    array[idx] = array[idx + 1];
                    idx++;
                } while (idx < count - 1);
            }
            // decrement count
            *(uint *)(this + 0x0C) = count - 1;
            return (int)obj;
        }
        idx++;
    } while (idx < count);

    return 0;
}