// FUNC_NAME: Entity::releaseSlots
void __thiscall Entity::releaseSlots(int thisPtr)
{
    // Release and clear three pointer slots at offsets 0xB0, 0xB4, 0xB8
    int *slot = reinterpret_cast<int *>(thisPtr + 0xB0);
    int count = 3;
    do {
        if (*slot != 0) {
            releaseObject(*slot, 0); // calls FUN_006065a0 - presumably decrements refcount or deletes
            *slot = 0;
        }
        slot++;
        count--;
    } while (count != 0);
}