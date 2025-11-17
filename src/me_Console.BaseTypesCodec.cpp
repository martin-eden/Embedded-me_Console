// Reading/writing subset of base types

/*
  Author: Martin Eden
  Last mod.: 2025-11-17
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_BaseTypesIo.h>

using namespace me_Console;

/*
  Read and write types support

  Type            TBool TUint_1 TUint_2 TUint_4 TSint_1 TSint_2 TSint_4
  Can be printed    x      x       x       x       x       x       x
  Can be read       x      x       x       -       -       -       -
*/

// ( Prints

// Print TBool
void TConsole::Print(
  TBool IsTrue
)
{
  PrintDelimiterBefore(TItemType::Number);

  me_BaseTypesIo::Write_Bool(IsTrue, OutputStream);

  PrevItemType = TItemType::Number;
}

// Print TUint_1
void TConsole::Print(
  TUint_1 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_BaseTypesIo::Write_Uint_1(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TUint_2
void TConsole::Print(
  TUint_2 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_BaseTypesIo::Write_Uint_2(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TUint_4
void TConsole::Print(
  TUint_4 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_BaseTypesIo::Write_Uint_4(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TSint_1
void TConsole::Print(
  TSint_1 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_BaseTypesIo::Write_Sint_1(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TSint_2
void TConsole::Print(
  TSint_2 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_BaseTypesIo::Write_Sint_2(Value, OutputStream);
  PrevItemType = ItemType;
}

// Print TSint_4
void TConsole::Print(
  TSint_4 Value
)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_BaseTypesIo::Write_Sint_4(Value, OutputStream);
  PrevItemType = ItemType;
}

// )

// ( Reads

// Read TBool
TBool TConsole::Read(
  TBool * Bool
)
{
  return me_BaseTypesIo::Read_Bool(Bool, InputStream);
}

// Read TUint_1
TBool TConsole::Read(
  TUint_1 * Uint_1
)
{
  return me_BaseTypesIo::Read_Uint_1(Uint_1, InputStream);
}

// Read TUint_2
TBool TConsole::Read(
  TUint_2 * Uint_2
)
{
  return me_BaseTypesIo::Read_Uint_2(Uint_2, InputStream);
}

// )

/*
  2024 # # #
  2025 # #
  2025-09-01
  2025-09-12
  2025-09-23
  2025-11-09
  2025-11-17
*/
