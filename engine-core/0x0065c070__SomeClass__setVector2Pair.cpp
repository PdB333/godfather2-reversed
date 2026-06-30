// FUNC_NAME: SomeClass::setVector2Pair
// Function at 0x0065c070: Sets a 2D vector pair (likely x,y) into an internal structure of size 0x40.
// The first parameter (this) is unused; the function copies the two values into a temporary array and passes them to FUN_0064b810 with size 0x40.
void __thiscall SomeClass::setVector2Pair(int x, int y)
{
    int temp[2]; // +0x00: x, +0x04: y
    temp[0] = x;
    temp[1] = y;
    // Invoke low-level setter; 0x40 may be size of a target structure (e.g., Matrix44 or UI element)
    FUN_0064b810(0x40, &temp);
}