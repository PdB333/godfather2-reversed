// FUNC_NAME: sortThreeAscending
// 0x0068ee60: Sorts three values in ascending order using a comparison function (sorting network)
void sortThreeAscending(int* a, int* b, int* c, char (*comparator)(int, int))
{
    char result;
    int temp;

    // Compare & swap b, a
    result = comparator(*b, *a);
    if (result != 0)
    {
        temp = *b;
        *b = *a;
        *a = temp;
    }

    // Compare & swap c, b
    result = comparator(*c, *b);
    if (result != 0)
    {
        temp = *c;
        *c = *b;
        *b = temp;
    }

    // Compare & swap b, a (final pass)
    result = comparator(*b, *a);
    if (result != 0)
    {
        temp = *b;
        *b = *a;
        *a = temp;
    }
}