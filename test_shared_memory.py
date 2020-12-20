from PIL import Image
import numpy as np
from shmem_utils import create_shared_msg_queue, get_next
import matplotlib.pyplot as plt

obj = create_shared_msg_queue("test", 100)
print(obj)

while True:
    print(get_next(obj))