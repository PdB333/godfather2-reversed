// FUNC_NAME: PlayerInputHandler::processInput
void __thiscall PlayerInputHandler::processInput(void* thisObject, PlayerInputData* inputData)
{
    char localVar1; // uninitialized use (stack)
    char resultString[12]; // used for FUN_007266b0
    int resultCode;
    int something;

    // Check if bit 1 of flags at +0x110 is set (0x2)
    if ((*(unsigned int*)((int)inputData + 0x110) >> 1 & 1) != 0)
    {
        // Call virtual method at vtable+0x1c on the object at this+0xc (likely an animation/action controller)
        (**(void (__thiscall**)(void*))(** (void***)((int)thisObject + 0xc) + 0x1c))((void*)((int)inputData + 0x130));
        
        // Prepare a string/hash possibly from local stack (but note: stack initialization is missing)
        resultCode = FUN_007266b0((char*)&something /* stack offset -0x10 */);
        // Another function call with result code and 0
        FUN_0046fe50(resultCode, 0);
        // Set some state to 1 (likely the animation/action state)
        FUN_007270a0(*(void**)((int)thisObject + 0xc), 1);
        return;
    }

    // Check if bits 0 or 4 are set (0x11 = 0x01 | 0x10)
    if ((*(unsigned int*)((int)inputData + 0x110) & 0x11) != 0)
    {
        // Check a condition on the object at this+0xc (e.g., whether animation is already playing)
        localVar1 = FUN_00726f50(*(void**)((int)thisObject + 0xc));
        if (localVar1 != '\0')
        {
            // Check if bit 4 is set (cover/defensive action)
            if ((*(unsigned int*)((int)inputData + 0x110) >> 4 & 1) != 0)
            {
                // Same sequence as above, but with resultCode used differently
                resultCode = FUN_007266b0(resultString);
                FUN_0046fe50(resultCode, 0);
                return;
            }
            // Otherwise, clear something at +0x130 (likely stop animation/action)
            FUN_0046ffe0((void*)((int)inputData + 0x130), 0);
        }
    }
    return;
}