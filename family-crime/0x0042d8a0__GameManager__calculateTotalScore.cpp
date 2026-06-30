// FUNC_NAME: GameManager::calculateTotalScore
// Function: Sums a value from each element of an internal array.
// The loop iterates `count` times, where count is at this+0x650.
// Calls a helper method (likely getUnitScore) per element.
int GameManager::calculateTotalScore()
{
    int totalSum = 0;
    int elementCount = *(int*)((char*)this + 0x650); // +0x650: number of elements in the collection

    for (int i = 0; i < elementCount; i++)
    {
        // Note: The decompilation shows getUnitScore(this) without an index,
        // but the loop pattern strongly suggests an index parameter is passed.
        // We assume the function signature is getUnitScore(int index).
        int elementValue = getUnitScore(i);
        totalSum += elementValue;
    }
    return totalSum;
}