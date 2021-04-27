#include"Set.h"
using namespace std;

int main() {
	Set<int> si;
	si.insert(3);
	for (int n : { 22, 30 })
	{
		si.insert(n);
	}
	
	for (const auto& v : si)
	{
		cout<<si.contains(v)<<",";
	}

}