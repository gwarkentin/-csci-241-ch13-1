# csci-241-ch13-1
Inline_Assembly_Prime_Check

Let the user input numbers repeatedly to display a message for each one indicating whether it is prime or not until -1 entered:
Enter an integer (-1 to exit) : 111
isPrimeC:   111 is NOT prime
inlineASM:  111 is NOT prime
inlineASM2: 111 is NOT prime
Enter an integer (-1 to exit) : 101
isPrimeC:   101 is prime
inlineASM:  101 is prime
inlineASM2: 101 is prime
Enter an integer (-1 to exit) :
A C-function can be: (if not familiar, Ref: Prime number)
bool isPrimeC(int n)
{
   bool ret =false;

   if (n >=2) 
   { 
      int divisor;
      for ( divisor = 2; divisor <= n / 2; divisor++)
      {
         if (n % divisor == 0)
            break;
      }

      if (divisor > n / 2)
         ret = true;
   }
   return ret;
}
You are required to make two C++ functions here. Practice inline assembly by defining all logic in a C function:
bool isPrimeC_inlineASM(int n)
{
   __asm {
      ; fill is prime logic here...
      }      // asm
}
Again, practice inline assembly partially defining like this:
bool isPrimeC_inlineASM2(int n)
{
      bool isPrime = true;

//  if (n <2) isPrime = false;
      __asm {
            ; ...
      }

      if (!isPrime)
         return false;

      for (int divisor = 2; divisor <= n/2; divisor++)
      {
         __asm {
            ; fill is prime checking here...
            ; ...
            }      // asm

         if (!isPrime)
            break;
      }
      return isPrime;
}
Make sure each implementation of inline assembly is called and working correctly. Recommended tests in main would be like this. Think of why not use && or || conditional logic?
   cout << "isPrimeC:   " << N << " is " << (isPrimeC(N)?  "" : "NOT ") << "prime\n";
   cout << "inlineASM:  " << N << " is " << (isPrimeC_inlineASM(N)?  "" : "NOT ") << "prime\n";
   cout << "inlineASM2: " << N << " is " << (isPrimeC_inlineASM2(N)?  "" : "NOT ") << "prime\n";
// for next C_Assembly_Mixed_Call
   cout << "isPrimeASM: " << N << " is " << (isPrimeASM(N)?  "" : "NOT ") << "prime\n\n";
In isPrimeC_inlineASM, you can set a return Boolean value to EAX fine without need of the return statement.
If you see the compiling message: C4716: 'isPrimeC_inlineASM' : must return a value and you want to remove it, simply add #pragma warning:

#pragma warning(disable: 4716)
