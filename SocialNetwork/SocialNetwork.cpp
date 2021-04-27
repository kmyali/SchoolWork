#include "SocialNetwork.h"
#include<iostream>


int main() {
	SocialNetwork MyFriends;

	MyFriends.addUser("Albert");
	MyFriends.addUser("Alice");
	MyFriends.addUser("Alisson");
	MyFriends.addUser("Ali");
	MyFriends.addUser("Bob");
	MyFriends.addUser("Art");

	auto i = MyFriends.find("Ali");
	i.setID(0);
	auto j = MyFriends.end();
	for (i; i != j; i++) {
		auto u = *(i);
		std::cout << u.getName();
	}
}
