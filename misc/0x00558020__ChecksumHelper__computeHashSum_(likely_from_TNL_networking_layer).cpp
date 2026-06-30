// FUNC_NAME: ChecksumHelper::computeHashSum (likely from TNL networking layer)
// Function address: 0x00558020
// Role: Computes a cumulative checksum over a list of data elements by summing the low byte
// of each element's individual checksum.

int __thiscall ChecksumHelper::computeHashSum(int param1, int param2)
{
    // +0x08: pointer to an array descriptor structure
    int *arrayDesc = *(int **)(this + 0x08); 
    // +0x0C: number of elements in the array
    int elementCount = *(int *)(arrayDesc + 0x0C);

    int accumulated = 0;
    int i = 0;

    if (elementCount > 0) {
        do {
            // computeElementChecksum returns a full dword, but we only keep the low byte
            uint checksum = FUN_00558070(param1, param2); // likely computeElementChecksum
            accumulated += (checksum & 0xFF);
            i++;
        } while (i < elementCount);
    }
    return accumulated;
}