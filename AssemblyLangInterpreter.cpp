#include "AssemblyLangInterpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Instruction.h"
#include <string>
#include <vector>

using namespace std;

static int count = 0;

// Constructor: Initialize memory and registers
AssemblyLangInterpreter::AssemblyLangInterpreter() : instruVect(128, nullptr), dataVect(128, 0),
                                                     accumulator(0), dataRegister(0), programCounter(0), zeroBit(0), overflowBit(0), haltProgram(0) {}

// Destructor: Clean up dynamically allocated Instruction objects
AssemblyLangInterpreter::~AssemblyLangInterpreter() {
    for (Instruction* instr : instruVect) {
        delete instr;
    }
}

// Command loop for user interaction
void AssemblyLangInterpreter::commandLoop() {
    AssemblyLangInterpreter a;

    cout << "Enter filename: ";
    string filename;
    getline(cin, filename);
    a.loading(filename);

    while (true) {
        string command;
        cout << "Enter command (s, a, or q): ";
        getline(cin, command);

        if (command == "s") { // execute single instruction
            a.executeOnce(true);
        }
        else if (command == "a") { // execute all instructions
            a.executeAll();
            a.print();
            if (count == 1000){
                cout<< "\n1000 instructions reached! Terminating ..." << endl;
            }
        }
        else if (command == "q") { // quit
            cout << "Good Bye\n";
            break;
        }
        else {
            cout << "Invalid command.\n";
        }
        if(a.haltProgram){
            break;
        }
    }
}

// Print the current state of the interpreter
void AssemblyLangInterpreter::print() {
    printInstructionMemory();
    printRegisters();
    printDataMemory();
}

// Print the registers
void AssemblyLangInterpreter::printRegisters() const {
    cout << "------- REGISTERS -------" << endl;
    cout << "Accumulator    : " << accumulator << endl;
    cout << "Data Register  : " << dataRegister << endl;
    cout << "Program Counter: " << programCounter << endl;
    cout << "Zero Bit       : " << (zeroBit ? "1" : "0") << endl;
    cout << "Overflow Bit   : " << (overflowBit ? "1" : "0") << endl;
}

// Print the instruction memory
void AssemblyLangInterpreter::printInstructionMemory() {
    cout << "------- Instruction Memory -------" << endl;
    for (int i = 0; i < 128; ++i) {
        if (instruVect[i]) {
            cout << i << ": " << instruVect[i]->to_string() << endl;
        }
    }
}

// Print the data memory
void AssemblyLangInterpreter::printDataMemory() {
    cout << "------- Data Memory -------" << endl;
    for (int i = 0; i < dataVect.size(); ++i) {
        string symbol = addressSymbol(128 + i);
        if (!symbol.empty() || dataVect[i] != 0) {
            cout << 128 + i << " " << (symbol.empty() ? "": symbol + ": ") << dataVect[i] << endl;
        }
    }
}

// Get the symbol associated with a given address
string AssemblyLangInterpreter::addressSymbol(int address) {
    for (const auto& pair : symbolTable) {
        if (pair.second == address) {
            return pair.first;
        }
    }
    return "";
}

// Convert a symbol to its corresponding address
int AssemblyLangInterpreter::convert(const string& symbol) {
    auto iterator = symbolTable.find(symbol);
    if (iterator == symbolTable.end()) {
        // If the symbol is not found in the symbol table
        int address = symbolTable.size() + 128; // Calculate a new address
        symbolTable[symbol] = address; // Add the symbol and address to the symbol table
        return address;
    }
    return iterator->second; // Return the address associated with the symbol
}

// Load instructions from a file
void AssemblyLangInterpreter::loading(const string& fileName) {
    ifstream file(fileName);
    string line;
    int lineNum = 0;

    while (getline(file, line) && lineNum < 128) {
        istringstream stream(line);
        string name;
        vector<string> vect;
        string values;

        stream >> name; // Read the instruction name
        while (stream >> values) {
            vect.push_back(values); // Read the operands
        }

        Instruction* instruction = makeInstru(name, vect); // Create an Instruction object based on the name and operands
        if (instruction && lineNum < instruVect.size()) {
            instruVect[lineNum] = instruction; // Store the instruction in the instruction vector
            lineNum++;
        }
    }
    file.close();
}

// Create an Instruction object based on the instruction name and operands
Instruction* AssemblyLangInterpreter::makeInstru(const string& name, const vector<string>& vect) {
    if (name == "DEC" ) {
        return new Dec(vect[0]);
    }
    else if (name == "LDI" ) {
        int value = stoi(vect[0]);
        return new Ldi(value);
    }
    else if (name == "STR") {
        return new Str(vect[0]);
    }
    else if (name == "XCH") {
        return new Xch();
    }
    else if (name == "ADD" ) {
        return new Add();
    }
    else if (name == "SUB" ) {
        return new Sub();
    }
    else if (name == "JZS") {
        int address = stoi(vect[0]);
        return new Jzs(address);
    }
    else if (name == "JMP") {
        int address = stoi(vect[0]);
        return new Jmp(address);
    }
    else if (name == "JVS" ) {
        int address = stoi(vect[0]);
        return new Jvs(address);
    }
    else if (name == "LDA") {
        return new Lda(vect[0]);
    }
    else if (name == "HLT") {
        return new Hlt();
    }
    return nullptr;
}

// Execute all instructions until the program halts
void AssemblyLangInterpreter::executeAll() {
    while (!haltProgram && programCounter < 256) {
        executeOnce(false);
    }
}

// Execute a given instruction
bool AssemblyLangInterpreter::execute(Instruction* instruction) {
    if (instruction != nullptr) {
        return instruction->execute(*this);
    } else {
        return true;
    }
}

// Execute a single instruction
void AssemblyLangInterpreter::executeOnce(bool printOrNo) {
    count++;
    if (count == 1000){
        haltProgram = 1;
    }
    if (haltProgram || programCounter >= instruVect.size()) {
        return;
    }

    Instruction* curr = instruVect[programCounter];
    if (curr != nullptr) {
        bool incrementOrNot = execute(curr);
        if (incrementOrNot) { // Sees of an instruction returns true or false and according to that it may or may not increment pc
            programCounter++;
        }
    }

    if (printOrNo) {
        print();
    }
}