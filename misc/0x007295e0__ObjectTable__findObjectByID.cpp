// FUNC_NAME: ObjectTable::findObjectByID
int __thiscall ObjectTable::findObjectByID(int this, int id)
{
    uint index = 0;
    if (*(uint *)(this + 0x14) != 0) {
        int* table = *(int **)(this + 0x10);
        while (id != *table) {
            index++;
            table += 3; // each entry is 12 bytes (3 ints)
            if (*(uint *)(this + 0x14) <= index) {
                return 0;
            }
        }
        if ((index != 0xffffffff) && (int* entry = table + 1, *entry != 0)) {
            return *entry - 0x48; // subtract offset to get containing object base
        }
    }
    return 0;
}