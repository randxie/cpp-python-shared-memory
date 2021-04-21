import time

import matplotlib.pyplot as plt
import numpy as np
# from memprof import memprof

from shmem_utils import create_shared_msg_queue, get_next


# @memprof(plot=True)
def run():
    obj = create_shared_msg_queue("test", 100)
    count = 0
    print(obj)

    while True:
        data = get_next(obj)
        if data is not None:
            print(type(data))
            print(data)
            count += 1
            if count > 10:
                break
        time.sleep(0.1)


run()