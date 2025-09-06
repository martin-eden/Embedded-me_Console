// Printing integer types in decimal ASCII

/*
  Author: Martin Eden
  Last mod.: 2025-09-06
*/

/*
  Very boring code

  We support six integer types:

    TUint_1  TSint_1
    TUint_2  TSint_2
    TUint_4  TSint_4

  We promised to provide overridden Print() for each of them.
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_WriteInteger.h>

using namespace me_Console;

/*
  Base code will be repeated six times. Difference is type of argument.
*/

// Print TUint_4
void TConsole::Print(
  TUint_4 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_U4(Value, RawConsole.GetOutputStream());
  PrevItemType = ItemType;
}

// Print TUint_2
void TConsole::Print(
  TUint_2 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_U2(Value, RawConsole.GetOutputStream());
  PrevItemType = ItemType;
}

// Print TUint_1
void TConsole::Print(
  TUint_1 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_U1(Value, RawConsole.GetOutputStream());
  PrevItemType = ItemType;
}

// Print TSint_4
void TConsole::Print(
  TSint_4 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_S4(Value, RawConsole.GetOutputStream());
  PrevItemType = ItemType;
}

// Print TSint_2
void TConsole::Print(
  TSint_2 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_S2(Value, RawConsole.GetOutputStream());
  PrevItemType = ItemType;
}

// Print TSint_1
void TConsole::Print(
  TSint_1 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_WriteInteger::Write_S1(Value, RawConsole.GetOutputStream());
  PrevItemType = ItemType;
}

/*
  2024 # # #
  2025 # #
*/
