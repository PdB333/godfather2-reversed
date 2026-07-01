// FUNC_NAME: getTotalValue
// Address: 0x008bd300
// Role: Utility function that sums two values obtained from other global functions.
int getTotalValue()
{
    int firstValue = getFirstValue();  // Calls FUN_006b1a20
    int secondValue = getSecondValue(); // Calls FUN_006b1a40
    return firstValue + secondValue;
}