// FUNC_NAME: NPC::getCachedValue
int __thiscall NPC::getCachedValue(void)
{
    char cVar1;
    int uVar2;
    
    if ((*(int *)(this + 0x9c) != 0) && (*(int *)(this + 0x9c) != 0x48) &&
        (cVar1 = isStateActive(), cVar1 != '\0')) {
        if (*(int *)(this + 0x9c) != 0) { // Redundant check - decompiler artifact
            uVar2 = computeValue();
            return uVar2;
        }
        uVar2 = computeValue(); // Unreachable due to outer condition
        return uVar2;
    }
    return *(int *)(this + 0xb0);
}