// FUNC_NAME: SomeClass::shuffleThree
void __thiscall SomeClass::shuffleThree(int *param1, int *param2)
{
    int a = *this;          // +0x00 (first member)
    int b = *param1;
    int c = *param2;

    // Three random conditional swaps yield a uniform random permutation of a,b,c
    if (randomBoolean()) {
        *this = b;
        *param1 = a;
        a = *this;  // update a after swap (a is now old b)
    }
    // After first swap, a = *this, b = *param1 (original a or b), c unchanged

    if (randomBoolean()) {
        *param2 = *this;    // swap a and c
        *this = c;
        c = *param2;
        a = *this;          // update a (now old c)
    }
    // After second swap, a = *this, c = *param2, b unchanged

    if (randomBoolean()) {
        *this = *param1;
        *param1 = a;
    }
    // final swap between a (which is *this after modifications) and b (*param1)
}