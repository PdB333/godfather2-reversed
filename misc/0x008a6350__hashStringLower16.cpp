// FUNC_NAME: hashStringLower16
uint hashStringLower16(const char* str)

{
  undefined hashed[4];
  
  FUN_008a6270(str, &str, hashed);
  return str & 0xffff;
}