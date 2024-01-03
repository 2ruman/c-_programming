# C++ Code Snippets

### Contents
+ [Thread](#thread)
<br>

## Thread

### Sleep
   
```cpp
#include <chrono>
#include <thread>

std::this_thread::sleep_for(std::chrono::seconds(5));

std::this_thread::sleep_for(std::chrono::milliseconds(5000));

std::this_thread::sleep_for(std::chrono::microseconds(5000000));

std::this_thread::sleep_for(std::chrono::nanoseconds(5000000000));
```

