#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

bool runTest(const string& testName, const string& inputFile, const string& outputFile) {
    cout << "\n=== Запуск теста: " << testName << " ===\n";
    
    // Формируем команду для запуска вашей программы
    string command = "../usr/bin/hello < " + inputFile + " > " + outputFile;
    
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

bool checkOutput(const string& outputFile, const string& expectedText) {
    ifstream file(outputFile);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл вывода\n";
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
    cout << "=== ТЕСТ 2: Проверка обработки некорректного ввода ===\n";
    
    int passed = 0;
    
    // ТЕСТ 2: Тест с некорректными данными (символы, дроби, буквы)
    {
        ofstream input("test2_input.txt");
        // Для матрицы 5x5 (нужно 25 чисел) - мешаем правильные числа с мусором
        input << "1\n2\nthree\n3\n4\n5\n"        // Третье число - буква
              << "6\n7\n8\n9\n10\n"
              << "11\n0.2\n12\n13\n14\n15\n"      // 0.2 - дробное число (не целое)
              << "16\n17\n18\n19\n20\n"
              << "21\n22\n23\n24\n25\n"
              << "1\n2\n3\n4\n5\n6\n"          // Матрица 6x6 (нужно 36 чисел)
              << "7\n8\n9\nten\n10\n11\n12\n"      // Десятое число - буква
              << "13\n14\n15\n16\n17\n18\n"
              << "19\n20\n21\n22\n23\n24\n"
              << "25\n26\n27\n28\n29\n30\n"
              << "31\n32\n33\n34\n35\n36\n";
        input.close();
        
        cout << "Запуск теста 2 (проверка обработки некорректного ввода)...\n";
        if (runTest("Ввод с ошибками", "test2_input.txt", "test2_output.txt")) {
            // Проверяем, что программа сообщила об ошибке ввода
            if (checkOutput("test2_output.txt", "Ошибка") || 
                checkOutput("test2_output.txt", "некорректный") ||
                checkOutput("test2_output.txt", "не является целым")) {
                cout << "✓ Тест 2 пройден (программа обнаружила ошибку ввода)\n";
                passed++;
            } else {
                cout << "✗ Тест 2 не пройден (программа не сообщила об ошибке при некорректных данных)\n";
            }
        }
    }
    
    if (passed == 1) {
        cout << "\nИТОГ: Тест пройден\n";
    } else {
        cout << "\nИТОГ: Тест не пройден\n";
    }
    
    return 0;
}
