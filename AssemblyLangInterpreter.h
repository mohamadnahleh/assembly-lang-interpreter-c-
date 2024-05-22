#ifndef CS474_PROJECT4_ASSEMBLYLANGINTERPRETER_H
#define CS474_PROJECT4_ASSEMBLYLANGINTERPRETER_H

#include <vector>
#include <unordered_map>
#include <string>
#include "Instruction.h"

using namespace std;

// Forward declaration of the Instruction class
class Instruction;

// The AssemblyLangInterpreter class is responsible for interpreting and executing assembly language instructions
class AssemblyLangInterpreter {
public:
    AssemblyLangInterpreter();
    ~AssemblyLangInterpreter();

    // Convert a symbol to its corresponding address
    int convert(const string& symbol);
    // Load instructions from a file
    void loading(const string& fileName);
    // Create an Instruction object based on the instruction name and operands
    static Instruction* makeInstru(const string& name, const vector<string>& vect);
    // Print the current state of the interpreter
    void print();
    // Print the instruction memory
    void printInstructionMemory();
    // Print the data memory
    void printDataMemory();
    // Print the registers
    void printRegisters() const;
    // Execute all instructions until the program halts
    void executeAll();
    // Execute a single instruction
    void executeOnce(bool printOrNo = true);
    // Execute a given instruction
    bool execute(Instruction* instruction);
    // Get the symbol associated with a given address
    string addressSymbol(int address);
    // Start the command loop for user interaction
    static void commandLoop();

    // Registers and flags
    int accumulator;
    int dataRegister;
    int programCounter;
    bool zeroBit;
    bool overflowBit;
    // Symbol table for storing labels and their addresses
    unordered_map<string, int> symbolTable;
    // Flag to indicate if the program should halt
    bool haltProgram;

    // Instruction memory and data memory
    vector<Instruction*> instruVect;
    vector<int> dataVect;
    // Map for storing addresses and their associated symbols
    unordered_map<int, string> address_to_symbol;
};

#endif //CS474_PROJECT4_ASSEMBLYLANGINTERPRETER_H