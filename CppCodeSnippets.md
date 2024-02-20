# C++ Code Snippets

### Contents
+ [Container](#container)
+ [Macro](#macro)
+ [Thread](#thread)
<br>

## Container

### Safely Get String from Map

```cpp
#include <string>
#include <unordered_map>

const std::string &getOrDefault(const std::unordered_map<int, std::string> &map, int key,
        const std::string &defaultVal) {
    auto iter = map.find(key);
    return iter != map.end() ? iter->second : defaultVal;
}

const std::string &getOrEmpty(const std::unordered_map<int, std::string> &map, int key) {
    return getOrDefault(map, key, "");
}

/* Otherwise, as a single function */
const std::string &getOrEmpty(const std::unordered_map<int, std::string> &map, int key) {
    static const std::string empty{};
    auto iter = map.find(key);
    return iter != map.end() ? iter->second : empty;
}
```

## Macro

### Loop & Condition Comparison

```cpp
/* Check if the flag is set in the given flags */
#define CHECK_FLAGS(flags, flag) if (((flags) & (flag)) > 0)

/* Check if the result is negative */
#define CHECK_NEGATIVE(r) if ((r) < 0)

/* Break the loop if the result is negative */
#define NEGATIVE_BREAK(r) if ((r) < 0) break

/* Oneshot loop that doesn't repeat */
#define ONESHOT_LOOP do {
#define ONESHOT_LOOP_END } while(false);
```

### Loop & Condition Comparison - Example

```cpp
const static int FLAG_A = 0x01;
const static int FLAG_B = 0x02;
const static int FLAG_C = 0x03;

int doA() { return 0; };
int doBC() { return -1; };

int test(int flags) {
    int rc;

    ONESHOT_LOOP

        CHECK_FLAGS(flags, FLAG_A) NEGATIVE_BREAK(rc = doA());
        CHECK_FLAGS(flags, FLAG_B | FLAG_C) NEGATIVE_BREAK(rc = doBC());
        rc = 0;

    ONESHOT_LOOP_END

    return rc;
}

int main() {
    printf("Result : %d\n", test(FLAG_A|FLAG_C));
    return 0;
}
```

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

