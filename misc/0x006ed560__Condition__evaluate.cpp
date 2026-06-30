// FUNC_NAME: Condition::evaluate
bool Condition::evaluate(int* param_1, int param_2)
{
    int type = param_1[0];
    if (type == 0) {
        // Compare unsigned byte result against threshold
        unsigned char result = compareUByte(param_1[1], param_1[2], param_2);
        return *(unsigned char*)(param_1 + 3) <= result;
    }
    else if (type == 1) {
        // Compare integer result against threshold
        int result = compareInt(param_1[1], param_1[2], param_2);
        return param_1[3] <= result;
    }
    else if (type == 2) {
        // Compare float result against threshold
        float result = compareFloat(param_1[1], param_1[2], param_2);
        return (float)param_1[3] <= result;
    }
    return false;
}