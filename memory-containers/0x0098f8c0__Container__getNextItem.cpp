// FUNC_NAME: Container::getNextItem
uint __thiscall Container::getNextItem(uint previousValue, undefined4 param2)
{
    uint result = previousValue & 0xffffff00; // Preserve high bytes, clear low byte
    if (this->maxCount != 0) // +0x48: maximum number of items
    {
        int nextIndex = this->currentIndex + 1; // +0x4c: current index
        if (nextIndex < 0 || nextIndex >= this->maxCount)
        {
            nextIndex = 0; // Wrap around to start
        }
        result = getItemAtIndex(nextIndex, param2); // Retrieve item at the new index
    }
    return result;
}