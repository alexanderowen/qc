# Quack language compiler  
Compiler for the Quack language, which is an imperative, object-oriented language which features inheritance, type inference, static scope, method overriding, dynamic dispatch, and short-circuit evaluation.  
## Build and Execution  
Build the compiler with `make` which generates an executable called `qc`. This is the Quack compiler   
Compile your Quack code with `./qc filename`  
This generates an executable called `pgm`, which you can execute with `./pgm`  
## Compiler functionality  
- Discovers the variable type by using type inference  
- Variable types are flow-insensitive, using least common ancestor to determine 
type in the case of conflicting type inferences  
- Allows user to create their own classes, featuring operator overloading and
inheritance  
- Features dynamic dispatch on method calls when static type does not match
dynamic type  
- Features a stack frame that allows for recursive method calls  
- Features short circuit evaluation for boolean opeartors 'and' and 'or'  
- Type checks for the following  
  - Variable usage is preceded by delcaration on ALL execution paths  
  - Operator method calls are allowed for the variable's type  
  - Method returns the type or a subtype of the type specified in the signature
  - Method calls have the correct number of arguments
  - Method calls arguments are either the same type or subtypes of types specified
in the method delcaration  
  - If/While conditions are of type Boolean  
  - Method overriding uses the correct number of arguments
  - Method overriding uses arguments that are the same type or supertype of the overrriden
method  
  - Method overriding returns a type that is the same type or a subtype of the 
overriden method  
  - Instance variables used within classes are defined

## Other Notes 
- When compiling Quack code, the C compiler may emit "Incompatible pointer" warnings  
- As a consequence of the Flex lexical tool, qc is not leak-free. However, this memory can be considered 'supressed' as it is a known source of leakage  
