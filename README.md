# Symbol Table with Nested Scopes

## Description
This project implements a symbol table for a compiler to handle nested scopes using a hash table data structure. The symbol table records variable names used in the source program along with their attributes. It supports nested scopes by maintaining a separate symbol table for each scope and linking it with the surrounding scope. The implementation provides functionality to insert and lookup variables in the current scope hash table. If a variable entry does not exist in the current scope hash table, it looks up the value in the surrounding scope.

## Functionality
- **Initialize Scope (begin):** Increments the current level and creates a new symbol table for that level. It links the new table to the previous level's table and updates the current level pointer used by lookup and insert functions.
- **Insert Variable (assign):** Inserts the value of a variable in the current scope with a specified value.
- **Lookup Variable (print):** Looks up the value of a variable in the current scope. If it does not exist in the current scope, it looks it up in the surrounding scope.
- **Finalize Scope (end):** Changes the current level pointer so that it points to the table for the scope surrounding the current level.

## Implementation Details
- Implementation Language is C++
- Implemented using a hash table data structure.
- This symbol table supports specific code which is provided as the sample code
- The Implementation of currscope and enclosing scopes is maintained using a Singly Linked List of Hashtable which are built specially
