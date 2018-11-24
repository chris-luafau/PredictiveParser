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

NOTE: @ will be used to represent 'a=' for more efficient implementation.
	  It will produce the exame same results as 'a='.

Column 1: '@(a=)' | Column 2: 'a' | Column 3: 'b' | Column 4: '+' | Column 5: '-' |
Column 6: '*' | Column 7: '/' | Column 8 = '(' | Column 9 = ')' | Column 10 = '$' |

Row 1: 'S' | Row 2: 'E' | Row 3: 'Q' | Row 4: 'T' | Row 5: 'R' | Row 6: 'F' |

*/
class ParsingTable {
public:
	std::vector<std::vector<int> > parse_table{ 7, std::vector<int>(11,0) };
	ParsingTable() {
		for (int i = 0; i < parse_table.size(); ++i) {
			parse_table[i][0] = 0;
		}
		for (int i = 0; i < parse_table[0].size(); ++i) {
			parse_table[0][i] = 0;
		}
		parse_table[1][1] = 11; // 11 = a=E
		parse_table[2][2] = 22; // 22 = TQ
		parse_table[2][3] = 23; // 23 = TQ
		parse_table[2][8] = 28; // 28 = TQ
		parse_table[3][4] = 34; // 34 = +TQ
		parse_table[3][5] = 35; // 35 = -TQ
		parse_table[3][9] = 39; // 39 = lambda
		parse_table[3][10] = 310; // 310 = lambda
		parse_table[4][2] = 42; // 42 = FR
		parse_table[4][3] = 43; // 43 = FR
		parse_table[4][8] = 48; // 48 = FR
		parse_table[5][4] = 54; // 54 = lambda
		parse_table[5][5] = 55; // 55 = lambda
		parse_table[5][6] = 56; // 56 = *FR
		parse_table[5][7] = 57; // 57 = /FR
		parse_table[5][9] = 59; // 59 = lambda
		parse_table[5][10] = 510; // 510 = lambda
		parse_table[6][2] = 62; // 62 = a
		parse_table[6][3] = 63; // 63 = b
		parse_table[6][8] = 68; // 68 = (E)

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
	case 'S':
		return 1;
	case 'E':
		return 2;
	case 'Q':
		return 3;
	case 'T':
		return 4;
	case 'R':
		return 5;
	case 'F':
		return 6;
	default:
		return 0;
		break;
	}
}

// Given a char which represents an input, return the column # of the state.
int ConvertToCol(char c) {
	switch (c)
	{
	case '@':		// @ -> a=
		return 1;
	case 'a':
		return 2;
	case 'b':
		return 3;
	case '+':
		return 4;
	case '-':
		return 5;
	case '*':
		return 6;
	case '/':
		return 7;
	case '(':
		return 8;
	case ')':
		return 9;
	case '$':
		return 10;
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
		std::cout << "Pushing a=E onto the stack." << std::endl;
		st.push_back('E');
		st.push_back('@');	// @ -> a=
		LOG(st);
		return true;
		break;
	case 22:
	case 23:
	case 28:
		std::cout << "Pushing TQ onto the stack." << std::endl;
		st.push_back('Q');
		st.push_back('T');
		LOG(st);
		return true;
		break;
	case 34:
		std::cout << "Pushing +TQ onto the stack." << std::endl;
		st.push_back('Q');
		st.push_back('T');
		st.push_back('+');
		LOG(st);
		return true;
		break;
	case 35:
		std::cout << "Pushing -TQ onto the stack." << std::endl;
		st.push_back('Q');
		st.push_back('T');
		st.push_back('-');
		LOG(st);
		return true;
		break;
	case 39:
	case 310:
	case 54:
	case 55:
	case 59:
	case 510:
		std::cout << "Pushing ^ (Lambda) onto the stack." << std::endl;
		st.push_back('^');	// ^ -> lambda
		LOG(st);
		return true;
		break;
	case 42:
	case 43:
	case 48:
		std::cout << "Pushing FR onto the stack." << std::endl;
		st.push_back('R');
		st.push_back('F');
		LOG(st);
		return true;
		break;
	case 56:
		std::cout << "Pushing *FR onto the stack." << std::endl;
		st.push_back('R');
		st.push_back('F');
		st.push_back('*');
		LOG(st);
		return true;
		break;
	case 57:
		std::cout << "Pushing /FR onto the stack." << std::endl;
		st.push_back('R');
		st.push_back('F');
		st.push_back('/');
		LOG(st);
		return true;
		break;
	case 62:
		std::cout << "Pushing 'a' onto the stack." << std::endl;
		st.push_back('a');
		LOG(st);
		return true;
		break;
	case 63:
		std::cout << "Pushing b onto the stack." << std::endl;
		st.push_back('b');
		LOG(st);
		return true;
		break;
	case 68:
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
	st.push_back('S');


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

		// Look ahead to the next input symbol.
		// If it is '=', then we know we have 'a='.
		// If so, set input equal to '@'.
		char next = input_string[1];
		if (next == '=') input = '@';

		// If state is Lambda, simply pop lambda from the stack.
		if (state == '^') 
		{
			std::cout << "Popping ^ (Lambda) from the stack." << std::endl;
			st.pop_back();
			LOG(st);
		} 

		// If state is a terminal or $ and it is equal to input, pop the stack and read the string.
		// If state does not equal input, then we know that input string must be rejected.
		else if (state == '(' || state == ')' || state == '$' || state == 'a' || state == '@' ||
			state == 'b' || state == '+' || state == '-' || state == '*' || state == '/') 
		{
			if (state == input) {

				// If state is '@', then we know we have 'a='. 
				// Therefore, we must handle this case differently.
				if (state == '@') {
					std::cout << "Popping from stack: @(a=)" << std::endl;
					st.pop_back();
					LOG(st);

					// Erase twice because we must read 'a' and '=' from the input string.
					input_string.erase(0, 1);	
					input_string.erase(0, 1);

					std::cout << "Input: " << input_string << std::endl;
				}
				else {
					std::cout << "Popping from stack: " << st.back() << std::endl;
					st.pop_back();
					LOG(st);
					input_string.erase(0, 1);
					std::cout << "Input: " << input_string << std::endl;
				}
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
		else if (state == 'S' || state == 'E' || state == 'T' || state == 'Q' || state == 'F' || state == 'R') 
		{
			int row = ConvertToRow(state);
			int col = ConvertToCol(input);
			if (parse_table.Get(row,col) != 0 || (!(row == 6 && col == 2)) || (!(row == 6 && col == 3))) {
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
