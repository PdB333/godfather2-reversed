// FUNC_NAME: allocateArray40Bytes
void allocateArray40Bytes(uint elementCount)
{
    if (elementCount == 0) {
        elementCount = 0;
    }
    else if ((0xffffffff / elementCount) < 0x28) {
        // overflow detected, throw bad allocation
        void **throwInfo = &PTR_LAB_00e31050;
        uint *throwCode = (uint *)0x0;
        // invoke custom throw handler if registered
        if (DAT_0113d3a0 != (code *)0x0) {
            (*DAT_0113d3a0)(&throwInfo);
        }
        // call the throw function via table entry index 2
        (*(code *)throwInfo[2])();
        std::_Throw((exception *)&throwInfo);
    }
    // allocate memory for elementCount elements of size 0x28
    FUN_009c8e50(elementCount * 0x28);
}