// FUNC_NAME: ScriptContext::intArgToString
// Address: 0x0046b060
// Converts an Int32 script argument to a string and pushes it onto the internal stack (param_1).
// Returns 1 on success, 0 on failure (though error path always returns 1? Possibly prints error and continues).

undefined4 ScriptContext::intArgToString(undefined4 param_1)
{
    undefined4 *puVar1;
    char local_20 [32];
    
    // Retrieve the first script argument (index 1) with expected type "Int32"
    puVar1 = (undefined4 *)FUN_00627e50(1, "Int32");
    if (puVar1 == (undefined4 *)0x0) {
        // If not found or type mismatch, print error and possibly use default
        puVar1 = (undefined4 *)FUN_00627bd0("1st argument must be a %s.\n", "Int32");
    }
    // Format the integer value as a decimal string
    __snprintf(local_20, 0x20, "%d", *puVar1);
    // Push the string onto the script stack (or set a property on param_1)
    FUN_00625ca0(param_1, local_20);
    return 1;
}