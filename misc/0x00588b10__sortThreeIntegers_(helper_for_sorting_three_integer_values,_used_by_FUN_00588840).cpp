// FUNC_NAME: sortThreeIntegers (helper for sorting three integer values, used by FUN_00588840)
// Address: 0x00588b10
// Role: Sorts three integer values pointed to by three pointers (first passed in ESI,
//        second and third as parameters). Uses a comparison function at 0x00587780
//        that likely checks if first < second. The function performs a bubble-sort
//        style swap sequence to order the values.

// Comparison function (external, defined at 0x00587780)
// Returns non-zero if condition is met (e.g., left < right)
extern char compareInts(int a, int b); // placeholder name

// This function takes three int pointers and sorts the integers in ascending order.
// The first pointer is passed in register ESI (implicit in original x86 convention).
// In C++ we model it as a regular function with three parameters.
void sortThreeIntegers(int* first, int* second, int* third) {
    int temp;

    // Compare first and second, swap if out of order
    if (compareInts(*first, *second)) {
        temp = *first;
        *first = *second;
        *second = temp;
    }

    // Compare third and first (after possible swap)
    if (compareInts(*third, *first)) {
        temp = *third;
        *third = *first;
        *first = temp;
    }

    // Compare second and first again
    if (compareInts(*second, *first)) {
        temp = *second;
        *second = *first;
        *first = temp;
    }
}