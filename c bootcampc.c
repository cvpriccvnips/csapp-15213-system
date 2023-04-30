#C review
int foo(unsigned int u){
	return (u>-1)?1:0
}
-1 is cast to an unsigned int in the comparison, so the comparison that is happening is actualy u>int_max, This always return 0.

...

#C boot camp
Agenda
`C basics
`C libraries
`debugging tools
`version control
`compilation
`demo

##C basics
`summary:
1.Pointers/Arrays/Structs/Casting
2.Memory Management
3.Function pointers/Generic Types
4.Strings 
5.GrabBag(Macros,typedefs,header guards/file,etc)

##Pointers
`store address of a value in Memory
1.eg int*,char*,int** etc
2.access the value by dereferencing (*a),can be used to read value or write value to given address
3.dereferencing NULL causes a runtime error

`pointer to type a references a block of sizeof(a) bytes
`get the address of a value in memory with the & operator