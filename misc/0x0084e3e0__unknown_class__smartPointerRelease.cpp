// FUNC_NAME: unknown_class::smartPointerRelease
void __fastcall smartPointerRelease(int *param_1)
{
  if (*param_1 != 0) {
    releaseRef(*param_1); // likely a ref count decrement or delete
  }
  return;
}