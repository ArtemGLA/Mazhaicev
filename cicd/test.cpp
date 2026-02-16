#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

// Функция для запуска программы с заданным входным файлом
bool runTest(const string& testName, const string& inputFile, const string& outputFile) {
    cout << "\n=== Запуск теста: " << testName << " ===\n";
    
    // ✅ ПРАВИЛЬНЫЙ ПУТЬ к hello в usr/bin
    string command = "../usr/bin/hello < " + inputFile + " > " + outputFile;
    
    // Запускаем программу
    int result = system(command.c_str());
    
    if (result == 0) {
        cout << "Программа выполнилась успешно\n";
        return true;
    } else {
        cout << "Ошибка выполнения программы. Команда: " << command << "\n";
        return false;
    }
}

// Проверка наличия определенного текста в выводе
bool checkOutput(const string& outputFile, const string& expectedText) {
    ifstream file(outputFile);
    if (!file.is_open()) {
        cout << "✗ Не удалось открыть файл вывода\n";
        return false;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.find(expectedText) != string::npos) {
            file.close();
            return true;
        }
    }
    
    file.close();
    return false;
}

int main() {
    cout << "=== ТЕСТИРОВАНИЕ ПРОГРАММЫ МАТРИЦЫ ===\n";
    
    // Отладка - посмотрим где мы и что доступно
    cout << "Текущая директория: ";
    system("pwd");
    cout << "Проверяем наличие hello: ";
    system("ls -la ../usr/bin/ || echo 'hello не найден!'");
    
    int passed = 0;
    
    // ТЕСТ 1: Простой тест
    {
        // ✅ Создаем test1_input.txt в текущей папке (./cicd/)
        ofstream input("test1_input.txt");
        input << "1 2 3 4 5\n"
              << "6 7 8 9 10\n"
              << "11 12 13 14 15\n"
              << "16 17 18 19 20\n"
              << "21 22 23 24 25\n";
        input.close();
        
        cout << "✅ Создан файл: test1_input.txt\n";
        
        if (runTest("Простой ввод", "test1_input.txt", "test1_output.txt")) {
            if (checkOutput("test1_output.txt", "Программа завершена")) {
                cout << "✓ Тест 1 пройден\n";
                passed++;
            } else {
                cout << "✗ Тест 1 не пройден\n";
            }
        }
    }
    
    if (passed == 1) {
        cout << "✅ Тест пройден\n";
        return 0;
    } else {
        cout << "❌ Тест не пройден\n";
        return 1;
    }
}
