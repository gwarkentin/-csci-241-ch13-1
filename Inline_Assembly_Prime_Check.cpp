/*
Program: Inline_Assembly_Prime_Check (Chapter 13, inline assembly)
Description: Check if prime number with various levels of inline assembly
Student:     Gabriel Warkentin
Date:        05/05/2020
Class:       CSCI 241
Instructor:  Mr. Ding
*/

#include<iostream>

using namespace std;

bool isPrimeC(int n)
{
    bool ret = false;

    if (n >= 2)
    {
        int divisor;
        for (divisor = 2; divisor <= n / 2; divisor++)
        {
            if (n % divisor == 0)
                break;
        }

        if (divisor > n / 2)
            ret = true;
    }
    return ret;
}

bool isPrimeC_inlineASM(int n) {
    __asm {
        mov ebx, n      // save n to register
        mov ecx, 2

        push edi        // c expects preserved but I'm out of regs
        mov edi, ebx
        sar edi, 1      // n/2

        cmp ebx, ecx
        jl Lfalse
    L1:
        cmp ecx, edi
        jg Ltrue         //made more clear
        mov eax, ebx
        mov edx, 0
        div ecx
        cmp edx, 0
        je Lfalse       //made more clear
        inc ecx
        jmp L1
    Ltrue:
        mov eax, 1
        jmp Lreturn
    Lfalse:
        mov eax, 0
    Lreturn:
        pop edi
    }

}

bool isPrimeC_inlineASM2(int n)
{
    bool isPrime = true;

    //  if (n <2) isPrime = false;
    __asm {
        mov eax, n
        cmp eax, 2
        jge L1
        mov isPrime, 0
        L1:
    }

    if (!isPrime)
        return false;

    for (int divisor = 2; divisor <= n / 2; divisor++)
    {
        __asm {
            mov eax, n
            mov edx, 0
            div divisor
            cmp edx, 0
            jne Lnext
            mov isPrime, 0
            Lnext:

        }      // asm

        if (!isPrime)
            break;
    }
    return isPrime;
}


int main() {
    int N = 0;

    while (true) {
        cout << "Enter an integer (-1 to exit) : ";
        cin >> N;
        if (N == -1) { break; }
        cout << "isPrimeC:   " << N << " is " << (isPrimeC(N) ? "" : "NOT ") << "prime\n";
        cout << "inlineASM:  " << N << " is " << (isPrimeC_inlineASM(N) ? "" : "NOT ") << "prime\n";
        cout << "inlineASM2: " << N << " is " << (isPrimeC_inlineASM2(N) ? "" : "NOT ") << "prime\n\n";
        // cout << "isPrimeASM: " << N << " is " << (isPrimeASM(N) ? "" : "NOT ") << "prime\n\n";
    }
}