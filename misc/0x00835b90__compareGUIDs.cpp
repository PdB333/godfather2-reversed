// FUNC_NAME: compareGUIDs
int compareGUIDs(int* guid1, int* guid2)
{
    char result;
    
    // First try a more complex comparison (possibly byte-by-byte or with endianness handling)
    result = FUN_00835a60(guid1, guid2);
    if (result != '\0') {
        return 1; // GUIDs are equal (via alternate comparison)
    }
    
    // Direct integer comparison of all 6 DWORDs (24 bytes total)
    if ((((*guid1 == *guid2) && 
          (guid1[1] == guid2[1])) && 
         (guid1[2] == guid2[2])) &&
        (((guid1[3] == guid2[3] && 
           (guid1[4] == guid2[4])) && 
          (guid1[5] == guid2[5])))) {
        return 0; // GUIDs are equal
    }
    
    return 0xffffffff; // GUIDs are not equal
}