#ifndef SHARED_MEMORY_H_
#define SHARED_MEMORY_H_

#include <Python.h>
#include <boost/interprocess/ipc/message_queue.hpp>

namespace shared_memory {

using boost::interprocess::message_queue;
using boost::interprocess::open_or_create;

constexpr char kMsgQueueName[] = "CppPyMessageQueue";
constexpr int SPECTRUM_FEATURE_DIM = 10;

struct SharedMsgQueue {
  message_queue *mq_;
  SharedMsgQueue() {
    mq_ = new message_queue(open_or_create, kMsgQueueName, 100,
                            SPECTRUM_FEATURE_DIM * sizeof(double));
  }

  ~SharedMsgQueue() {}
};

PyObject *CreateSharedMsgQueue(PyObject *name);

PyObject *GetNext(PyObject *msg_queue_obj);

} // namespace shared_memory

#endif // SHARED_MEMORY_H_