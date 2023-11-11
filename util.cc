#include <string>
#include <algorithm>
#include <stack>
#include <vector>
#include <iostream>
#include <random>
#include <cstdlib>
#include <chrono>
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
	unsigned fin = index;
	for(int start = index; start >= 0; start--){
		char c = s[start];
		if(c == ')' || c == ']'){
			st.push(c);
		}else if(c == '('){
			if(!st.empty() && st.top() == ')'){
				st.pop();
				if(st.empty()) fin = start;
			}else{
				return index - fin + 1; 
			}
		}else if(c == '['){
			if(!st.empty() && st.top() == ']'){
				st.pop();
				if(st.empty()) fin = start;
			}else{
				return index - fin + 1;
			}
		}
	}
	return index - fin + 1; 
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
			if(index == prev_length + 1){
				return (s[0] == '[') ? prev_length + 2 : 0;
			}
			if(index == prev_length) return 0;
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
			if(index == prev_length + 1){
				return (s[0] == '(') ? prev_length + 2 : 0;
			}
			if(index == prev_length) return 0;
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
				if(i == prev_length + 1){
					max_lengths[i] = (s[0] == '[') ? prev_length + 2 : 0;
					continue;
				}
				if(i == prev_length){
					max_lengths[i] = 0; continue;
				}
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
				if(i == prev_length + 1){
					max_lengths[i] = (s[0] == '(') ? prev_length + 2 : 0;
					continue;
				}
				if(i == prev_length){
					max_lengths[i] = 0; continue;
				}
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

char random_bracket(std::mt19937& gen){
	std::uniform_int_distribution<> distrib(0, 3);
	char v[4] = {'(', '[', ']', ')'};
	return v[distrib(gen)];
}
std::string perfectly_balanced(int n){
	n = (n / 2) * 2;
	std::vector<char> v(n);
	for(int i = 0; i < n/2; i++){
		v[i] = '(';	
	}
	for(int i = n/2; i < n; i++){
		v[i] = ')';
	}
	std::string s(v.begin(), v.end());
	return s;
}
int main(int argc, char** argv){
	std::mt19937 gen;
	if(argc != 2){
		std::cout << "Need exactly 2 arguments";
		return 1;
	}
	int n = std::atoi(argv[1]);
	std::vector<char> v(n);
	for(int i = 0; i < n; i++){
		v[i] = random_bracket(gen);
	}
    auto start{std::chrono::steady_clock::now()};
   	auto end{std::chrono::steady_clock::now()};
	//std::string s(v.begin(), v.end());
	std::string s = perfectly_balanced(n);
	//brute force
	/*start = std::chrono::steady_clock::now();
	std::cout << brute_force(s);
	end = std::chrono::steady_clock::now();
	std::chrono::duration<double> bf{end - start};
	std::cout << ' ' << bf.count() << '\n';*/
	//scan_left
	/*start = std::chrono::steady_clock::now();
	std::cout << scan_left(s);
	end = std::chrono::steady_clock::now();
	std::chrono::duration<double> sl{end - start};
	std::cout << ' ' << sl.count() << '\n';
	//basic_recursion
	start = std::chrono::steady_clock::now();
	std::cout << basic_recursion(s);
	end = std::chrono::steady_clock::now();
	std::chrono::duration<double> br{end - start};
	std::cout << ' ' << br.count() << '\n';*/
	//dp
	start = std::chrono::steady_clock::now();
	std::cout << dynamic_programming(s);
	end = std::chrono::steady_clock::now();
	std::chrono::duration<double> dp{end - start};
	std::cout << ' ' << dp.count() << '\n';
}
