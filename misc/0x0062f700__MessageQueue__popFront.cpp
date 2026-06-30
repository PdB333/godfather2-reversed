// FUNC_NAME: MessageQueue::popFront
void __thiscall MessageQueue::popFront(int this) {
    int size;
    int *p_type; // pointer to type field of first element
    undefined4 *pTail;
    undefined4 *pSrc;
    
    // Check if there is an element to pop
    size = FUN_0062f5c0(this);
    if (size >= 0) {
        return; // queue is empty or cannot pop
    }
    
    // Get pointer to the type field of the first element (element at head)
    // Assuming each element is 8 bytes: [4-byte type/flag] [4-byte data]
    p_type = (int *)(*(int *)(this + 0x8) - 8); // tail - 8 = address of last element? Actually tail points after last, so this is last element.
    // Wait: The code uses piVar3 = (int *)(*(int*)(param_1+8)+ -8); then checks *piVar3 == 4 or 3.
    // So that's the type of the last element? But we are popping front? The function seems to pop from the end? Let's re-express.
    // Actually the removal shifts elements left, which suggests removing the first element. But the type check is on the element at tail-8 (the last element). That seems odd.
    // However, the subsequent shift copies from tail backwards, effectively moving the last element to after tail? That would be a remove from end? Hmm.
    // Let's stick with the original logic: the type check is on the element at (tail-8). That could be the front? No.
    // I'll keep the logic and comment it.
    
    if (p_type != (int *)0x0 && (*p_type == 4 || *p_type == 3)) {
        // Special handling for certain message types
        FUN_00627b40();
        
        pTail = *(undefined4 **)(this + 0x8);
        pSrc = pTail;
        
        // Shift elements: copy from (pSrc-2) to pSrc, moving backwards
        while (pTail - 4 < pSrc) {
            // Copy an 8-byte element from two positions earlier to current
            *pSrc = pSrc[-2];
            pSrc[1] = pSrc[-1];
            pSrc -= 2;
        }
        // After loop, pSrc points to the head (first element)
        // Copy the head element into the freed slot at the beginning? Not clear.
        pSrc = *(undefined4 **)(this + 0x8);
        pTail[-4] = *pSrc;
        pTail[-3] = pSrc[1]; // copy head to the slot before the original tail
        
        // Check if we need to resize the buffer
        if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
            FUN_00627360(); // enlarge buffer
        }
    }
    
    // Update count and tail pointer
    // ((tail - head) >> 3) - 1 gives new size
    FUN_006343b0(this, 2, (*(int *)(this + 0x8) - *(int *)(this + 0xc) >> 3) - 1);
    *(int *)(this + 0x8) = *(int *)(this + 0x8) - 8; // tail decremented by 8 (one element removed)
    
    // Finalize
    FUN_006338a0();
    return;
}