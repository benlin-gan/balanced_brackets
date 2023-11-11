#include <string>
#include <algorithm>
#include <stack>
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
				std::cout << q << '\n';
				max_size = std::max( (unsigned) q.size(), max_size);		
			}
		}	
	}	
	return max_size;
}
int main(){
	std::cout << brute_force("()[()()](])([]]]");
}
