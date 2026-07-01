// FUNC_NAME: Component::getOwner
int __fastcall Component::getOwner(int thisPtr)
{
    // Check component type at +0xff8: if not 0x02 (built-in/self), 
    // try to get owner pointer at +0xff0 and adjust back by 0x48 (header size)
    if (*(char *)(thisPtr + 0xff8) != 0x02) {
        if (*(int *)(thisPtr + 0xff0) != 0) {
            return *(int *)(thisPtr + 0xff0) - 0x48;
        }
        thisPtr = 0;
    }
    return thisPtr;
}