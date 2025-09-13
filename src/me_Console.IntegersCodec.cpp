// Reading/writing integer numbers for [me_Console]

/*
  Author: Martin Eden
  Last mod.: 2025-09-13
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_ReadInteger.h>
#include <me_WriteInteger.h>

using namespace me_Console;

// Read TUint_1
TBool TConsole::Read(
  TUint_1 * Uint_1
)
{
  return me_ReadInteger::Read_TUint_1(Uint_1, InputStream);
}

// Read TUint_2
TBool TConsole::Read(
  TUint_2 * Uint_2
)
{
  return me_ReadInteger::Read_TUint_2(Uint_2, InputStream);
}

// Print TUint_1
void TConsole::Print(
  TUint_1 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_U1(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TUint_2
void TConsole::Print(
  TUint_2 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_U2(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TUint_4
void TConsole::Print(
  TUint_4 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_U4(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TSint_1
void TConsole::Print(
  TSint_1 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_S1(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TSint_2
void TConsole::Print(
  TSint_2 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_S2(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TSint_4
void TConsole::Print(
  TSint_4 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_S4(Value, OutputStream);
  PrevItemType = ItemType;
}

/*
  2024 # # #
  2025 # #
  2025-09-01
  2025-09-12
*/
