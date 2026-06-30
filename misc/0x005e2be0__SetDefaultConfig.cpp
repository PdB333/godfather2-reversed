// FUNC_NAME: SetDefaultConfig
// Function address: 0x005e2be0
// Role: Initializes a configuration structure with default values (first field = 1, others = 0) and passes it to another function.

struct ConfigParams {
    int field0; // +0x00
    int field1; // +0x04
    int field2; // +0x08
    int field3; // +0x0C
};

void FUN_005e2440(ConfigParams* params); // forward declaration

void SetDefaultConfig(void)
{
    ConfigParams params;
    params.field0 = 1;
    params.field1 = 0;
    params.field2 = 0;
    params.field3 = 0;
    FUN_005e2440(&params);
    return;
}