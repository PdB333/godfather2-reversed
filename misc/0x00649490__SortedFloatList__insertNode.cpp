// FUNC_NAME: SortedFloatList::insertNode
void __fastcall SortedFloatList::insertNode(SortedFloatNode* newNode, SortedFloatBucketArray* bucketArr)
{
    // newNode is the node being inserted (this in ECX)
    // bucketArr is an array of 8 bucket headers, each 0x20 bytes apart
    
    // Get the float value from newNode (stored as uint with low bit masked)
    uint rawValue = *(uint*)(newNode + 4) & 0xFFFFFFFE;
    
    // Convert to float and extract exponent (IEEE single precision)
    float fVal = (float)(int)rawValue;
    if ((int)rawValue < 0)
    {
        fVal += DAT_00e44578; // constant to handle negative zero? Probably 0x80000000 as float
    }
    uint exponent = ((uint)fVal >> 23) - 127; // unbiased exponent
    
    // Clamp exponent to range 0..7 (for 8 buckets)
    if (exponent < 6)
        exponent = 6;
    exponent -= 6; // now 0..7
    if (exponent > 7)
        exponent = 7;
    
    // Compute bucket header pointer: each bucket header is 0x20 bytes
    SortedFloatBucketHeader* bucket = (SortedFloatBucketHeader*)((int)bucketArr + exponent * 0x20);
    
    // Sentinel node is at offset +0x78 within the bucket header
    SortedFloatNode* sentinel = (SortedFloatNode*)((int)bucket + 0x78);
    
    // Start from the head pointer at offset +0x90
    SortedFloatNode* current = *(SortedFloatNode**)((int)bucket + 0x90);
    
    // Walk the list to find insertion point (ascending order by rawValue)
    SortedFloatNode* prev = sentinel;
    while (current != sentinel && (*(uint*)(current + 4) & 0xFFFFFFFE) < rawValue)
    {
        prev = current;
        current = *(SortedFloatNode**)(current + 0x18);
    }
    
    // Insert newNode after prev
    newNode->prev = prev;                // +0x14
    newNode->next = prev->next;          // +0x18
    prev->next = newNode;                // +0x18
    newNode->next->prev = newNode;      // +0x14 of next node
}