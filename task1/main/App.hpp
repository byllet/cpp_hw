#pragma once

#include <memory>

#include "Manager.hpp"

class App {
public:
  App();
  void Exec();

private:
  void Parse(std::string &command);

  void CreateUser();
  void DeleteUser();
  void AllUsers();
  void GetUser(int user_id);

  void CreateGroup();
  void DeleteGroup();
  void AllGroups();
  void GetGroup(int group_id);

  void LinkUserGroup();

private:
  Manager _manager;
};