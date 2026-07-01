// FUNC_NAME: compareHandleValues (comparator for object handles based on a global sort value)
int __cdecl compareHandleValues(int* pHandle1, int* pHandle2)
{
    float value1 = 0.0f;
    float value2 = 0.0f;

    // Check if handle1 points to a valid object and that object's first int field is non-zero (e.g., active flag)
    if ( (*(void**)*pHandle1 != NULL) && (*(int*)*pHandle1 != 0) )
    {
        value1 = (float)getGlobalSortValue(); // Returns some float used for ordering
    }

    if ( (*(void**)*pHandle2 != NULL) && (*(int*)*pHandle2 != 0) )
    {
        value2 = (float)getGlobalSortValue();
    }

    // Returns -1 if second has smaller value (descending order: larger values first)
    if (value2 < value1) return -1;
    if (value1 < value2) return 1;
    return 0;
}