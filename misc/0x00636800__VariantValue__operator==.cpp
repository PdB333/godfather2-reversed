// FUNC_NAME: VariantValue::operator==
bool __fastcall VariantValue::operator==(const VariantValue& other) const
{
    // Compare type tags first
    if (type != other.type) {
        return false;
    }

    switch (type) {
        case 0: // Null or invalid type – treat as equal if both are type 0
            return true;
        case 3: // Float data
            return floatValue == other.floatValue;
        default: // Integer data (types 1 and 2)
            return intValue == other.intValue;
    }
}