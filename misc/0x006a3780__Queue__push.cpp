// FUNC_NAME: Queue::push
void __thiscall Queue::push(void* this, int value)
{
    // Offset 0x44: current write position / count of items
    // Offset 0x4c: array of uint32 elements (each 4 bytes)
    *(int*)((char*)this + 0x4c + *(int*)((char*)this + 0x44) * 4) = value;
    *(int*)((char*)this + 0x44) = *(int*)((char*)this + 0x44) + 1;
}