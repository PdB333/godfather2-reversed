// FUNC_NAME: ConstantTable::addConstant
int ConstantTable::addConstant(int* pContext, int* pConstantData)
{
    int* pResult;
    int* pNewBuffer;
    int index;
    int* pRefEntry;

    // Determine the type of constant based on the runtime context
    if (*pContext == 3) {
        // Float constant: check if the value is already an integer representation
        if ((float)(int)(float)pContext[1] == (float)pContext[1]) {
            pResult = (int*)getFloatConstantTable(); // FUN_00637f10
            goto checkType;
        }
    }
    else if (*pContext == 4) {
        pResult = (int*)getIntConstantTable(); // FUN_00637f90
        goto checkType;
    }
    pResult = (int*)getDefaultConstantTable(); // FUN_00637ea0

checkType:
    // If the constant table entry type is 3, return the stored float as int
    if (*pResult == 3) {
        return (int)(float)pResult[1];
    }

    // Ensure the constant table has space for one more entry
    if (*(int*)((int)this + 0x28) < this->count + 1) {
        // Expand the constant table buffer
        int newBuffer = expandConstantTable(this->allocator, this->buffer, (int*)((int)this + 0x28), 8, "constant table overflow");
        this->buffer = newBuffer;
    }

    // Write the constant data into the table at the current index
    int* entry = (int*)(this->buffer + this->count * 8);
    entry[0] = pConstantData[0];
    entry[1] = pConstantData[1];

    // Add a reference to this constant in the symbol table (type 3 = constant index)
    pRefEntry = (int*)addConstantReference(this->allocator, this->somePointer);
    pRefEntry[0] = 3;
    pRefEntry[1] = (float)this->count;

    index = this->count;
    this->count = index + 1;
    return index;
}