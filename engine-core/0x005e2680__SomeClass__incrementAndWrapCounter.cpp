// FUNC_NAME: SomeClass::incrementAndWrapCounter
void __thiscall SomeClass::incrementAndWrapCounter(void) {
    int counter = *(int *)((char *)this + 0x1748); // +0x1748: counter field
    counter++;
    if (counter == -1) {
        counter = 0;
    }
    *(int *)((char *)this + 0x1748) = counter;
}