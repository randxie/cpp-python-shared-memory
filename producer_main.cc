#include <boost/interprocess/ipc/message_queue.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace boost::interprocess;

int main() {
  message_queue::remove("message_queue");
  // Create a message_queue.
  message_queue mq(create_only, "message_queue", 100,
                   sizeof(double)); // max message size
  double num = 0.0;
  while (true) {
    std::cout << "Sending...." << std::endl;

    mq.send(&num, sizeof(num), 0);
    num += 1;
    // sleep 2 seconds
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }
  return 0;
}