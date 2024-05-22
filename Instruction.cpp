#include "Instruction.h"
#include "AssemblyLangInterpreter.h"

using namespace std;

// Implementation of the DEC instruction
Dec::Dec(string symbol) : symbol(std::move(symbol)) {}

bool Dec::execute(AssemblyLangInterpreter& a) {
    // Convert the symbol to its corresponding address
    int loc = a.convert(this->symbol);

    // Check if the address is within the data memory range
    if (loc >= 128 && loc < 256) {
        // Set the value at the specified address to 0
        a.dataVect[loc - 128] = 0;
    }

    // Increment the program counter
    return 1;
}

string Dec::to_string() const {
    return "DEC " + symbol;
}

// Implementation of the LDA instruction
Lda::Lda(string sym) : symbol(std::move(sym)) {}

bool Lda::execute(AssemblyLangInterpreter& a) {
    // Convert the symbol to its corresponding address
    int loc = a.convert(symbol);

    // Check if the address is within the data memory range
    if (loc >= 128 && loc < 256) {
        // Load the value from the specified address into the accumulator
        a.accumulator = a.dataVect[loc - 128];
    }

    // Increment the program counter
    return 1;
}

string Lda::to_string() const {
    return "LDA " + symbol;
}

// Implementation of the LDI instruction
Ldi::Ldi(int val) : value(val) {}

bool Ldi::execute(AssemblyLangInterpreter& a) {
    // Load the immediate value into the accumulator
    a.accumulator = value;

    // Increment the program counter
    return 1;
}

string Ldi::to_string() const {
    return "LDI " + std::to_string(value);
}

// Implementation of the STR instruction
Str::Str(string sym) : symbol(std::move(sym)) {}

bool Str::execute(AssemblyLangInterpreter& a) {
    // Convert the symbol to its corresponding address
    int loc = a.convert(symbol);

    // Check if the address is within the data memory range
    if (loc >= 128 && loc < 256) {
        // Store the value from the accumulator into the specified address
        a.dataVect[loc - 128] = a.accumulator;
    }

    // Increment the program counter
    return 1;
}

string Str::to_string() const {
    return "STR " + symbol;
}

// Implementation of the XCH instruction
Xch::Xch() : Instruction() {}

bool Xch::execute(AssemblyLangInterpreter& a) {
    // Swap the values of the accumulator and data register
    int temp = a.accumulator;
    a.accumulator = a.dataRegister;
    a.dataRegister = temp;

    // Increment the program counter
    return 1;
}

string Xch::to_string() const {
    return "XCH";
}

// Implementation of the JMP instruction
Jmp::Jmp(int addr) : address(addr) {}

bool Jmp::execute(AssemblyLangInterpreter& a) {
    // Set the program counter to the specified address
    a.programCounter = address;

    // Do not increment the program counter
    return 0;
}

string Jmp::to_string() const {
    return "JMP " + std::to_string(address);
}

// Implementation of the JZS instruction
Jzs::Jzs(int addr) : address(addr) {}

bool Jzs::execute(AssemblyLangInterpreter& a) {
    // Check if the zero bit is set
    if (a.zeroBit) {
        // Set the program counter to the specified address
        a.programCounter = address;

        // Do not increment the program counter
        return 0;
    }

    // Increment the program counter
    return 1;
}

string Jzs::to_string() const {
    return "JZS " + std::to_string(address);
}

// Implementation of the JVS instruction
Jvs::Jvs(int addr) : address(addr) {}

bool Jvs::execute(AssemblyLangInterpreter& a) {
    // Check if the overflow bit is set
    if (a.overflowBit) {
        // Set the program counter to the specified address
        a.programCounter = address;

        // Do not increment the program counter
        return 0;
    }

    // Increment the program counter
    return 1;
}

string Jvs::to_string() const {
    return "JVS " + std::to_string(address);
}

// Implementation of the ADD instruction
Add::Add() : Instruction() {}

bool Add::execute(AssemblyLangInterpreter& a) {
    // Calculate the sum of the accumulator and data register
    int sum = a.accumulator + a.dataRegister;

    // Check for overflow
    bool overflow = sum > 2147483647 || sum < -2147483647 - 1;

    // Update the overflow bit
    a.overflowBit = overflow;

    // Store the sum in the accumulator
    a.accumulator = sum;

    // Update the zero bit
    a.zeroBit = (a.accumulator == 0);

    // Increment the program counter
    return 1;
}

string Add::to_string() const {
    return "ADD";
}

// Implementation of the SUB instruction
Sub::Sub() : Instruction() {}

bool Sub::execute(AssemblyLangInterpreter& a) {
    // Calculate the difference between the accumulator and data register
    int difference = a.accumulator - a.dataRegister;

    // Check for overflow
    bool overflow = difference > 2147483647 || difference < -2147483647 - 1;

    // Update the overflow bit
    a.overflowBit = overflow;

    // Store the difference in the accumulator
    a.accumulator = difference;

    // Update the zero bit
    a.zeroBit = (a.accumulator == 0);

    // Increment the program counter
    return 1;
}

string Sub::to_string() const {
    return "SUB";
}

// Implementation of the HLT instruction
Hlt::Hlt() : Instruction() {}

bool Hlt::execute(AssemblyLangInterpreter& a) {
    // Set the halt program flag to true
    a.haltProgram = 1;

    // Do not increment the program counter
    return 0;
}

string Hlt::to_string() const {
    return "HLT";
}