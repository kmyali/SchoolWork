#ifndef SOCIAL_NETWORK_H_
#define SOCIAL_NETWORK_H_

#include "User.h"


 /**
  * A (rather crude!) representation of a social network.
  */
//This is basically a graph
class SocialNetwork
{
public:

	SocialNetwork() {
		users.push_back(nullptr);
	}

	//! Add a new user to the social network.
	User::ID addUser(std::string name) {
		auto u = std::make_shared<User>(name); //Construct a dynamically allocated user
		u->setID( users.size()-1);
		users[users.size() - 1]= u; //Replace the nullptr
		users.push_back(nullptr);
		return u->id();
	}

	/**
	 * Add a (bidirectional/undirected) friendship link between two users.
	 *
	 * @pre the named users actually exist in the social network
	 */
	SocialNetwork& addFriendship(User::ID user1, User::ID user2) {
		users[user1]->addFriend(*users[user2]);
		users[user2]->addFriend(*users[user1]); //add to the friends list of each other
		User::Edge* e = new User::Edge(user1, user2); //create the edge dynamically
		adjacencies.push_back(*e); //add the edge to the adjacency list by dereferencing the pointer
		return *this;
	}

	//! Retrieve a reference to a specific user.
	User& getUser(User::ID id) {
		return *users[id]; //because the vector is ordered, we directly pass in the id to the vector
	}

	//! An iterator over users in the social network
	struct Iterator
	{
		Iterator(std::vector<std::shared_ptr<User>> u) {
			userID = 0;
			users = u;
		}

		Iterator(std::vector<std::shared_ptr<User>> u, std::string name) {
			for (int i = 0; i < u.size()-1; i++) {
				std::string userName = u[i]->getName();
				int stringSize = name.size();
				std::string compareTo = userName.substr(0, stringSize);
				if (name == compareTo) {
					users.push_back(u[i]);
				}
			}
			users.push_back(nullptr);
		}

		void setID(User::ID number){
			userID = number;
		}
		std::string getName() {
			return users[userID]->getName();
		}
		User& operator*() {
			return *users[userID]; 
		}
		Iterator operator ++ (int) {
			userID++;
			return *this;
		}

		bool operator == (const Iterator& other) const {
			if (users[userID] == other.users[users.size() - 1])
				return true;
			else
				return false;
		}
		bool operator != (const Iterator& other) const {
			bool ret = false;
			auto x = other.users[other.users.size() - 1];
			if (users[userID] !=x )
				ret= true;
			return ret;
		}

		User::ID userID;
		std::vector<std::shared_ptr<User>> users;
	};

	//! Get an iterator over all users in the network.
	Iterator begin() {
		Iterator it(users);
		return it;
	}

	//! Find all users in the network whose names start with `name`.
	Iterator find(std::string name) {
		auto i = Iterator(users, name);
		return i;
	}

	//! Get an iterator that signifies the end of any user iteration.
	Iterator end() {
		Iterator it(users);
		it.setID(users.size());
		return it;
	}

private:
	std::vector<std::shared_ptr<User>> users; //Should i use share_ptr
	std::vector<User::Edge> adjacencies; 
};

#endif