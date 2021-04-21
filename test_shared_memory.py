import time

import matplotlib.pyplot as plt
import numpy as np
from PIL import Image

from shmem_utils import create_shared_msg_queue, get_next

obj = create_shared_msg_queue("test", 100)
print(obj)

while True:
    data = get_next(obj)
    if data is not None:
        print(type(data))
        print(data)
    time.sleep(0.1)