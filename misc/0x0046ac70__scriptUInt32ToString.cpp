// FUNC_NAME: scriptUInt32ToString
int scriptUInt32ToString(void* output) // output is likely a StringBuffer or similar
{
    char buffer[32];
    uint32_t* arg = (uint32_t*)getScriptArgTyped(1, "UInt32"); // Retrieve argument index 1, expecting UInt32 type
    if (arg == nullptr)
    {
        arg = (uint32_t*)reportScriptArgError("1st argument must be a %s.\n", "UInt32"); // Print error and return default
    }
    snprintf(buffer, sizeof(buffer), "%u", *arg); // Format the uint32 as decimal string
    appendToStringBuffer(output, buffer); // Append formatted string to output buffer
    return 1;
}