// FUNC_NAME: sortThreeValues
void sortThreeValues(int* a, int* b, int* c)
{
    int tempA = *a;
    int tempB = *b;
    int tempC = *c;
    char result;

    // Compare and swap a and b
    result = FUN_00587780(tempA);
    if (result != '\0') {
        *a = tempB;
        *b = tempA;
    }

    // Compare and swap b and c
    tempB = *b;
    tempA = *a;
    result = FUN_00587780(tempA);
    if (result != '\0') {
        *c = tempA;
        *a = tempB;
    }

    // Compare and swap a and b again
    tempA = *a;
    tempB = *b;
    result = FUN_00587780(tempA);
    if (result != '\0') {
        *b = tempA;
        *a = tempB;
    }
}