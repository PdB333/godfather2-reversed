// FUNC_NAME: initializeSevenSlots
void initializeSevenSlots(void)
{
    int count = 7;
    do
    {
        initializeSlot(); // Calls FUN_00897da0 - per-slot initialization
        count--;
    } while (count != 0);
}