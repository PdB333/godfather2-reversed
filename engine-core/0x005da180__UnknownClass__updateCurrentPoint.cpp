// FUNC_NAME: UnknownClass::updateCurrentPoint
void UnknownClass::updateCurrentPoint(int newX, int newY, int oldX, int oldY)
{
    // Assertion: newX must be non-zero and equal to oldX (the x-coordinate is constant)
    if (newX == 0 || newX != oldX) {
        FUN_00b97aea(); // Debug assertion/error – ID or x-coordinate mismatch
    }
    // If y-value changed, store the transformed old value at this+0xC
    if (newY != oldY) {
        *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xC) = FUN_005da650(oldY);
    }
    // Update the global "current point" (pointed to by ESI at call site)
    // This is a 2-int structure storing (x, y) or (id, value)
    g_currentPoint->x = newX;   // *unaff_ESI = newX
    g_currentPoint->y = newY;   // unaff_ESI[1] = newY
}