// FUNC_NAME: StringUtils::stripSuffix
void stripSuffix(char* str)
{
    // Call setup or preprocess function
    FUN_005be330();
    
    // Check condition (possibly whether to strip)
    if (FUN_005be2c0())
    {
        char* end = str;
        // Find null terminator
        while (*end != '\0')
        {
            end++;
        }
        // Truncate by removing the last 6 characters
        // index = (end - str) - 6
        str[(int)(end - str) - 6] = '\0';
    }
}