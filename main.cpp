#include <vector>
#include <string>
#include <iostream>

// Log is a preprocessor directive that prints out the current stack.
#define LOG(v) \
std::cout << "Current stack: "; \
for (auto& x : v) std::cout << x << " "; \
std::cout << std::endl;

/*

Define Predicitve Parsing Table.

Column 1: 'a' | Column 2: '+' | Column 3: '-' | Column 4: '*' | 
Column 5: '/' | Column 6: '(' | Column 7 = ')' | Column 8 = '$'

Row 1: 'E' | Row 2: 'Q' | Row 3: 'T' | Row 4: 'R' | Row 5: 'F'

*/
class ParsingTable {
public:
std::vector<std::vector<int> > parse_table{ 6, std::vector<int>(9,0) };
ParsingTable() {
	for (int i = 0; i < parse_table.size(); ++i) {
		parse_table[i][0] = 0;
	}
	for (int i = 0; i < parse_table[0].size(); ++i) {
		parse_table[0][i] = 0;
	}
	parse_table[1][1] = 11; // 11 = TQ
	parse_table[1][6] = 16; // 16 = TQ
	parse_table[2][2] = 22; // 22 = +TQ
	parse_table[2][3] = 23; // 23 = -TQ
	parse_table[2][7] = 27; // 27 = lambda
	parse_table[2][8] = 28; // 28 = lambda
	parse_table[3][1] = 31; // 31 = FR
	parse_table[3][6] = 36; // 36 = FR
	parse_table[4][2] = 42; // 42 = lambda
	parse_table[4][3] = 43; // 43 = lambda
	parse_table[4][4] = 44; // 44 = *FR
	parse_table[4][5] = 45; // 45 = /FR
	parse_table[4][7] = 47; // 47 = lambda
	parse_table[4][8] = 48; // 48 = lambda
	parse_table[5][1] = 51; // 51 = 'a'
	parse_table[5][6] = 56; // 56 = (E)
}

// Given the row and column, return the state.
int Get(int row, int col) {
	return parse_table[row][col];
}
};

// Given a char which represents a state, return the row # of the state.
int ConvertToRow(char c) {
switch (c)
{
case 'E':
	return 1;
case 'Q':
	return 2;
case 'T':
	return 3;
case 'R':
	return 4;
case 'F':
	return 5;
default:
	return 0;
	break;
}
}

// Given a char which represents an input, return the column # of the state.
int ConvertToCol(char c) {
switch (c)
{
case 'a':
	return 1;
case '+':
	return 2;
case '-':
	return 3;
case '*':
	return 4;
case '/':
	return 5;
case '(':
	return 6;
case ')':
	return 7;
case '$':
	return 8;
default:
	return 0;
	break;
}
}


// Using a vector to represent stack because it is much easier to print out the current elements.
// Given the stack and an integer that represents a state(s) in the parsing table, push the corresponding state(s) onto the stack.
bool push_backToStack(std::vector<char>& st, int x) {
switch (x)
{
case 0:
	return false;
case 11:
case 16:
	std::cout << "Pushing TQ onto the stack." << std::endl;
	st.push_back('Q');
	st.push_back('T');
	LOG(st);
	return true;
	break;
case 22:
	std::cout << "Pushing +TQ onto the stack." << std::endl;
	st.push_back('Q');
	st.push_back('T');
	st.push_back('+');
	LOG(st);
	return true;
	break;
case 23:
	std::cout << "Pushing -TQ onto the stack." << std::endl;
	st.push_back('Q');
	st.push_back('T');
	st.push_back('-');
	LOG(st);
	return true;
	break;
case 27:
case 28:
case 42:
case 43:
case 47:
case 48:
	std::cout << "Pushing ^ (Lambda) onto the stack." << std::endl;
	st.push_back('^');	// ^ == lambda
	LOG(st);
	return true;
	break;
case 31:
case 36:
	std::cout << "Pushing FR onto the stack." << std::endl;
	st.push_back('R');
	st.push_back('F');
	LOG(st);
	return true;
	break;
case 44:
	std::cout << "Pushing *FR onto the stack." << std::endl;
	st.push_back('R');
	st.push_back('F');
	st.push_back('*');
	LOG(st);
	return true;
	break;
case 45:
	std::cout << "Pushing /FR onto the stack." << std::endl;
	st.push_back('R');
	st.push_back('F');
	st.push_back('/');
	LOG(st);
	return true;
	break;
case 51:
	std::cout << "Pushing 'a' onto the stack." << std::endl;
	st.push_back('a');
	LOG(st);
	return true;
	break;
case 56:
	std::cout << "Pushing (E) onto the stack." << std::endl;
	st.push_back(')');
	st.push_back('E');
	st.push_back('(');
	LOG(st);
	return true;
	break;
default:
	return false;
	break;
}
}

int main() {

// Instantiate the parsing table object.
ParsingTable parse_table;

// String variable to capture user input.
std::string input_string;

// Char variable to hold the current state.
char state;

// Bool variable to keep track of whether the input is still valid.
bool accepted = true;

// Vector that is used as a stack.
std::vector<char> st;

// Stack will have $E as it's initial elements.
st.push_back('$');
st.push_back('E');


// Ask for user input.
std::cout << "Enter string" << std::endl;
std::cin >> input_string;

// Log is a preprocessor directive that prints out the current stack.
LOG(st);
do {
	// Set state equal to the top of the stack.
	state = st.back();
		
	// Set input equal to the next symbol of the string.
	char input = input_string[0];

	// If state is Lambda, simply pop lambda from the stack.
	if (state == '^') 
	{
		std::cout << "Popping ^ (Lambda) from the stack." << std::endl;
		st.pop_back();
		LOG(st);
	} 

	// If state is a terminal or $ and it is equal to input, pop the stack and read the string.
	// If state does not equal input, then we know that input string must be rejected.
	else if (state == '(' || state == ')' || state == '$' || state == 'a' || 
		state == '+' || state == '-' || state == '*' || state == '/') 
	{
		if (state == input) {
			std::cout << "Popping from stack: " << st.back() << std::endl;
			st.pop_back();
			LOG(st);
			input_string.erase(0, 1);
			std::cout << "Input: " << input_string << std::endl;
		}
		else {
			std::cout << "Rejected." << std::endl;
			accepted = false;
			break;
		}
	}

	// If state is non-terminal, then retrieve the states from the parsing table.
	// Then, pop the state off of the stack and push the new states onto the stack.
	// If there are no new states retrieved from the parsing table, then the input is rejected.
	else if (state == 'E' || state == 'T' || state == 'Q' || state == 'F' || state == 'R') 
	{
		int row = ConvertToRow(state);
		int col = ConvertToCol(input);
		if (parse_table.Get(row,col) != 0 || (!(row == 5 && col == 1))) {
			std::cout << "Popping from stack: " << st.back() << std::endl;
			st.pop_back();
			LOG(st);
			if (!(push_backToStack(st, parse_table.Get(row, col)))) {
				accepted = false;
				break;
			}
		}
		else {
			std::cout << "Rejected." << std::endl;
			accepted = false;
			break;
		}
	}

} while (state != '$');	// Repeat until we reach $

if (accepted) 
	std::cout << "Accepted.";
else 
	std::cout << "Rejected.";

std::cin.ignore();
std::cin.get();

return 0;
}