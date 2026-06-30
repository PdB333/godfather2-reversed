// FUNC_NAME: SomeManager::getItemData
void __thiscall SomeManager::getItemData(int id, ItemData* outData)
{
    byte buffer[76]; // local_50: temporary buffer for raw data from virtual call
    StackStruct stackStruct; // auStack_98 and subsequent locals, total 16 dwords (64 bytes)

    // Virtual call: likely retrieves item data into buffer
    (*(void (__thiscall**)(int, byte*))(*(int*)this + 0x254))(id, buffer);

    // Initialize stackStruct with default values
    FUN_00aa1a10(&stackStruct);

    // Copy selective fields from stackStruct into output
    outData->field0 = stackStruct.field0;
    outData->field1 = stackStruct.field1;
    outData->field2 = stackStruct.field2;
    outData->field4 = stackStruct.field4;
    outData->field5 = stackStruct.field5;
    outData->field6 = stackStruct.field6;
    outData->field8 = stackStruct.field8;
    outData->field9 = stackStruct.field9;
    outData->fieldA = stackStruct.fieldA;
    outData->fieldC = stackStruct.fieldC;
    outData->fieldD = stackStruct.fieldD;
    outData->fieldE = stackStruct.fieldE;

    // Modify some fields
    stackStruct.field3 = 0;
    stackStruct.field7 = 0;
    stackStruct.fieldB = 0;
    stackStruct.fieldF = DAT_00e2b1a4;

    // Possibly apply logic based on buffer
    FUN_00417560();

    // Copy all 16 dwords from stackStruct to output
    for (int i = 0; i < 16; i++) {
        outData[i] = ((unsigned int*)&stackStruct)[i];
    }
}