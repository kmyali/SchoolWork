#ifndef USER_H_
#define USER_H_

#include <cstddef>      // for definition of size_t
#include <memory>       // std::unique_ptr
#include <string>
#include<vector>
#include<queue>

 /**
  * Representation of a social network user.
  */
class User
{
public:
	using ID = size_t;
	
	User(std::string name){
		name_ = name;
		//done = false; //for iterators
		degree_ = 0;
	}
	
	void setID(ID number) {
		userID_ = number;
	}

	std::string getName() {
		return name_;
	}

	//! What is this user's ID?
	ID id() const {
		return userID_;
	}

	//! How many friends does this user have?
	size_t degree() const {
		return degree_;
	}

	/**
	 * What is the shortest path to the given User from this one?
	 *
	 * @returns   the number of friend links between this User and that
	 *            one, or SIZE_MAX if there is no connection between them
	 */
	size_t distance(const User&) const {
		return 1;
	}

	//! Make this User friends with another User.
	void addFriend(const User& other) {
		friends.push_back(other);
		degree_++;
	}

	//! An iterator that can iterate over all of a User's friends
	struct FriendIterator
	{

		FriendIterator() {
			currentUser = 0;
		}

		FriendIterator(std::vector<User> friends) {
			currentUser = 0;
			friends_ = friends;
		}
		FriendIterator(std::vector<User> friends, std::string name) {
			for (int i = 0; i < friends.size(); i++) {
				std::string userName = friends[i].name_;
				int stringSize = name.size();
				if (name == userName.substr(0, stringSize)) {
					friends_.push_back(friends[i]);
				}
			}
		}
		User& operator*() {
			return friends_[currentUser]; 
		}

		FriendIterator operator ++ (int) {
			currentUser += 1;
			return *this;
		}

		bool operator == (const FriendIterator& other) const {
			return (currentUser == other.currentUser);
		}
		bool operator != (const FriendIterator& other) const {
			return (currentUser != other.currentUser);
		}

		void setID(ID id) {
			currentUser = id;
		}
		
		ID currentUser;
		std::vector<User> friends_;
		//bool ofFriends_;
		//std::queue<User> worklist;
	};

	//! Get an iterator that will iterate over this User's friends
	FriendIterator begin() const {
		FriendIterator it = FriendIterator(friends);
		return it;
	}

	/**
	 * Get an iterator that will iterate over this User's friends
	 * as well as **their** friends.
	 *
	 * The resulting iterator should iterate over all of this user's friends
	 * and friends of friends in no particular order. This user (i.e., the
	 * centre of the egonet) should not show up in the iteration, and no
	 * single user should be iterated over more than once.
	 */
	FriendIterator friendsOfFriends() const {
		//FriendIterator(friends, this, true); // a bool for friendsOfFriends
		FriendIterator it = FriendIterator(friends);
		return it;
	}

	//! Get an iterator that signifies the end of any friend iteration.
	FriendIterator end() const {
		FriendIterator it;
		it.setID(friends.size());
		return it;
	}

	struct Edge {
		Edge(ID u1, ID u2) {
			user1 = u1;
			user2 = u2;
		}
		ID user1;
		ID user2;
	};

private:
	std::vector<User> friends;
	ID userID_;
	std::string name_;
	size_t degree_;
	//bool done;
	//
};

#endif