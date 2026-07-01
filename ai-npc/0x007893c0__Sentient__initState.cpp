// FUNC_NAME: Sentient::initState

void __thiscall Sentient::initState(int thisPtr)
{
    int iteration = 2;
    do
    {
        // Perform internal initialization (maybe physics or animation buffer reset)
        FUN_004df590();
        iteration--;
    } while (iteration != 0);
    // Clear the "first update required" flag at offset +0xE4
    *(uint8_t*)(thisPtr + 0xE4) = 0;
}