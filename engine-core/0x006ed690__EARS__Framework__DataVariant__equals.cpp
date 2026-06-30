// FUNC_NAME: EARS::Framework::DataVariant::equals
bool EARS::Framework::DataVariant::equals(DataVariant* this, uint32 dataContext)
{
    int type = this->type;          // +0x00
    bool result = false;

    if (type == 0) // char
    {
        char val1 = getChar(this->value1_part1, this->value1_part2, dataContext); // FUN_006ebff0
        char val2 = getChar(this->value2_part1, this->value2_part2, dataContext); // FUN_006ebff0
        result = (val1 == val2);
    }
    else if (type == 1) // int
    {
        int val1 = getInt(this->value1_part1, this->value1_part2, dataContext);   // FUN_006eb7b0
        int val2 = getInt(this->value2_part1, this->value2_part2, dataContext);   // FUN_006eb7b0
        return (val1 == val2);
    }
    else if (type == 2) // float
    {
        float val1 = getFloat(this->value1_part1, this->value1_part2, dataContext); // FUN_006eb7c0
        float val2 = getFloat(this->value2_part1, this->value2_part2, dataContext); // FUN_006eb7c0
        return (val1 == val2);
    }
    return result;
}