// FUNC_NAME: destructorWithDeletingFlag
int __thiscall destructorWithDeletingFlag(int this, byte deletingFlag)
{
    if (*(int *)(this + 8) != 0) {
        FUN_009c8f10(*(int *)(this + 8));
    }
    if ((deletingFlag & 1) != 0) {
        FUN_009c8eb0(this);
    }
    return this;
}