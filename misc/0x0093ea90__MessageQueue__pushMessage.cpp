// FUNC_NAME: MessageQueue::pushMessage
void __thiscall MessageQueue::pushMessage(int thisPtr, undefined4 *messageData)
{
    char cVar1;
    undefined4 *node;
    undefined4 uVar3;
    char *srcString;
    void *dst;
    char *src;
    
    // Check if queue size is less than max (20)
    if (*(uint *)(thisPtr + 0x50) < 0x14) {
        // If free list is empty and (other pointer is null or flag bit not set), call debug function
        if ((*(int *)(thisPtr + 0x44) == 0) &&
           ((*(int *)(thisPtr + 0x40) == 0 || ((*(byte *)(thisPtr + 0x34) & 1) == 0)))) {
            FUN_004de190(); // likely debug warning or error
        }
        // Pop node from free list (linked list at +0x44)
        node = *(undefined4 **)(thisPtr + 0x44);
        if (node != (undefined4 *)0x0) {
            uVar3 = *node; // next pointer
            *(int *)(thisPtr + 0x1c) = *(int *)(thisPtr + 0x1c) + -1; // decrement free count
            *(undefined4 *)(thisPtr + 0x44) = uVar3; // update free list head
            *(int *)(thisPtr + 0x20) = *(int *)(thisPtr + 0x20) + 1; // increment allocated count
            
            if (node != (undefined4 *)0x0) {
                src = (char *)*messageData;
                if (src == (char *)0x0) {
                    src = &DAT_0120546e; // default empty string
                }
                // Initialize node fields
                node[2] = 1;          // +0x08: flag (active)
                *node = 0;            // +0x00: next = null
                node[1] = 0;          // +0x04: prev = null
                *(undefined2 *)(node + 4) = 0;   // +0x10: short field
                *(undefined2 *)((int)node + 0x12) = 0; // +0x12: short field
                *(undefined2 *)(node + 5) = 15000; // +0x14: timeout (ms)
                node[6] = 0;          // +0x18: unknown
                node[7] = 0;          // +0x1c: unknown
                // Allocate and copy string
                pcVar4 = src;
                do {
                    cVar1 = *pcVar4;
                    pcVar4 = pcVar4 + 1;
                } while (cVar1 != '\0');
                dst = (void *)FUN_009c8e80(pcVar4 + (1 - (int)(src + 1))); // allocate memory for string
                node[8] = dst;        // +0x20: string pointer
                _memcpy(dst, src, (size_t)(pcVar4 + (1 - (int)(src + 1))));
                node[3] = DAT_01205224 + 12000; // +0x0c: timestamp (current time + 12s)
                FUN_0093e4c0(node); // process/enqueue the node
            }
        }
    }
    return;
}