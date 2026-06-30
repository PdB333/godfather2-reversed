// FUNC_NAME: ShapeQuery::executeQuery

void __thiscall ShapeQuery::executeQuery(ShapeQuery* this, const float input[10], int extraFlag, int context)
{
    this->result = 0; // +0x38

    if (this->callback != nullptr) // +0x40
    {
        // Build local data from base position (+0x20) and input
        float localData[10];
        localData[0] = this->basePos[0] + input[0]; // +0x20
        localData[1] = this->basePos[1] + input[1]; // +0x24
        localData[2] = this->basePos[2] + input[2]; // +0x28
        localData[3] = this->basePos[3] + input[3]; // +0x2c
        localData[4] = this->basePos[0] + input[4];
        localData[5] = this->basePos[1] + input[5];
        localData[6] = this->basePos[2] + input[6];
        localData[7] = this->basePos[3] + input[7];
        localData[8] = input[8];
        localData[9] = input[9];

        uint32_t callbackResult = this->callback(this->paramA, localData, *(int*)(context + 4), this->paramB); // +0x34, context+4, +0x44
        this->result = ~callbackResult; // +0x38
        if (callbackResult == 0)
            goto done;
    }

    // Default processing if callback doesn't exist or returns non-zero
    FUN_00557e20(); // defaultQueryHandler
    FUN_00a73130(input, extraFlag, context); // additionalProcessing

done:
    this->result = 0;
    return;
}