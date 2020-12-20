# cpp-python-shared-memory

## VSCode setup

```
  "C_Cpp.default.includePath": [
    "${workspaceFolder}/include",
    "~/anaconda3/envs/vision/include/python3.6m",
    "~/anaconda3/envs/vision/lib/python3.6/site-packages/numpy/core/include"
  ],
  "python.condaPath": "~/anaconda3/condabin/conda",
  "python.pythonPath": "~/anaconda3/envs/vision/bin/python",
  "python.analysis.extraPaths": [
    "~/anaconda3/envs/vision/lib/python3.7/site-packages"
  ],
```

```
g++ -o producer_main producer_main.cc -lboost_system -lpthread
```