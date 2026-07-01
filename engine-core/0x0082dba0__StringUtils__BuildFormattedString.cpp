// FUNC_NAME: StringUtils::BuildFormattedString
/* Function at 0x0082dba0 - Constructs a formatted string using three helper steps.
   Likely part of EA EARS string utilities. Uses temporary buffers of 96 and 108 bytes.
   Parameters:
     param_1 (char* output) - destination string buffer
     param_2 (const char* str2) - second string component
     param_3 (const char* fmt) - format string or delimiter
     param_4 (const char* str1) - first string component
   Returns output pointer. */
char* __cdecl StringUtils::BuildFormattedString(char* output, const char* str2, const char* fmt, const char* str1)
{
    char tempBuffer1[96];   // 96-byte temporary buffer
    char tempBuffer2[108];  // 108-byte temporary buffer
    int intermediate;       // holds result from subfunctions

    // Step 1: Format first component into tempBuffer1 using fmt and str1
    intermediate = sub_format(tempBuffer1, str1, fmt);   // FUN_009d3830
    // Step 2: Append str2 to tempBuffer2, using intermediate (likely length) from step 1
    intermediate = sub_append(tempBuffer2, str2, intermediate); // FUN_009d3960
    // Step 3: Finalize output using fmt and the intermediate result (likely length or buffer)
    sub_final(output, fmt, intermediate); // FUN_009d3790

    return output;
}