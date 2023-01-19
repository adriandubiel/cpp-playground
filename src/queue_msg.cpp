#include <condition_variable>
#include <iostream>
#include <queue>
#include <thread>

using namespace std;

struct Color {
  int r;
  int g;
  int b;
};

struct Message {
  enum class Id { SET_STATE = 0, SET_INTENSITY, SET_COLOR, TERMINATE };
  union Params {
    Color rgb;
    uint8_t intensity;
    bool state;
  };

  Id id;
  Params params;
};

mutex mtx;
condition_variable cv{};
queue<Message> msgs{};

void SetState(const bool state) { std::cout << "SetState " << state << "\n"; }

void SetIntensity(const uint8_t intensity) {
  std::cout << "SetIntensity " << (unsigned int)intensity << "\n";
}

void SetColor(const Color color) {
  std::cout << "SetColor " << color.r << ", " << color.g << ", " << color.b
            << "\n";
}

Message GetMessage() {
  unique_lock<mutex> lck{mtx};
  cv.wait(lck, []() { return !msgs.empty(); });

  auto m = msgs.front();
  msgs.pop();
  return m;
}

void PutMessage(const Message &msg) {
  unique_lock<mutex> lck{mtx};
  msgs.push(msg);
  lck.unlock();
  cv.notify_one();
}

void controller() {
  Color white = {255, 255, 255};
  uint8_t intensity = 255;

  PutMessage(Message{Message::Id::SET_STATE, true}); // switch on
  PutMessage(Message{Message::Id::SET_INTENSITY,
                     intensity}); // set the highest intensity
  PutMessage(Message{Message::Id::SET_COLOR, white}); // set color to white
  PutMessage(Message{Message::Id::SET_STATE, false}); // switch off
  PutMessage(Message{Message::Id::TERMINATE});
}

void handler() {
  while (true) {
    const Message msg = GetMessage();
    switch (msg.id) {
    case Message::Id::SET_STATE:
      SetState(msg.params.state);
      break;
    case Message::Id::SET_INTENSITY:
      SetIntensity(msg.params.intensity);
      break;
    case Message::Id::SET_COLOR:
      SetColor(msg.params.rgb);
      break;
    case Message::Id::TERMINATE:
      cout << "TERMINATE" << endl;
      return;
      break;
    default:
      break;
    }
  }
}

int main() {

  thread t1{handler};
  thread t2{controller};

  t1.join();
  t2.join();

  return 0;
}
