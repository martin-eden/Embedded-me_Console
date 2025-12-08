// [me_Console] Test/demo

/*
  Author: Martin Eden
  Last mod.: 2025-12-08
*/

#include <me_Console.h>

#include <me_BaseTypes.h>
#include <me_ProgramMemory.h>

/*
  Demonstrate [me_Console] usage

  Prints ASCIIZ.
  Prints integer values.
  Prints ASCIIZ in program memory.
  Uses indentation.
*/
void TestPrints()
{
  /*
    me_Console::TConsole Console;

    <me_Console.cpp> defines global variable "Console".
    So you don't need this declaration.

    You can still use it but beware that indentation will gone
    at your instance destruction.
  */

  Console.Print("--");
  Console.Print("Prints demo");
  Console.Print("");
  Console.Print("We'll show how values are represented for base types.");
  Console.Print("We'll use indentation too.");
  Console.Print("");

  Console.Print("(");
  Console.Indent();

  {
    Console.Write("TUint_1 (");
    Console.Print((TUint_1) 0x00);
    Console.Print((TUint_1) 0x7F);
    Console.Print((TUint_1) 0x80);
    Console.Print((TUint_1) 0xFF);
    Console.Write(")");
    Console.EndLine();
  }

  {
    Console.Write("TSint_1 (");
    Console.Print((TSint_1) 0x00);
    Console.Print((TSint_1) 0x7F);
    Console.Print((TSint_1) 0x80);
    Console.Print((TSint_1) 0xFF);
    Console.Write(")");
    Console.EndLine();
  }

  {
    Console.Write("TUint_2 (");
    Console.Print((TUint_2) 0x0000);
    Console.Print((TUint_2) 0x7FFF);
    Console.Print((TUint_2) 0x8000);
    Console.Print((TUint_2) 0xFFFF);
    Console.Write(")");
    Console.EndLine();
  }

  {
    Console.Write("TSint_2 (");
    Console.Print((TSint_2) 0x0000);
    Console.Print((TSint_2) 0x7FFF);
    Console.Print((TSint_2) 0x8000);
    Console.Print((TSint_2) 0xFFFF);
    Console.Write(")");
    Console.EndLine();
  }

  {
    Console.Write("TUint_4 (");
    Console.Print((TUint_4) 0x00000000);
    Console.Print((TUint_4) 0x7FFFFFFF);
    Console.Print((TUint_4) 0x80000000);
    Console.Print((TUint_4) 0xFFFFFFFF);
    Console.Write(")");
    Console.EndLine();
  }

  {
    Console.Write("TSint_4 (");
    Console.Print((TSint_4) 0x00000000);
    Console.Print((TSint_4) 0x7FFFFFFF);
    Console.Print((TSint_4) 0x80000000);
    Console.Print((TSint_4) 0xFFFFFFFF);
    Console.Write(")");
    Console.EndLine();
  }

  {
    Console.Write("TBool (");
    Console.Print(true);
    Console.Print(false);
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

    Console.Write("Program memory (");
    Console.WriteProgmem(ProgmemSeg);
    Console.Write(")");
    Console.EndLine();

    Console.Write("Program memory (via macro) (");
    Console.WriteProgmem(AsProgmemSeg("These are in program memory too"));
    Console.Write(")");
    Console.EndLine();
  }

  Console.Unindent();
  Console.Print(")");
}

void TestReads()
{
  TUint_1 Uint_1 = 0;
  TUint_2 Uint_2 = 0;
  TBool Bool = false;

  Console.Print("--");
  Console.Print("Reading demo");
  Console.Print("");
  Console.Print("We'll read from input stream and try to parse to fixed type.");
  Console.Print("");

  Console.Print("(");
  Console.Indent();

  Console.Print("Enter integer [0, 255]");

  if (!Console.Read(&Uint_1))
    Console.Print("Reading TUint_1 failed");

  Console.Write("Got");
  Console.Print(Uint_1);
  Console.EndLine();

  Console.Print("Enter integer [0, 65535]");

  if (!Console.Read(&Uint_2))
    Console.Print("Reading TUint_2 failed");

  Console.Write("Got");
  Console.Print(Uint_2);
  Console.EndLine();

  Console.Print("Enter boolean ( Y N )");

  if (!Console.Read(&Bool))
    Console.Print("Reading TBool failed");

  Console.Write("Got");
  Console.Print(Bool);
  Console.EndLine();

  Console.Unindent();
  Console.Print(")");
}

void RunTests()
{
  TestPrints();
  TestReads();
}

void setup()
{
  Console.Init();

  Console.Print("--");
  Console.Print("[me_Console] demo");
  Console.Print("");
  Console.Print("(");

  Console.Indent();

  RunTests();

  Console.Unindent();
  Console.Print(") Done");
}

void loop()
{
}

/*
  2024 # # # # # # #
  2025 # #
  2025-09-04
  2025-09-19
*/
