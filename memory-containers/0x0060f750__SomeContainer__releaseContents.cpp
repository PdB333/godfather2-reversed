// FUNC_NAME: SomeContainer::releaseContents
void __thiscall SomeContainer::releaseContents(int *thisPtr) // +0x0: pointer to something, +0x4: count
{
    int count = thisPtr[1]; // offset 0x4
    while (count = count - 1, count >= 0)
    {
        releaseItem(); // FUN_00609aa0 - release individual item
    }
    if (thisPtr[0] != 0) // offset 0x0
    {
        deallocate(thisPtr[0]); // FUN_009c8f10 - free the main pointer
    }
}