// FUNC_NAME: Variant::resolveWithDefault (or VariantResolveFunction)

struct Variant {
    uint8_t type;       // +0x00: 2 = string/object type, 0 = empty, others?
    uint8_t pad[3];     // +0x01-0x03
    uint32_t data[8];   // +0x04: 32 bytes of payload
};

// external deep copy function for type 2 (e.g., string duplication)
void __fastcall VariantDeepCopy(Variant* dest); // address 0x00582ea0

// global default variant pointer (ESI register)
extern Variant* g_defaultVariant; // = (Variant*)0x... 

// Resolve variant assignment: if source has type 2, use it; otherwise fall back to g_defaultVariant
void __fastcall resolveVariant(Variant* source, Variant* dest) // ecx=source, edx=dest
{
    uint8_t srcType = source->type;
    uint8_t defType = g_defaultVariant->type;

    if (srcType == 2) {
        dest->type = 2;
        if (defType == 2) {
            VariantDeepCopy(dest);
            return;
        }
        // copy source data
        uint32_t* srcData = source->data;
        uint32_t* dstData = dest->data;
        dstData[0] = srcData[0];
        dstData[1] = srcData[1];
        dstData[2] = srcData[2];
        dstData[3] = srcData[3];
        dstData[4] = srcData[4];
        dstData[5] = srcData[5];
        dstData[6] = srcData[6];
        dstData[7] = srcData[7];
    } else {
        if (defType != 2) {
            dest->type = 0;
            return;
        }
        dest->type = 2;
        uint32_t* defData = g_defaultVariant->data;
        uint32_t* dstData = dest->data;
        dstData[0] = defData[0];
        dstData[1] = defData[1];
        dstData[2] = defData[2];
        dstData[3] = defData[3];
        dstData[4] = defData[4];
        dstData[5] = defData[5];
        dstData[6] = defData[6];
        dstData[7] = defData[7];
    }
}