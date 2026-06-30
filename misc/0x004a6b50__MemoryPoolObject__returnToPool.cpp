// FUNC_NAME: MemoryPoolObject::returnToPool
void MemoryPoolObject::returnToPool(void)
{
    // Set status flag bit 3 (0x08) at offset +0x80 - marks this as free/in pool
    *(unsigned short *)(this + 0x80) |= 8;

    // Only process if node is not currently in any list (prev and next both NULL)
    if ((*(int *)(this + 0x88) == 0) && (*(int *)(this + 0x84) == 0))
    {
        // Pre-return-to-pool callback (initialization cleanup)
        FUN_004a69b0(0);

        int tail = (int)this; // maybe g_poolTail
        if (g_poolHead != 0)  // DAT_01205484
        {
            *(int *)(g_poolHead + 0x88) = (int)this; // set next of current head
            tail = g_poolTail;                       // DAT_01205480
        }
        g_poolTail = tail;            // DAT_01205480
        *(int *)(this + 0x84) = g_poolHead; // prev = old head
        *(int *)(this + 0x88) = 0;           // next = NULL (new tail)
        g_poolHead = (int)this;             // DAT_01205484, new node becomes head
    }
}