#include <boost/interprocess/ipc/message_queue.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

namespace {

using namespace boost::interprocess;
const char kMsgQueueName[] = "CppPyMessageQueue";

} // namespace

int main() {
  // To reuse the previously created queue. You can comment out the remove line.
  
  message_queue::remove(kMsgQueueName);
  // Create a message_queue.
  message_queue mq(open_or_create, kMsgQueueName, 100, sizeof(double));

  // Sends an increasing double number.
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