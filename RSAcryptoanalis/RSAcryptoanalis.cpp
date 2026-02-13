#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

/**
 * Проверка числа на простоту с использованием теста Миллера-Рабина
 * @param n - число для проверки
 * @param k - количество раундов теста (точность проверки)
 * @return true, если число вероятно простое, false - если составное
 */
bool is_prime(long long n, int k = 5) {
    // Обработка простых случаев
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    // Представляем n-1 в виде (2^s)*d
    long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    // Проводим k раундов теста
    for (int i = 0; i < k; i++) {
        // Выбираем случайное основание a в диапазоне [2, n-2]
        long long a = 2 + rand() % (n - 3);
        long long x = 1;

        // Вычисляем a^d mod n с помощью возведения в степень по модулю
        long long power = d;
        while (power > 0) {
            if (power % 2 == 1) {
                x = (x * a) % n;
            }
            a = (a * a) % n;
            power /= 2;
        }

        // Если x == 1 или x == n-1, переходим к следующему раунду
        if (x == 1 || x == n - 1) continue;

        // Повторяем s-1 раз
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = (x * x) % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }

        // Если не найдено x == n-1, число составное
        if (composite) return false;
    }
    return true;
}

/**
 * Генерация двух близких простых чисел заданной битовой длины
 * @param bit_length - битовая длина генерируемых чисел
 * @return пара простых чисел (p, q), где q > p и они близки друг к другу
 */
pair<long long, long long> generate_close_primes(int bit_length) {
    // Инициализация генератора случайных чисел
    random_device rd;
    mt19937 gen(rd());
    // Диапазон для генерации чисел заданной битовой длины
    uniform_int_distribution<long long> dis(1LL << (bit_length - 2), (1LL << (bit_length - 1)) - 1);

    cout << "Начинаем генерацию близких простых чисел...\n";

    while (true) {
        // Генерируем случайное начальное значение p
        long long p = dis(gen);
        cout << "Пробуем начальное значение p = " << p;

        // Ищем следующее простое число после p
        while (!is_prime(p)) {
            p++;
            if (p % 1000 == 0) cout << "."; // Вывод прогресса
        }
        cout << "\nНайдено простое p = " << p << "\n";

        // Ищем простое число q близкое к p (в пределах 2^20)
        cout << "Ищем близкое простое q...\n";
        for (long long q = p + 2; q < p + (1 << 20); q += 2) {
            if (is_prime(q)) {
                cout << "Найдено простое q = " << q << " (разница с p: " << q - p << ")\n";
                cout << "Генерация завершена.\n\n";
                return { p, q };
            }
            if ((q - p) % 1000 == 0) cout << "."; // Вывод прогресса
        }
        cout << "\nНе удалось найти близкое q для p = " << p << ", пробуем новое p...\n";
    }
}

/**
 * Факторизация числа методом Ферма
 * @param n - число для факторизации (произведение двух близких простых)
 * @return пара множителей (p, q) таких, что p*q = n
 */
pair<long long, long long> fermat_factorization(long long n) {
    cout << "\nНачинаем факторизацию методом Ферма...\n";
    cout << "Ищем такие a и b, что n = a² - b² = (a-b)(a+b)\n";

    // Начальное значение a - наименьшее целое, большее или равное √n
    long long a = ceil(sqrt(n));
    // Вычисляем начальное b² = a² - n
    long long b2 = a * a - n;

    cout << "Начальное значение a = ceil(√n) = " << a << "\n";
    cout << "Начальное значение b² = a² - n = " << b2 << "\n\n";

    int step = 0;
    while (true) {
        step++;
        // Проверяем, является ли b² полным квадратом
        long long b = round(sqrt(b2));
        if (b * b == b2) {
            cout << "Шаг " << step << ": Найдено решение!\n";
            cout << "b² = " << b2 << " является полным квадратом (b = " << b << ")\n";
            // Находим множители: p = a - b, q = a + b
            long long p = a - b;
            long long q = a + b;
            cout << "Найденные множители: p = a - b = " << p << ", q = a + b = " << q << "\n";
            return { p, q };
        }

        // Периодический вывод текущего состояния
        if (step % 100 == 0) {
            cout << "Шаг " << step << ": a = " << a << ", b² = " << b2;
            cout << " (b ≈ " << sqrt(b2) << ")\n";
        }

        // Увеличиваем a и пересчитываем b²
        a++;
        b2 = a * a - n;
    }
}

int main() {
    setlocale(LC_ALL, "Russian"); 

    cout << "=== Атака на RSA методом Ферма ===\n";
    cout << "Генерируем два близких простых числа p и q...\n";

    // Генерируем два близких простых числа (30 бит для демонстрации)
    auto [p, q] = generate_close_primes(30);
    long long n = p * q;

    // Выводим параметры RSA
    cout << "=== Параметры RSA ===" << endl;
    cout << "p = " << p << "\nq = " << q << "\n";
    cout << "n = p * q = " << n << "\n\n";

    // Запускаем атаку методом Ферма и замеряем время
    cout << "=== Начало атаки ===" << endl;
    auto start = chrono::high_resolution_clock::now();
    auto [found_p, found_q] = fermat_factorization(n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // Выводим результаты
    cout << "\n=== Результаты факторизации ===" << endl;
    cout << "Найденный p = " << found_p << "\n";
    cout << "Найденный q = " << found_q << "\n";
    cout << "Время выполнения: " << elapsed.count() << " секунд\n";

    // Проверяем корректность результатов
    if (found_p == p && found_q == q) {
        cout << "\nАтака успешна! Найдены исходные простые множители.\n";
    }
    else {
        cout << "\nАтака не удалась.\n";
    }

    // Дополнительная проверка через перемножение
    cout << "\n=== Проверка ===" << endl;
    cout << "p * q = " << found_p * found_q << " (должно быть равно " << n << ")\n";

    return 0;
}