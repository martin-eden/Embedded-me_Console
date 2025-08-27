// [me_Console] Test/demo

/*
  Author: Martin Eden
  Last mod.: 2025-08-27
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_ProgramMemory.h>

/*
  Demonstrate [me_Console] usage

  Prints integer values. Representation is type-dependent.
  Uses indentation.
*/
void RunTest()
{
  /*
    me_Console::TConsole Console;

    <me_Console.cpp> defines global variable "Console".
    So you don't need this declaration.

    You can still use it but beware that indentation will gone
    at your instance destruction.
  */

  Console.Print("[me_Console] demo.");

  Console.Print("--");
  Console.Indent();

  Console.Print("We'll show how values are represented for base types.");
  Console.Print("We'll use indentation too.");

  Console.Print("--");
  Console.Indent();

  {
    Console.Write("TUint_1 (");
    Console.Print((TUint_1) 0x00);
    Console.Print((TUint_1) 0x7F);
    Console.Print((TUint_1) 0xFF);
    Console.Write(")");
    Console.EndLine();
  }

  {
    Console.Write("TSint_1 (");
    Console.Print((TSint_1) 0x80);
    Console.Print((TSint_1) 0x00);
    Console.Print((TSint_1) 0x7F);
    Console.Write(")");
    Console.EndLine();
  }

  {
    Console.Write("TUint_2 (");
    Console.Print((TUint_2) 0x0000);
    Console.Print((TUint_2) 0x7FFF);
    Console.Print((TUint_2) 0xFFFF);
    Console.Write(")");
    Console.EndLine();
  }

  {
    Console.Write("TSint_2 (");
    Console.Print((TSint_2) 0x8000);
    Console.Print((TSint_2) 0x0000);
    Console.Print((TSint_2) 0x7FFF);
    Console.Write(")");
    Console.EndLine();
  }

  {
    Console.Write("TUint_4 (");
    Console.Print((TUint_4) 0x00000000);
    Console.Print((TUint_4) 0x7FFFFFFF);
    Console.Print((TUint_4) 0xFFFFFFFF);
    Console.Write(")");
    Console.EndLine();
  }

  {
    Console.Write("TSint_4 (");
    Console.Print((TSint_4) 0x80000000);
    Console.Print((TSint_4) 0x00000000);
    Console.Print((TSint_4) 0x7FFFFFFF);
    Console.Write(")");
    Console.EndLine();
  }

  {
    static const TUint_1 ProgmemData[] [[gnu::progmem]] =
      "These characters are located in program memory";

    TAddressSegment ProgmemSeg =
      {
        .Addr = (TAddress) ProgmemData,
        .Size = sizeof(ProgmemData) - 1
      };

    Console.Write("Program memory ( ");
    Console.WriteProgmem(ProgmemSeg);
    Console.Write(" )");
    Console.EndLine();

    Console.Write("Program memory (via macro) ( ");
    Console.WriteProgmem(AsProgmemSeg("This one is in program memory also"));
    Console.Write(" )");
    Console.EndLine();
  }

  Console.Unindent();
  Console.Print("--");

  Console.Unindent();
  Console.Print("--");

  Console.Print("[me_Console] That's all folks!");
}

void setup()
{
  Console.Init();

  RunTest();
}

void loop()
{
}

/*
  2024-10 # # # # #
  2024-12 # #
  2025-08-21
  2025-08-22
*/
