#include <boost/interprocess/ipc/message_queue.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#define randint(a, b) (rand() % ((b) - (a))) + (a)

#define randfloat(a, b) ((a) + 1.0 * rand() / RAND_MAX * ((b) - (a)))

namespace {

using namespace boost::interprocess;
constexpr char kMsgQueueName[] = "CppPyMessageQueue";
constexpr int SPECTRUM_FEATURE_DIM = 10;

void generate_data(std::vector<double> &msg, int num) {
  msg.clear();
  msg.shrink_to_fit();
  for (int i = 0; i < SPECTRUM_FEATURE_DIM; i++)
    msg.push_back(randfloat(num, num + 1));
}

} // namespace

int main() {
  // To reuse the previously created queue. You can comment out the remove line.
  // message_queue::remove(kMsgQueueName);
  // Create a message_queue.
  message_queue mq(open_or_create, kMsgQueueName, 100,
                   SPECTRUM_FEATURE_DIM * sizeof(double));

  // Sends an increasing double number.
  std::vector<double> nums;

  while (true) {
    generate_data(nums, randint(1, 100));

    std::cout << "Sending...." << nums.size() << std::endl;

    mq.send(&nums[0], nums.size() * sizeof(double), 0);

    // sleep 2 seconds
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }
  return 0;
}