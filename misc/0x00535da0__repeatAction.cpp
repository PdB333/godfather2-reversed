// FUNC_NAME: repeatAction
// Address: 0x00535da0
// Calls an underlying function (FUN_005357a0) a specified number of times.
// Parameter passed via EAX (likely __fastcall or register optimization).
void __fastcall repeatAction(int count)
{
    if (count > 0) {
        do {
            FUN_005357a0();  // Perform the action once
            count--;
        } while (count != 0);
    }
}