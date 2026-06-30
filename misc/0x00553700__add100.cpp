// FUNC_NAME: add100
// Function at 0x00553700: simple utility that adds 100 to its integer argument.
// Called three times from 0x00809980, possibly to apply a fixed offset (e.g., health, score, or damage modifier).
int __fastcall add100(int value)
{
    return value + 100;
}