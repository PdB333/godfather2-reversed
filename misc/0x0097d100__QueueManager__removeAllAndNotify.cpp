// FUNC_NAME: QueueManager::removeAllAndNotify
void __thiscall QueueManager::removeAllAndNotify()
{
    int currentCount = *(int *)(this + 0x9c); // current number of items in the main queue (+0x9c)
    if (currentCount != 0)
    {
        int* itemPtr = (int*)(this + 0x78 + currentCount * 4); // pointer to the item being removed (+0x78 is start of item array)
        int remaining = currentCount;
        do
        {
            remaining--;
            *(int *)(this + 0x9c) = *(int *)(this + 0x9c) - 1; // decrement queue count
            if (remaining != *(int *)(this + 0x9c))
            {
                // If the removed item is not the last, copy the last item into the removed slot
                *itemPtr = *(int *)(this + 0x7c + *(int *)(this + 0x9c) * 4);
            }
            // Check if all four queues (+0x9c, +0x78, +0x54, +0x30) are empty
            if (*(int *)(this + 0x9c) + *(int *)(this + 0x78) + *(int *)(this + 0x54) + *(int *)(this + 0x30) == 0)
            {
                unsigned int i = 0;
                *(int *)(this + 0xa0) = 0; // clear a status flag
                int callbackCount = *(int *)(this + 0xdc); // number of registered callbacks (+0xdc)
                if (callbackCount != 0)
                {
                    do
                    {
                        // Each callback entry at +0xd8 is an array of pointers to function tables.
                        // The actual function is at offset +4 from the table start.
                        (*(void (**)())(**(int**)(*(int*)(this + 0xd8) + i * 4) + 4))();
                        i++;
                    } while (i < (unsigned int)callbackCount);
                }
            }
            if (*(int *)(this + 0x9c) == 0)
            {
                releaseMutex(&DAT_0112a638); // release synchronization object when main queue is empty
            }
            itemPtr--; // move to previous item (removing from end to start)
            currentCount--;
        } while (currentCount != 0);
    }
}