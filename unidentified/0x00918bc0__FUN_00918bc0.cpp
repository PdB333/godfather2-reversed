// FUNC_NAME: SomeManager::readIntProperty
void __thiscall SomeManager::readIntProperty(int this, undefined4 unusedParam, int index)
{
    char buffer[64]; // stack buffer for string
    void* handle; // handle from data source
    int value = 0; // default value

    buffer[0] = '\0';
    // buffer is zero-initialized (local_104 and local_108 also zeroed, but not used)
    handle = FUN_00907680(index); // get handle for this index
    if (FUN_00ae69b0(handle, buffer) != '\0') { // read string into buffer
        // value = atoi(buffer); // likely conversion omitted by decompiler
        *(int*)(*(int*)(this + 0xa8) + index * 4) = value; // store integer into array
    }
}