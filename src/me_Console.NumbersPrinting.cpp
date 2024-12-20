// Printing integer types in decimal ASCII

/*
  Author: Martin Eden
  Last mod.: 2024-12-19
*/

/*
  Very boring code.

  We support six integer types:

    TUint_1  TSint_1
    TUint_2  TSint_2
    TUint_4  TSint_4

  We promised to provide overridden Print() for each of them.
*/

#include <me_Console.h>

#include <me_CodecDecInt.h> // Encode()
#include <me_Uart.h> // Op_PutByte()

using namespace me_Console;

using me_CodecDecInt::Encode;

const TOperation PrintByte = me_Uart::Op_PutByte;

/*
  Base code will be repeated six times. Difference is type of argument.
*/

// Print TUint_4
void TConsole::Print(TUint_4 Value)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  Encode(Value, PrintByte);
  PrevItemType = ItemType;
}

// Print TUint_2
void TConsole::Print(TUint_2 Value)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  Encode(Value, PrintByte);
  PrevItemType = ItemType;
}

// Print TUint_1
void TConsole::Print(TUint_1 Value)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  Encode(Value, PrintByte);
  PrevItemType = ItemType;
}

// Print TSint_4
void TConsole::Print(TSint_4 Value)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  Encode(Value, PrintByte);
  PrevItemType = ItemType;
}

// Print TSint_2
void TConsole::Print(TSint_2 Value)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  Encode(Value, PrintByte);
  PrevItemType = ItemType;
}

// Print TSint_1
void TConsole::Print(TSint_1 Value)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  Encode(Value, PrintByte);
  PrevItemType = ItemType;
}

/*
  2024-10-17
  2024-12-18
  2024-12-19
*/
