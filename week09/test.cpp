/*
 * compile with the -g option to include debugging symbols:
 *   clang++ lldbtest.cpp -Wall -g
 * then:
 *   lldb a.out
 *
 * some commands:
 *   h: lists all available commands
 *   run: runs the program
 *   run arg1 [,arg2...]: runs with arguments
 *   breakpoint set--file lldbtest.cpp --line 22: sets a breakpoint at line 22
 *   n: executs the current line
 *   s: steps into a function
 *   gui: loads the ncurses GUI
 *   // clang++ test.cpp -Wall -g
 * */
#include<bits/stdc++.h>
using namespace std;
#define int long long

int32_t main(){
	int t=1; 
	string s; cin>>s;
	cout<<s<<endl;
	for(int i=2; i<6;i++){
		t*=i;
	}
	cout<<t<<endl;
	return 0;
}
