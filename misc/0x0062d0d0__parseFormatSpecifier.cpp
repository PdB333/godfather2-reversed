// FUNC_NAME: parseFormatSpecifier
byte* parseFormatSpecifier(undefined4 param_1, byte* param_2, undefined1* param_3, undefined4* param_4)
{
    byte* pbVar1;
    byte bVar2;
    char* pcVar3;
    int iVar4;
    byte* pbVar5;
    
    // Skip any flag characters: '-', '+', ' ', '#', '0'
    pcVar3 = _strchr("-+ #0", (int)(char)*param_2);
    pbVar5 = param_2;
    while (pcVar3 != (char*)0x0) {
        pbVar1 = pbVar5 + 1;
        pbVar5 = pbVar5 + 1;
        pcVar3 = _strchr("-+ #0", (int)(char)*pbVar1);
    }
    
    // Check for width digit
    iVar4 = _isdigit((uint)*pbVar5);
    if (iVar4 != 0) {
        pbVar5 = pbVar5 + 1;
    }
    
    // Check for second width digit
    iVar4 = _isdigit((uint)*pbVar5);
    if (iVar4 != 0) {
        pbVar5 = pbVar5 + 1;
    }
    
    // Check for precision specifier ('.')
    if (*pbVar5 == 0x2e) {
        bVar2 = pbVar5[1];
        *param_4 = 1;  // Set precision flag
        iVar4 = _isdigit((uint)bVar2);
        pbVar1 = pbVar5 + 1;
        if (iVar4 != 0) {
            pbVar1 = pbVar5 + 2;
        }
        pbVar5 = pbVar1;
        
        // Check for second precision digit
        iVar4 = _isdigit((uint)*pbVar5);
        if (iVar4 != 0) {
            pbVar5 = pbVar5 + 1;
        }
    }
    
    // Validate no additional digits (width/precision too long)
    iVar4 = _isdigit((uint)*pbVar5);
    if (iVar4 != 0) {
        FUN_00627bd0("invalid format (width or precision too long)");
    }
    
    // Validate total format specifier length
    if (0x14 < (int)(pbVar5 + (2 - (int)param_2))) {
        FUN_00627bd0("invalid format (too long)");
    }
    
    // Build the format specifier: start with '%'
    *param_3 = 0x25;
    _strncpy(param_3 + 1, (char*)param_2, (size_t)(pbVar5 + (1 - (int)param_2)));
    param_3[(int)(pbVar5 + (2 - (int)param_2))] = 0;  // Null-terminate
    
    return pbVar5;  // Return pointer to end of parsed format
}