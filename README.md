
# cRegex

cRegex is a traditional regular expression library written in C. Internally it uses a recursive descent parser to create an AST which is then transformed into a Non Deterministic Automata (NFA). Then the given input string is checked for acceptance on the NFA.

## Features

### Current:
- Full string matching
- Start of string matching
- Concatenation, Union, Kleene Star
- Grouping
- Ranges
- Wildcard

### Work in progress:
- Group string capturing
- Quantifiers (?, +, {})

## Usage (Linux)

1. Run `Make` with the provided makefile
2. Use the header file: `/include/cRegex.h`  with the compiled static library file: `/build/cRegex.a`


## Example

Simple example where the `quickFullMatch()` function is used to filter email addresses and phone numbers from a list of strings.
```c
char  strings[10][100] = {
"johnappleseed@email.org",
"adam@adam.org",
"123432432534.3443",
"!!!;';'@email.com",
"(111)-222-3333",
"111-222-3333",
"abcdefg",
"(111)-222-900",
"111-222-abcd",
"helloworld@.com"
};

char  emailRegex[73] =  "[A-Za-z0-9][A-Za-z0-9]*@[A-Za-z0-9][A-Za-z0-9]*\\.[A-Za-z0-9][A-Za-z0-9]*";
char  phoneRegex[75] =  "(\\([0-9][0-9][0-9]\\)|[0-9][0-9][0-9])-[0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]";

for(int  i  =  0; i<10;i++){
	if(quickFullMatch(emailRegex, strings[i]) ==  1){
		printf(" Email: %s  \n\n",strings[i]);
	}else  if(quickFullMatch(phoneRegex, strings[i]) ==  1){
		printf(" Phone: %s  \n\n",strings[i]);
	}else{
	printf("Invalid: %s  \n\n",strings[i]);
	}
}
```

#### output:

```
  Email: johnappleseed@email.org

  Email: adam@adam.org

Invalid: 123432432534.3443

Invalid: !!!;';'@email.com

  Phone: (111)-222-3333

  Phone: 111-222-3333

Invalid: abcdefg

Invalid: (111)-222-900

Invalid: 111-222-abcd

Invalid: helloworld@.com
```

