#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

// Функция для запуска программы с заданным входным файлом
bool runTest(const string& testName, const string& inputFile, const string& outputFile) {
    cout << "\n=== Запуск теста: " << testName << " ===\n";
    
    // Формируем команду для запуска вашей программы
    string command = "./hello < " + inputFile + " > " + outputFile;
    
    // Запускаем программу
    int result = system(command.c_str());
    
    if (result == 0) {
        cout << "Программа выполнилась успешно\n";
        return true;
    } else {
        cout << "Ошибка выполнения программы\n";
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
    
    int passed = 0;
    
    // ТЕСТ 1: Простой тест с маленькими числами
    {
        ofstream input("/home/runner/work/TestGitHub/TestGitHub/usr/bin/hello");
        input << "1\n2\n3\n4\n5\n"  // Матрица 5x5 (первые 25 чисел)
              << "6\n7\n8\n9\n10\n"
              << "11\n12\n13\n14\n15\n"
              << "16\n17\n18\n19\n20\n"
              << "21\n22\n23\n24\n25\n"
              << "1\n2\n3\n4\n5\n6\n"  // Матрица 6x6 (первые 36 чисел)
              << "7\n8\n9\n10\n11\n12\n"
              << "13\n14\n15\n16\n17\n18\n"
              << "19\n20\n21\n22\n23\n24\n"
              << "25\n26\n27\n28\n29\n30\n"
              << "31\n32\n33\n34\n35\n36\n";
        input.close();
        
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
        cout << "Тест пройден\n";
    } else {
        cout << "Тест не пройден\n";
    }
    return 0;
}
