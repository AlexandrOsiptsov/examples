// Условие: Разбить токены строки на группы анаграмм.
// не нарушая порядок следования внутри групп (опционально)

// Анаграммы - слова, состоящие из одних наборов букв, например:
// ("ток", "кот"), ("апорт", "тропа", "топар"), ("itto", "otit")

// Пример входа:  "ittos llo lol oll tosit hello"
// Пример выхода: [ ["ittos", "tosit"], ["llo", "lol", "oll"], ["hello"] ]

#include <cstddef>
#include <cstring>
#include <iostream>

size_t tokens_num(const char* s, const char* del) {
    size_t res{0};
    while (s != NULL && *s != '\0') {
        s += strspn(s, del);
        s += strcspn(s, del);
        ++res;
    }
    return res;
}

bool anagrams(const char* s1, const char* s2) {
    size_t ht[256] {0};
    while (*s1 != '\0') ++ht[(unsigned char)(*s1++)];
    while (*s2 != '\0') --ht[(unsigned char)(*s2++)];
    for (int i = 0; i < 256; ++i) if (ht[i] != 0) return false;
    return true;
}


template <typename T>
struct SizedArr {
    T* arr;
    size_t size;
};

SizedArr<SizedArr<const char*>> groupify(
    const char** tokens,
    size_t tc, // tokens count
    bool (*same_group)(const char*, const char*) // ф-ция определяющая должны ли токены быть в одной группе
) {
    SizedArr<SizedArr<const char*>> res;

    size_t* ids = new size_t[tc] {0}; // "айдишники"
    int curr_id {0};                  // current id

    // Каждому токену присваиваем id его группы (начиная с 1, 2, 3 ...)
    for (int i = 0; i < tc; ++i) {
        if (ids[i] != 0) continue;
        ids[i] = ++curr_id;

        for (int j = i + 1; j < tc; ++j) {
            if (ids[j] != 0) continue;
            if (same_group(tokens[i], tokens[j])) ids[j] = curr_id;
            // использование здесь указателя на любую ф-цию однозначно разбивающую массив токенов на группы
            // делает groupify универсальной
        }
    }

    res.size = curr_id;
    res.arr = new SizedArr<const char*>[res.size];

    size_t* group_sizes = new size_t[res.size];
    for (int i = 0; i < tc; ++i) ++group_sizes[ids[i] - 1]; // считаем размер каждой группы за O(n) + массив group_sizes
    
    // Выделяем память и запоминаем размер для каждой группы
    for (int i = 0; i < res.size; ++i) {
        res.arr[i].arr = new const char*[group_sizes[i]];
        res.arr[i].size = group_sizes[i];
    }

    // Заполняем каждую группу за O(n) используя уже выделенный массив group_sizes (чтобы не создавать новый)
    for (int i = 0; i < tc; ++i) {
        const size_t g_ind = ids[i] - 1;
        res.arr[g_ind].arr[res.arr[g_ind].size - group_sizes[g_ind]--] = tokens[i]; 
        // не рекоммендую делать так на серьёзных проектах
    }
    delete[] group_sizes;
    delete[] ids;

    return res;
}

int main() {
    char s[] = "ittos llo lol oll tosit hello";
    const char *del = " ,.?";

    size_t tc = tokens_num(s, del);
    const char** tokens = new const char*[tc];

    char* temp = strtok(s, del);
    for (size_t c = 0; temp != NULL; temp = strtok(NULL, del)) tokens[c++] = temp;

    auto res = groupify(tokens, tc, anagrams);
    for (int i = 0; i < res.size; ++i) {
        std::cout << "Group " << i + 1 << ": ";
        for (int j = 0; j < res.arr[i].size; ++j) {
            std::cout << res.arr[i].arr[j] << ' ';
        }
        std::cout << '\n';
    }

    // Пример освобождения памяти такого результата
    for (int i = 0; i < res.size; ++i) delete[] res.arr[i].arr;

    return 0;
}
