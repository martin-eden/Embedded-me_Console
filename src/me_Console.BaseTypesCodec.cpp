// Reading/writing subset of base types

/*
  Author: Martin Eden
  Last mod.: 2025-11-09
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_ReadInteger.h>
#include <me_WriteInteger.h>
#include <me_BooleansCodec.h>

using namespace me_Console;

// Read TUint_1
TBool TConsole::Read(
  TUint_1 * Uint_1
)
{
  return me_ReadInteger::Read_TUint_1(Uint_1, InputStream);
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

// Read TUint_2
TBool TConsole::Read(
  TUint_2 * Uint_2
)
{
  return me_ReadInteger::Read_TUint_2(Uint_2, InputStream);
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

// Print TBool
void TConsole::Print(
  TBool IsTrue
)
{
  PrintDelimiterBefore(TItemType::Number);

  me_BooleansCodec::Write(IsTrue, OutputStream);

  PrevItemType = TItemType::Number;
}

// Read TBool
TBool TConsole::Read(
  TBool * Bool
)
{
  return me_BooleansCodec::Read(Bool, InputStream);
}

/*
  2024 # # #
  2025 # #
  2025-09-01
  2025-09-12
  2025-09-23
  2025-11-09
*/
