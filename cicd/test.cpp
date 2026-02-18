#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

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
    cout << "=== ТЕСТИРОВАНИЕ ПРОГРАММЫ МАТРИЦЫ ===\n";
    
    int passed = 0;
    
    // ТЕСТ 1: Простой тест с маленькими числами
    {
        ofstream input("test1_input.txt");
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
    // ТЕСТ 2: Тест с некорректными данными (символы, дроби, буквы)
{
    ofstream input("test2_input.txt");
    // Для матрицы 5x5 (нужно 25 чисел) - мешаем правильные числа с мусором
    input << "1\n2\nthree\n4\n5\n"        // Третье число - буква
          << "6\n7\n8\n9\n10\n"
          << "11\n0.2\n13\n14\n15\n"      // 0.2 - дробное число (не целое)
          << "16\n17\n18\n19\n20\n"
          << "21\n22\n23\n24\n25\n"
          << "1\n2\n3\n4\n5\n6\n"          // Матрица 6x6 (нужно 36 чисел)
          << "7\n8\n9\nten\n11\n12\n"      // Десятое число - буква
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

// ТЕСТ 3: Проверка правильности вычислений на заранее известных данных
{
    ofstream input("test3_input.txt");
    // Матрица A 5x5: все числа = 10 (кроме диагоналей, чтобы легко проверить замену)
    // Диагональные элементы: 1, 2, 3, 4, 5 на главной и 6, 7, 3, 8, 9 на побочной
    input << "1\n10\n10\n10\n6\n"     // Строка 1: 1(гл),10,10,10,6(поб)
          << "10\n2\n10\n7\n10\n"     // Строка 2: 10,2(гл),10,7(поб),10
          << "10\n10\n3\n10\n10\n"    // Строка 3: 10,10,3(гл/поб),10,10
          << "10\n8\n10\n4\n10\n"     // Строка 4: 10,8(поб),10,4(гл),10
          << "9\n10\n10\n10\n5\n"     // Строка 5: 9(поб),10,10,10,5(гл)
          // Матрица C 6x6: все числа = 20 (кроме диагоналей)
          // Диагональные элементы: 11,12,13,14,15,16 на гл и 17,18,13,19,20,21 на поб
          << "11\n20\n20\n20\n20\n17\n"  // Строка 1
          << "20\n12\n20\n20\n18\n20\n"  // Строка 2
          << "20\n20\n13\n19\n20\n20\n"  // Строка 3
          << "20\n20\n20\n14\n20\n20\n"  // Строка 4
          << "20\n20\n20\n20\n15\n20\n"  // Строка 5
          << "21\n20\n20\n20\n20\n16\n"; // Строка 6
    input.close();
    
    // Ожидаемые результаты:
    // Матрица A: диагональные элементы: 1+2+3+4+5+6+7+8+9 = 45 (9 элементов, т.к. центр (3) учтен 1 раз)
    // Среднее = 45 / 9 = 5. Все недиагональные элементы должны стать = 5
    // Матрица C: диагональные элементы: 11+12+13+14+15+16+17+18+19+20+21 = 176 (11 элементов, центр(13) учтен 1 раз)
    // Среднее = 176 / 11 = 16. Все недиагональные элементы должны стать = 16
    
    cout << "Запуск теста 3 (проверка точности вычислений)...\n";
    if (runTest("Точный ввод", "test3_input.txt", "test3_output.txt")) {
        // Проверяем наличие ожидаемых значений в выводе
        bool correctA = false;
        bool correctC = false;
        
        ifstream output("test3_output.txt");
        string line;
        while (getline(output, line)) {
            // Ищем в выводе матрицы с числами
            if (line.find("5") != string::npos && line.find("Матрица A") != string::npos) {
                correctA = true;
            }
            if (line.find("16") != string::npos && line.find("Матрица C") != string::npos) {
                correctC = true;
            }
        }
        output.close();
        
        if (correctA && correctC && checkOutput("test3_output.txt", "Программа завершена")) {
            cout << "✓ Тест 3 пройден (результаты вычислений корректны)\n";
            passed++;
        } else {
            cout << "✗ Тест 3 не пройден (неверные результаты вычислений)\n";
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
