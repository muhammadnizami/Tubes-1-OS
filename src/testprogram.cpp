#include <iostream>
using namespace std;
int main(int argc, char * argv []){
	char a[1024];
	cin>>a;
	cout<<a<<endl;
	for (int i=0;i<argc;i++)
		cout<<argv[i]<<endl;
}
