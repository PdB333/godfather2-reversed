// FUNC_NAME: TNLConnection::getSequence
int __thiscall TNLConnection::getSequence(int *outSeq)
{
    // +0x3c offset from this (base class?) holds a handle/pointer
    int handle = *(int *)((char *)this - 0x3c);
    // Resolves handle to an object (likely a net object or packet)
    int obj = GetObjectFromHandle(handle);   // FUN_004058a0
    // Extracts the sequence number from the object
    int seq = GetSequenceFromObject(obj);    // FUN_004dafd0
    *outSeq = seq;
    return 1;  // success
}