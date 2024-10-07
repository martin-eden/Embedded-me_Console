// Serial console interface

/*
  Author: Martin Eden
  Status: sketched
  Last mod.: 2024-10-06
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

namespace me_Console
{
  /*
    Currently "console" is values printer to Serial.

    There are two modes of output: "Print" and "Write".

    Assumption of "Print" is that it writes delimited value.
    So it keeps granularity. And that value can be read
    back from stream someday.

    For example Print(TUint_1 42) may produce "TUint_1(42)".
    Or " 42 ". But output should be distinguishable from
    Print(TUint_2 42). Which in our example may produce
    "TUint_2(42)" or " 00042 ".

    "Write" writes in binary. No values granularity. Result
    is byte stream.

    This implementation implements Print() for base types.

       Value | TUint_1 | TUint_2 | TSint_1 | TSint_2
      -------+---------+---------+---------+---------
         0   | 000     | 00000   | +000    | +00000
         42  | 042     | 00042   | +042    | +00042

       Value | Print()   | Write()
       ------+-----------+---------
       Hello | \nHello\n | Hello
  */

  class TConsole
  {
    public:
      // Initialize UART to given speed
      TBool Init(TUint_4 SerialSpeed);

      // ( Indents!

      // Increase indent
      void Indent();

      // Decrease indent
      void Unindent();

      // ) Indents!

      // ( Write data

      // Data is memory segment
      void Write(me_MemorySegment::TMemorySegment Data);
      // Data is ASCIIZ pointer
      void Write(const TChar * String);

      // ) Write

      // ( Print string on newline with newline

      // Data is memory segment
      void Print(me_MemorySegment::TMemorySegment Data);
      // Data is ASCIIZ pointer
      void Print(const TChar * Asciiz);

      // ) Print

      // Print newline
      void Newline();

      // Print space
      void Space();

      // Print separation line
      void Line();

      // ( Custom printers for base types

      // Print TUint_1
      void Print(TUint_1 Uint_1);
      // Print TUint_2
      void Print(TUint_2 Uint_2);
      // Print TUint_4
      void Print(TUint_4 Uint_4);
      // Print TSint_1
      void Print(TSint_1 Sint_1);
      // Print TSint_2
      void Print(TSint_2 Sint_2);
      // Print TSint_4
      void Print(TSint_4 Sint_4);

      // ) Custom printers

    private:
      /*
        Internal mechanics to avoid double spaces and heading/trailing
        spaces in output.

        Need to emit Print()-specific delimiter (newline or space)
      */
      TBool NeedDelimiter;

      // Indentation level
      TUint_1 IndentLev;

      // Flag that current line is empty
      TBool LineIsEmpty;

      // Prints space before number if needed
      void ApplyNumberNeeds();

      // Prints newline before string if needed
      void ApplyStringNeeds();

  };

  namespace Freetown
  {
    // Print uncooked contents of memory segment to stdout
    void PrintSeg(me_MemorySegment::TMemorySegment Data);

    // Print indentation
    void PrintIndent(TUint_1 IndentLev);
  }
}

/*
  2024-10-03
  2024-10-06
*/
