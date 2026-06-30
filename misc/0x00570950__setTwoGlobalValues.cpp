// FUNC_NAME: setTwoGlobalValues
// Function address: 0x00570950
// Role: Stores two integer values into global variables at 0x01205570 and 0x01205574.
void setTwoGlobalValues(int value1, int value2)
{
    DAT_01205570 = value1;   // +0x0
    DAT_01205574 = value2;   // +0x4
}