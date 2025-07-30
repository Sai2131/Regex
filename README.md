# cRegex

cRegex is a traditional regular expression library written in C. Internally it uses a recursive descent parser to create an AST which is then transformed into a Non Deterministic Automata (NFA). Then the given input string is checked for acceptance on the NFA.

