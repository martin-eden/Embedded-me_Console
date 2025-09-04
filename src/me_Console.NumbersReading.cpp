// Console. Reading integers implementation

/*
  Author: Martin Eden
  Last mod.: 2025-09-01
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_ReadInteger.h>

using namespace me_Console;

/*
  Read TUint_1
*/
TBool TConsole::Read(
  TUint_1 * Uint_1
)
{
  return me_ReadInteger::Read_TUint_1(Uint_1, RawConsole.GetInputStream());
}

/*
  Read TUint_2
*/
TBool TConsole::Read(
  TUint_2 * Uint_2
)
{
  return me_ReadInteger::Read_TUint_2(Uint_2, RawConsole.GetInputStream());
}

/*
  2025-09-01
*/
