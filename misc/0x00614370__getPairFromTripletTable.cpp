// FUNC_NAME: getPairFromTripletTable
void getPairFromTripletTable(int index, int *outValue1, int *outValue2)
{
    // Table at 0x011f6bb8 contains triplets (3 values per entry)
    // This function retrieves the first two values of the triplet at the given index
    *outValue1 = (&DAT_011f6bb8)[index * 3];    // First value in triplet
    *outValue2 = (&DAT_011f6bbc)[index * 3];    // Second value in triplet (offset +4 bytes from first)
    return;
}