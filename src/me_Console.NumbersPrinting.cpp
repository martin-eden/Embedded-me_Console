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

  template <typename IntType>
void TConsole::Print(IntType IntValue)
{
  TItemType ItemType = TItemType::Number;
  PrintDelimiterBefore(ItemType);
  me_CodecDecInt::Encode(IntValue, me_Uart::Op_PutByte);
  PrevItemType = ItemType;
}

/*
  2024-10-17
  2024-12-18
  2024-12-19
*/
