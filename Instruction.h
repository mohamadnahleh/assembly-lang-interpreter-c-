#ifndef CS474_PROJECT4_INSTRUCTION_H
#define CS474_PROJECT4_INSTRUCTION_H

#include <string>
#include <vector>

using namespace std;

// Forward declaration of the AssemblyLangInterpreter class
class AssemblyLangInterpreter;

// Base class for all instructions
class Instruction {
public:
    // Pure virtual function to execute the instruction
    virtual bool execute(AssemblyLangInterpreter& a) = 0;
    // Pure virtual function to get the string representation of the instruction
    virtual string to_string() const = 0;
};

// Derived class for the DEC instruction
class Dec : public Instruction {
public:
    explicit Dec(string symbol);
    bool execute(AssemblyLangInterpreter& a) override;
    string to_string() const override;

private:
    string symbol;
};

// Derived class for the LDA instruction
class Lda : public Instruction {
public:
    explicit Lda(string sym);
    bool execute(AssemblyLangInterpreter& a) override;
    string to_string() const override;

private:
    string symbol;
};

// Derived class for the LDI instruction
class Ldi : public Instruction {
public:
    explicit Ldi(int val);
    bool execute(AssemblyLangInterpreter& a) override;
    string to_string() const override;

private:
    int value;
};

// Derived class for the STR instruction
class Str : public Instruction {
public:
    explicit Str(string sym);
    bool execute(AssemblyLangInterpreter& a) override;
    string to_string() const override;

private:
    string symbol;
};

// Derived class for the XCH instruction
class Xch : public Instruction {
public:
    Xch();
    bool execute(AssemblyLangInterpreter& a) override;
    string to_string() const override;
};

// Derived class for the JMP instruction
class Jmp : public Instruction {
public:
    explicit Jmp(int addr);
    bool execute(AssemblyLangInterpreter& a) override;
    string to_string() const override;

private:
    int address;
};

// Derived class for the JZS instruction
class Jzs : public Instruction {
public:
    explicit Jzs(int addr);
    bool execute(AssemblyLangInterpreter& a) override;
    string to_string() const override;

private:
    int address;
};

// Derived class for the JVS instruction
class Jvs : public Instruction {
public:
    explicit Jvs(int addr);
    bool execute(AssemblyLangInterpreter& a) override;
    string to_string() const override;

private:
    int address;
};

// Derived class for the ADD instruction
class Add : public Instruction {
public:
    Add();
    bool execute(AssemblyLangInterpreter& a) override;
    string to_string() const override;
};

// Derived class for the SUB instruction
class Sub : public Instruction {
public:
    Sub();
    bool execute(AssemblyLangInterpreter& a) override;
    string to_string() const override;
};

// Derived class for the HLT instruction
class Hlt : public Instruction {
public:
    Hlt();
    bool execute(AssemblyLangInterpreter& a) override;
    string to_string() const override;
};

#endif //CS474_PROJECT4_INSTRUCTION_H