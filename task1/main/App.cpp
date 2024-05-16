#include "App.hpp"
#include "Group.hpp"
#include "User.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_map>

const std::string PROMPT = "> ";
const std::string USER_ID = "user_id:";
const std::string USERNAME = " username:";
const std::string GROUP_ID = " group_id:";
const int BAD_GROUP = -444;

enum class Command {
  CREATE_USER,
  DELETE_USER,
  ALL_USERS,
  GET_USER,
  CREATE_GROUP,
  DELETE_GROUP,
  ALL_GROUPS,
  GET_GROUP,
  LINK_USER_GROUP
};

std::unordered_map<std::string, Command> map = {
    {"createuser", Command::CREATE_USER},
    {"deleteuser", Command::DELETE_USER},
    {"allusers", Command::ALL_USERS},
    {"getuser", Command::GET_USER},
    {"creategroup", Command::CREATE_GROUP},
    {"deletegroup", Command::DELETE_GROUP},
    {"allgroups", Command::ALL_GROUPS},
    {"getgroup", Command::GET_GROUP},
    {"linkusergroup", Command::LINK_USER_GROUP},
    {"cu", Command::CREATE_USER},
    {"du", Command::DELETE_USER},
    {"au", Command::ALL_USERS},
    {"gu", Command::GET_USER},
    {"cg", Command::CREATE_GROUP},
    {"dg", Command::DELETE_GROUP},
    {"ag", Command::ALL_GROUPS},
    {"gg", Command::GET_GROUP},
    {"lug", Command::LINK_USER_GROUP},
};

void PrintUserInfo(int user_id, const std::string &username, int group_id,
                   const std::string &info);

App::App() {}

void App::Exec() {
  while (std::cin) {
    std::cout << PROMPT;
    std::string command;
    std::cin >> command;
    Parse(command);
  }
}

void App::Parse(std::string &command) {
  std::transform(command.begin(), command.end(), command.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  switch (map[command]) {
  case Command::CREATE_USER:
    CreateUser();
    return;

  case Command::DELETE_USER:
    DeleteUser();
    return;

  case Command::ALL_USERS:
    AllUsers();
    return;

  case Command::GET_USER: {
    int user_id;
    std::cin >> user_id;
    GetUser(user_id);
    return;
  }

  case Command::CREATE_GROUP:
    CreateGroup();
    return;

  case Command::DELETE_GROUP:
    DeleteGroup();
    return;

  case Command::ALL_GROUPS:
    AllGroups();
    return;

  case Command::GET_GROUP: {
    int group_id;
    std::cin >> group_id;
    GetGroup(group_id);
    return;
  }

  case Command::LINK_USER_GROUP:
    LinkUserGroup();
    return;
  }

  char bad_input[256];
  std::cin.getline(bad_input, 256);
  std::cout << "Unknown enter" << std::endl;
}

void App::CreateUser() {
  int user_id;
  std::cin >> user_id;
  std::string username;
  std::cin >> username;
  std::string status = "Created";
  std::string name = username;

  if (_manager.AddNewUser(user_id, username) == 0) {
    status = "Already exist";
    name = _manager.GetUser(user_id)->GetName();
  }

  PrintUserInfo(user_id, name, BAD_GROUP, status);
}

void App::DeleteUser() {
  int user_id;
  std::cin >> user_id;
  std::string status = "Not exist";

  if (_manager.DeleteUser(user_id)) {
    status = "Deleted";
  }

  PrintUserInfo(user_id, "", BAD_GROUP, status);
}

void App::AllUsers() {
  for (const auto &users_iter : _manager.GetUsers()) {
    const auto &user = users_iter.second;
    GetUser(user->GetUserId());
  }
}

void App::GetUser(int user_id) {
  if (_manager.IsUserExist(user_id) == 0) {
    std::cout << "Not exist" << std::endl;
    return;
  }

  const auto &user = _manager.GetUser(user_id);
  PrintUserInfo(user_id, user->GetName(), user->GetGroupId(), "");
}

void App::CreateGroup() {
  int group_id;
  std::cin >> group_id;
  std::string status = "Created";

  if (_manager.AddNewGroup(group_id) == 0) {
    status = "Already exist";
  }

  std::cout << status << " " << "group_id:" << group_id << std::endl;
}

void App::DeleteGroup() {
  int group_id;
  std::cin >> group_id;
  std::string status = "Not exist";

  if (_manager.DeleteGroup(group_id)) {
    status = "Deleted";
  }

  std::cout << status << " group_id:" << group_id << std::endl;
}

void App::AllGroups() {
  for (const auto &group_iter : _manager.GetGroups()) {
    const auto &group = group_iter.second;
    GetGroup(group->GetGroupId());
  }
}

void PrintAllUsers(const std::shared_ptr<Group> &group) {
  for (const auto &user_ptr : group->GetUsers()) {
    const auto &user = *user_ptr.lock();
    if (user.GetGroupId() == group->GetGroupId()) {
      std::cout << "    user_id:" << user.GetUserId() << '\n';
    }
  }
}

void App::GetGroup(int group_id) {
  if (_manager.IsGroupExist(group_id) == 0) {
    std::cout << "Not exits" << std::endl;
    return;
  }

  std::cout << "group_id:" << group_id << '\n';
  const auto &group = _manager.GetGroup(group_id);
  PrintAllUsers(group);
}

void App::LinkUserGroup() {
  int user_id;
  int group_id;
  std::cin >> user_id >> group_id;
  if (_manager.IsUserExist(user_id) == 0) {
    std::cout << "user_id:" << user_id << " not exist" << std::endl;
    return;
  }

  if (_manager.IsGroupExist(group_id) == 0) {
    std::cout << "group_id:" << group_id << " not exist" << std::endl;
    return;
  }

  std::weak_ptr<User> user = _manager.GetUser(user_id);
  _manager.GetGroup(group_id)->AddUser(user);

  std::weak_ptr<Group> group = _manager.GetGroup(group_id);
  _manager.GetUser(user_id)->SetGroup(group);

  std::cout << "Linked user_id:" << user_id << " with group:id" << group_id
            << std::endl;
}

void PrintUserInfo(int user_id, const std::string &username, int group_id,
                   const std::string &info) {
  std::string out = info;
  if (info.size()) {
    out += " ";
  }

  out += USER_ID;
  out += std::to_string(user_id);

  if (username.size() > 0) {
    out += USERNAME;
    out += username;
  }

  if (group_id != BAD_GROUP) {
    out += GROUP_ID;
    out += std::to_string(group_id);
  }

  std::cout << out << std::endl;
}