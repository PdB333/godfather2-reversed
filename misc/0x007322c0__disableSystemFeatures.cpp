// FUNC_NAME: disableSystemFeatures
// Function address: 0x007322c0
// This function disables four system features (IDs 2,2,3,4,5) in sequence.
// Likely called during shutdown or cleanup to release specific subsystems.
void __fastcall disableSystemFeatures(void* param1)
{
    disableFeature(2, param1);  // Disable feature slot 2
    disableFeature(3, param1);  // Disable feature slot 3
    disableFeature(4, param1);  // Disable feature slot 4
    disableFeature(5, param1);  // Disable feature slot 5
    return;
}