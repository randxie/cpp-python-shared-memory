#include "shared_memory.h"
#include "numpy/arrayobject.h"
#include "numpy/ndarrayobject.h"
#include "numpy/ndarraytypes.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <Python.h>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <iterator>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/ocl.hpp>
#include <optional>
#include <vector>

namespace shared_memory {
namespace {
using boost::interprocess::message_queue;
using boost::interprocess::open_or_create;

const static int kNumpyInitialized = _import_array();
const char kSharedMemoryName[] = "SharedMemory";

void destroy_msg_queue(PyObject *msg_queue_obj) {
  delete (SharedMsgQueue *)PyCapsule_GetPointer(msg_queue_obj,
                                                kSharedMemoryName);
}
} // namespace

PyObject *CreateSharedMsgQueue(PyObject *name) {
  PyObject *obj = PyCapsule_New((void *)new SharedMsgQueue(), kSharedMemoryName,
                                destroy_msg_queue);

  return obj;
};

PyObject *GetNext(PyObject *msg_queue_obj) {
  SharedMsgQueue *msg_queue =
      (SharedMsgQueue *)PyCapsule_GetPointer(msg_queue_obj, kSharedMemoryName);

  // Create numpy array for receiving data.
  npy_intp dims[] = {SPECTRUM_FEATURE_DIM};
  auto recv_data_np = PyArray_ZEROS(1, dims, PyArray_DOUBLE, 0);

  // Get data from message queue
  unsigned int priority;
  message_queue::size_type recvd_size;
  bool has_data = msg_queue->mq_->try_receive(
      PyArray_DATA((PyArrayObject *)recv_data_np),
      SPECTRUM_FEATURE_DIM * sizeof(double), recvd_size, priority);

  if (has_data) {
    return recv_data_np;
  } else {
    // Note: do not need to call PyArray_free. PyObject will be gc-ed.
    return Py_BuildValue("");
  }
};

} // namespace shared_memory