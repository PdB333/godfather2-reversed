// FUNC_NAME: DataStack::pushInt
void __thiscall DataStack::pushInt(int* this, int value)
{
    // Store value at current index in array starting at this+0x5C
    *(int*)((int)this + 0x5C + *(int*)((int)this + 0x48) * 4) = value;
    // Increment count at this+0x48
    *(int*)((int)this + 0x48) += 1;
}