#include <array>
#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

enum LogStatus { LOG_NORMAL, LOG_ERROR, LOG_NOTE };

const std::size_t N = 10;

template <class Derrived> class Singleton {
public:
  static Derrived *Instance() {
    if (!_ptr) {
      _ptr = new Derrived();
    }
    return _ptr;
  }

  static void Destroy() {
    delete _ptr;
    _ptr = nullptr;
  }

private:
  static Derrived *_ptr;
};

template <class Derrived> Derrived *Singleton<Derrived>::_ptr = nullptr;

class Log : public Singleton<Log> {
  friend Singleton<Log>;

private:
  Log() : _messages{} {}
  std::array<std::string, N> _messages;
  std::size_t i = 0;

public:
  void Message(LogStatus status, const std::string &message) {
    std::stringstream out_message;
    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);

    out_message << std::ctime(&t_c);

    switch (status) {
    case LOG_ERROR:
      out_message << "ERROR: ";
      break;
    case LOG_NORMAL:
      out_message << "NORMA: ";
      break;
    case LOG_NOTE:
      out_message << "NOTE: ";
      break;
    }

    out_message << message << std::endl;

    if (i < N)
      _messages[i++] = out_message.str();
  }

  void Print() const {
    for (const auto &msg : _messages) {
      if (!msg.empty())
        std::cout << msg << '\n';
    }
  }
};

int main() {
  Log *log = Log::Instance();
  log->Message(LOG_ERROR, "SOME BIG ERROR");
  log->Message(LOG_NORMAL, "All normal");
  log->Message(LOG_NOTE, "There are note");
  log->Print();
  Log::Destroy();
  return 0;
}