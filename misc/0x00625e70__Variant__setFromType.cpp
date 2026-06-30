// FUNC_NAME: Variant::setFromType
void __fastcall Variant::setFromType(int param_2) // this in ECX
{
    // +0x08: Pointer to a VariantData structure (type + value pair)
    int* pData = *(int**)(this + 8);
    VariantData* pVariant = (VariantData*)(pData - 8); // Points to the pair's type field

    if (param_2 < 1)
    {
        // Initialize or reset the variant data container
        FUN_00625430();
    }

    // Read current type and fetch corresponding default pair
    if (pVariant->type == 3)
    {
        // Check for NaN? (Convert float to int and back)
        if ((float)(int)pVariant->value == pVariant->value)
        {
            VariantData* pDefault = (VariantData*)FUN_00637f10(); // get default for type 3
            *pVariant = *pDefault;
            return;
        }
    }
    else if (pVariant->type == 4)
    {
        VariantData* pDefault = (VariantData*)FUN_00637f90(); // get default for type 4
        *pVariant = *pDefault;
        return;
    }

    // Default case: type not 3 or 4, or type 3 condition failed
    VariantData* pDefault = (VariantData*)FUN_00637ea0(); // get default for other types
    *pVariant = *pDefault;
}