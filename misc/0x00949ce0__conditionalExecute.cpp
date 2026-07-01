// FUNC_NAME: conditionalExecute
void __cdecl conditionalExecute(int param1, int param2)
{
    int result = lookupIndex(&param1); // FUN_00949380, checks param1 validity (e.g., returns >=0 if valid)
    if (result >= 0) {
        handleAction(param2); // FUN_009496d0, executes action on param2
    }
}