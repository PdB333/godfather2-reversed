// FUNC_NAME: PropertyVariant::isNotEqual
bool PropertyVariant::isNotEqual(int param2) {
    int type = this->type;
    bool result = false;

    if (type == 0) {
        // Character comparison (likely bool or char)
        char val1 = getCharFromValue(this->value1_part1, this->value1_part2, param2);
        char val2 = getCharFromValue(this->value2_part1, this->value2_part2, param2);
        result = (val1 != val2);
    } else if (type == 1) {
        // Integer comparison
        int val1 = getIntFromValue(this->value1_part1, this->value1_part2, param2);
        int val2 = getIntFromValue(this->value2_part1, this->value2_part2, param2);
        return (val1 != val2);
    } else if (type == 2) {
        // Float comparison
        double val1 = (double)getFloatFromValue(this->value1_part1, this->value1_part2, param2);
        double val2 = (double)getFloatFromValue(this->value2_part1, this->value2_part2, param2);
        if (val1 != val2) {
            return true;
        }
        return false;
    }
    return result;
}