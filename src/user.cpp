﻿#include "user.h"
#include "generator.h"

#include <fstream>
#include <vector>
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::ios;
using std::vector;

User::User() :
	isAuthenticated(false), account(nullptr)
{ }


User::~User() {
	delete account;
}


bool User::Login(const string &userName, const string &passWord) {
	Account cur_acc;
	int cur_role;
	ifstream in;

	in.open("data/account/account.txt");

	while (in >> cur_acc.ID >> cur_acc.username >> cur_acc.password >> cur_role >> cur_acc.firstTimeLogin) {
		if (userName == cur_acc.username && Generator::generatePassword(passWord) == cur_acc.password) {
			cur_acc.role = FormatIntToRole(cur_role);
			this->isAuthenticated = true;
			this->account = new Account();
			this->account->ID = cur_acc.ID;
			this->account->username = cur_acc.username;
			this->account->password = cur_acc.password;
			this->account->role = cur_acc.role;
			this->account->firstTimeLogin = cur_acc.firstTimeLogin;
			in.close();
			return true;
		}
	}

	in.close();

	return false;
}


bool User::Logout() {
	if (!isAuthenticated) return false;

	delete account;
	isAuthenticated = false;
	
	return true;

}


bool User::FirstTimeLogin(void){
	return account->firstTimeLogin;
}


void User::CreateAccount(const int &id, const string &userName, const string &password, const UserRole &role){
	ofstream out;
	out.open("data/account/account.txt", ios::app);

	out << id << " " << userName << " " << Generator::generatePassword(password) << " " << role << " " << 1 << "\n"; // firsttime is true

	out.close();
}


bool User::ResetPassword(const int &id, const string &oldPassword, const string &newPassword){
	vector <Account> ListAcc;
	Account cur_acc;
	int cur_role;
	bool resetStatus = false;

	ifstream in;
	in.open("data/account/account.txt");
	
	while (in >> cur_acc.ID >> cur_acc.username >> cur_acc.password >> cur_role >> cur_acc.firstTimeLogin) {
		if (id == cur_acc.ID && cur_acc.password == Generator::generatePassword(oldPassword)) {
			cur_acc.password = Generator::generatePassword(newPassword);
			resetStatus = true;
		}
		cur_acc.role = FormatIntToRole(cur_role);
		ListAcc.push_back(cur_acc);
	}
	
	in.close();

	if (!resetStatus) {
		return false;
	}

	ofstream out;
	out.open("data/account/account.txt");

	while (!ListAcc.empty()) {
		out << ListAcc.back().ID << " " << ListAcc.back().username << " " << ListAcc.back().password << " " << ListAcc.back().role << " " << ListAcc.back().firstTimeLogin << "\n";
		ListAcc.pop_back();
	}

	out.close();

	return true;
}

void User::DeleteAccount(const int &id){
	vector <Account> ListAcc;
	Account cur_acc;
	int cur_role;

	ifstream in;
	in.open("data/account/account.txt");

	while (in >> cur_acc.ID >> cur_acc.username >> cur_acc.password >> cur_role >> cur_acc.firstTimeLogin) {
		if (id == cur_acc.ID)
			continue;
		cur_acc.role = FormatIntToRole(cur_role);
		ListAcc.push_back(cur_acc);
	}

	in.close();

	ofstream out;
	out.open("data/account/account.txt");

	while (!ListAcc.empty()) {
		out << ListAcc.back().ID << " " << ListAcc.back().username << " " << ListAcc.back().password << " " << ListAcc.back().role << " " << ListAcc.back().firstTimeLogin << "\n";
		ListAcc.pop_back();
	}

	out.close();

	return;
}

UserRole User::FormatIntToRole(int role){
	switch (role) {
	case UserRole::Lecturer:
		return UserRole::Lecturer;

	case UserRole::Staff:
		return UserRole::Staff;

	case UserRole::Student:
		return UserRole::Student;

	default:
		break;
	}
}