// FUNC_NAME: ResourceManager::createResourceOrSomething
int __cdecl createResourceOrSomething(int unk1, int unk2)
{
    int result;
    int stackStruct[3]; // unknown struct with fields {2, 16, 0}
    stackStruct[0] = 2;
    stackStruct[1] = 0x10;
    stackStruct[2] = 0;

    // 0xc0 seems like a resource type or allocation size; the call returns non-zero on success
    if (FUN_009c8ed0(0xc0, stackStruct) != 0) {
        result = FUN_004154c0(unk1, unk2); // likely a constructor or copy operation
        return result;
    }
    return 0;
}