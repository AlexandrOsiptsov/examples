# dllist


## Linux

### Компиляция и запуск `main`

```sh
g++ --std=c++17 dllist.hpp main.cpp -o main.out && ./main.out 
```

### Компиляция и запуск тестов

Тесты написаны на gtest фреймворке, для установки на ОС, пропишите:


```sh
sudo apt-get install libgtest-dev
```

Или скачайте и соберите код из `github.com/google/googletest` (чуть дольше)

--- 

Компиляция и запуск тестов

```sh
g++ --std=c++17 test/test_dllist.cpp dlllist.cpp -lgtest -lgtest_main -pthread -o test_dllist
```

### VSCode

При работе на `VSCode` не забываем про 

```json
// .vscode/settings.json

{
    "files.autoSave": "onFocusChange"
}
```