# JFI2020 MIPS Compiler
A simple compiler that compiles C-Like Code into MIPS Assembly. It started as a 2-Day project in a group of three after an introductory talk on compiler theory by Philip Lukert at Jugendforum Informatik 2020.

## Features
 - Int Datatype
 - Variable declarations
 - Addition, Subtraction, Multiplication and Division
 - Boolean Expressions ( &&, ||, <, >, <=, >=, ==, != )
 - While block
 - If block
 - Syscalls

## Technical details
### Grammar
The grammar is defined in the Backus-Naur-Form.

#### Statements
```
s ::= int x; s
    | x = e; s
    | if (b) { s } s
    | while (b) { s } s
    | print(e);¹ s
    | ε
```

#### Expressions
```
e ::= e2 [+ e]
e2 ::= e3 [* e2]
e3 ::= -e3 | e4
e4 ::= n | x | (e) | read()²
```
```
n ∈ ℕ
x ∈ Var
```

#### Boolean Expression
```
b ::= b2 [|| b]
b2 ::= b3 [&& b2]
b3 ::= !b3 | b4
b4 ::= e < > == != <= >= e | (b) | true | false
```
Notes:
1: print(e) is a statement syscall, it doesn't return a value so it cannot be treated as an expression.
2: read() is an expression syscall, it returns a value.

### AST
The AST is defined in ast.h and consists of a base class Node and multiple classes for each Node type (Variables, Expressions, Syscalls, etc.) that inherit from the base class Node.

Statements have their own base class Statement, which inherits from Node. For example the Assignment statement inherits from Statement, which itself inherits from Node.

Each class overrides two virtual methods generateSubTree and generateCode which are used to create the AST or generate the respective Assembly.

Furthermore each class saves pointers to needed expressions or states. For example the Assignment statement saves pointers to its variable, its expression and the next statement.

### Compile process
The compile process is divided into three steps: the lexer, the parser and the generator

#### lexer
The lexer converts the source file into an array that the parser can understand. It removes all whitespace and tokenizes the syntax-elements into 5 groups:
- Keyword: Datatypes such as `int` and control flow statements such as `if` and `while`
- Identifier: Variable names
- Constant: Hard-coded values in the source code, such as 12
- Special Symbols: Arithmetic symbols such as + or / and syntax-elements such as = or {
- Boolean Operators: The typical boolean operators known from other languages such as ==, && and >=

#### Parser
The parser uses the tokenization of the input to create an AST.

First the method getNodeInstanceFromToken returns a pointer to the respective class of the first token in the tokenization list.

Afterwards the generateSubTree method is called for this instance which in turn generates instances for its children and calls generateSubTree recursively for each child. 

For the next statement getNodeInstanceFromToken is called at the current index and the cycle repeats.
After the initial call to generateSubTree for the root node returns, it contais the entire AST for the input file and can be passed to the generateCode function.

#### Generator
The generator recursively goes through the AST and generates the Assembly code in one big string.
For each statement the code for parameters is generated first so that their value can be pushed onto the stack. After that the code for the statement itself will be generated and finally the code for the next statement will be generated.

#### Main function
The main function first reads in the input file and passes its content to the lexer.
Afterwards the tokenization is passed to the parser and the pointer to the root node to the generator. Finally the generated string is written to the output file.
