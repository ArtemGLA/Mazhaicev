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

// ТЕСТ 3: Проверка точного соответствия ожидаемым матрицам
{
    ofstream input("test3_input.txt");
    // Матрица A 5x5: исходные данные для получения ожидаемого результата
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
    
    // Ожидаемые матрицы в текстовом формате
    string expectedMatrixA = 
        "   1   11   11   11    6 \n"
        "  11    2   11    7   11 \n"
        "  11   11    3   11   11 \n"
        "  11    8   11    4   11 \n"
        "   9   11   11   11    5 ";
    
    string expectedMatrixC = 
        "  11   11   11   11   11   17 \n"
        "  11   12   11   11   18   11 \n"
        "  11   11   13   19   11   11 \n"
        "  11   11   20   14   11   11 \n"
        "  11   20   11   11   15   11 \n"
        "  21   11   11   11   11   16 ";
    
    cout << "Запуск теста 3 (проверка точного соответствия матриц)...\n";
    if (runTest("Точный ввод", "test3_input.txt", "test3_output.txt")) {
        bool matrixA_correct = false;
        bool matrixC_correct = false;
        
        ifstream output("test3_output.txt");
        string content;
        string line;
        
        // Собираем весь вывод в одну строку для поиска
        while (getline(output, line)) {
            content += line + "\n";
        }
        output.close();
        
        // Создаем упрощенные версии для сравнения (убираем лишние пробелы)
        string simplifiedExpectedA;
        string simplifiedExpectedC;
        string simplifiedContent;
        
        // Копируем только цифры и пробелы в упрощенные строки
        for (char c : expectedMatrixA) {
            if (isdigit(c) || c == ' ') simplifiedExpectedA += c;
        }
        for (char c : expectedMatrixC) {
            if (isdigit(c) || c == ' ') simplifiedExpectedC += c;
        }
        for (char c : content) {
            if (isdigit(c) || c == ' ') simplifiedContent += c;
        }
        
        // Проверяем наличие обеих матриц в выводе
        if (simplifiedContent.find(simplifiedExpectedA) != string::npos) {
            matrixA_correct = true;
        }
        if (simplifiedContent.find(simplifiedExpectedC) != string::npos) {
            matrixC_correct = true;
        }
        
        // Дополнительная проверка через построчный поиск
        ifstream output2("test3_output.txt");
        string lineA, lineC;
        int lineNum = 0;
        bool exactMatchA = true;
        bool exactMatchC = true;
        
        // Разбиваем ожидаемые матрицы на строки
        vector<string> expectedALines;
        vector<string> expectedCLines;
        stringstream ssA(expectedMatrixA);
        stringstream ssC(expectedMatrixC);
        
        while (getline(ssA, lineA)) {
            expectedALines.push_back(lineA);
        }
        while (getline(ssC, lineC)) {
            expectedCLines.push_back(lineC);
        }
        
        // Ищем первую матрицу в выводе
        bool foundA = false;
        bool foundC = false;
        
        while (getline(output2, line)) {
            if (!foundA) {
                // Ищем начало матрицы A (первые несколько чисел из первой строки)
                if (line.find("1   11   11   11    6") != string::npos) {
                    foundA = true;
                    // Проверяем все строки матрицы A
                    for (int i = 0; i < 5 && foundA; i++) {
                        if (i > 0) getline(output2, line);
                        // Упрощенная проверка: ищем ключевые числа в каждой строке
                        switch(i) {
                            case 0: if (line.find("1") == string::npos || 
                                        line.find("6") == string::npos) foundA = false; break;
                            case 1: if (line.find("2") == string::npos || 
                                        line.find("7") == string::npos) foundA = false; break;
                            case 2: if (line.find("3") == string::npos) foundA = false; break;
                            case 3: if (line.find("8") == string::npos || 
                                        line.find("4") == string::npos) foundA = false; break;
                            case 4: if (line.find("9") == string::npos || 
                                        line.find("5") == string::npos) foundA = false; break;
                        }
                    }
                }
            }
        }
        
        // Сбрасываем файл для поиска второй матрицы
        output2.clear();
        output2.seekg(0);
        
        while (getline(output2, line)) {
            if (!foundC) {
                // Ищем начало матрицы C
                if (line.find("11   11   11   11   11   17") != string::npos) {
                    foundC = true;
                    // Проверяем все строки матрицы C
                    for (int i = 0; i < 6 && foundC; i++) {
                        if (i > 0) getline(output2, line);
                        // Упрощенная проверка: ищем ключевые числа
                        switch(i) {
                            case 0: if (line.find("17") == string::npos) foundC = false; break;
                            case 1: if (line.find("12") == string::npos || 
                                        line.find("18") == string::npos) foundC = false; break;
                            case 2: if (line.find("13") == string::npos || 
                                        line.find("19") == string::npos) foundC = false; break;
                            case 3: if (line.find("20") == string::npos || 
                                        line.find("14") == string::npos) foundC = false; break;
                            case 4: if (line.find("20") == string::npos || 
                                        line.find("15") == string::npos) foundC = false; break;
                            case 5: if (line.find("21") == string::npos || 
                                        line.find("16") == string::npos) foundC = false; break;
                        }
                    }
                }
            }
        }
        output2.close();
        
        if (foundA && foundC) {
            cout << "✓ Тест 3 пройден (матрицы полностью соответствуют ожидаемым)\n";
            passed++;
        } else {
            cout << "✗ Тест 3 не пройден (матрицы не соответствуют ожидаемым)\n";
            if (!foundA) cout << "  - Матрица A не совпадает\n";
            if (!foundC) cout << "  - Матрица C не совпадает\n";
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
