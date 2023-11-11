#include <string>
#include <algorithm>
#include <stack>
#include <vector>
#include <iostream>
bool is_balanced(std::string s){
	std::stack<char> st;
	for(char c: s){
		if(c == '(' || c== '['){
			st.push(c);
		}else if(c == ')'){
			if(!st.empty() && st.top() == '('){
				st.pop();
			}else{
				return false;
			}
		}else if(c == ']'){
			if(!st.empty() && st.top() == '['){
				st.pop();
			}else{
				return false;
			}
		}
	}
	return st.empty();
}
unsigned brute_force(std::string s){
	unsigned max_size = 0;
	for(int i = 0; i < s.size(); i++){
		for(int j = 0; j <= s.size() - i; j++){
			std::string q = s.substr(i, j);	
			if(is_balanced(q)){
				max_size = std::max( (unsigned) q.size(), max_size);		
			}
		}	
	}	
	return max_size;
}
unsigned scan_left(std::string& s, unsigned index){
	std::stack<char> st;
	for(int start = index; start >= 0; start--){
		char c = s[start];
		if(c == ')' || c == ']'){
			st.push(c);
		}else if(c == '('){
			if(!st.empty() && st.top() == ')'){
				st.pop();
			}else{
				return index - start - st.size(); 
			}
		}else if(c == '['){
			if(!st.empty() && st.top() == ']'){
				st.pop();
			}else{
				return index - start - st.size();
			}
		}
	}
	return index + 1 - st.size(); 
} 
unsigned scan_left(std::string s){
	unsigned max_size = 0;
	for(unsigned i = 0; i < s.size(); i++){
		max_size = std::max(scan_left(s, i), max_size); 
	}
	return max_size;
}
unsigned basic_recursion(std::string& s, unsigned index){
	if(index == 0) return 0;
	if(index == 1){
		if(s[0] == '(' && s[1] == ')') return 2;
		if(s[0] == '[' && s[1] == ']') return 2;
		return 0;
	}
	if(s[index] == '(' || s[index] == '[') return 0;
	if(s[index] == ']'){
		if(s[index - 1] == '[') return basic_recursion(s, index - 2) + 2;
		if(s[index - 1] != '('){
			unsigned prev_length = basic_recursion(s, index - 1);			
			char toMatch = s[index - prev_length - 1];
			if(toMatch == '['){
				return basic_recursion(s, index - prev_length - 2) + prev_length + 2;
			}
		}
		return 0;
	}
	if(s[index] == ')'){
		if(s[index - 1] == '(') return basic_recursion(s, index - 2) + 2;
		if(s[index - 1] != '['){
			unsigned prev_length = basic_recursion(s, index - 1);			
			char toMatch = s[index - prev_length - 1];
			if(toMatch == '('){
				return basic_recursion(s, index - prev_length - 2) + prev_length + 2;
			}
		
		}
		return 0;
	}	
	return 0;
}
unsigned basic_recursion(std::string s){
	unsigned max_size = 0;
	for(unsigned i = 0; i < s.size(); i++){
		max_size = std::max(basic_recursion(s, i), max_size); 
	}
	return max_size;
}
void dynamic_programming(std::string &s, std::vector<unsigned>& max_lengths){
	max_lengths[0] = 0;
	max_lengths[1] = 0;
	if(s[0] == '(' && s[1] == ')') max_lengths[1] = 2;
	if(s[0] == '[' && s[1] == ']') max_lengths[1] = 2;
	for(unsigned i = 2; i < max_lengths.size(); i++){
		if(s[i] == '(' || s[i] == '['){
		   	max_lengths[i] = 0;
			continue;
		}
		
		if(s[i] == ']'){
			if(s[i - 1] == '['){
			   	max_lengths[i] = max_lengths[i - 2] + 2;
				continue;
			}
			if(s[i - 1] != '('){
				unsigned prev_length = max_lengths[i - 1];
				char toMatch = s[i - prev_length - 1];  
				if(toMatch == '['){
					max_lengths[i] = max_lengths[i - prev_length - 2] + prev_length + 2; 
					continue;
				}
			}
		}
		if(s[i] == ')'){
			if(s[i - 1] == '('){
			   	max_lengths[i] = max_lengths[i - 2] + 2;
				continue;
			}
			if(s[i - 1] != '['){
				unsigned prev_length = max_lengths[i - 1];
				char toMatch = s[i - prev_length - 1];  
				if(toMatch == '('){
					max_lengths[i] = max_lengths[i - prev_length - 2] + prev_length + 2; 
					continue;
				}
			}
		}
		max_lengths[i] = 0;
	}	
}
unsigned dynamic_programming(std::string s){
	std::vector<unsigned> max_lengths(s.size(), 0); 
	dynamic_programming(s, max_lengths);
	unsigned max_size = 0;
	for(unsigned length : max_lengths){
		max_size = std::max(length, max_size);
	}
	return max_size;
}
int main(){
	std::string s = "[][][][][][][(()(]()[()()](])([]()()()()()(]]";
	std::cout << brute_force(s) << '\n';
	std::cout << scan_left(s) << '\n';
	std::cout << basic_recursion(s) << '\n';
	std::cout << dynamic_programming(s) << '\n';
}
