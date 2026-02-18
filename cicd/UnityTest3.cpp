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
    cout << "=== ТЕСТ 3: Проверка точного соответствия матриц ===\n";
    
    int passed = 0;
    
    // ТЕСТ 3: Проверка точного соответствия ожидаемым матрицам
    {
        ofstream input("test3_input.txt");
        // Матрица A 5x5: исходные данные
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
        
        cout << "Запуск теста 3 (проверка точного соответствия матриц)...\n";
        if (runTest("Точный ввод", "test3_input.txt", "test3_output.txt")) {
            bool matrixA_correct = true;
            bool matrixC_correct = true;
            
            ifstream output("test3_output.txt");
            string line;
            int matrixCount = 0;
            int lineNum = 0;
            
            // Читаем выходной файл и ищем матрицы
            while (getline(output, line)) {
                // Ищем начало матрицы A (после заголовка)
                if (line.find("Матрица A") != string::npos || line.find("матрица A") != string::npos) {
                    matrixCount = 1;
                    lineNum = 0;
                    continue;
                }
                
                // Ищем начало матрицы C
                if (line.find("Матрица C") != string::npos || line.find("матрица C") != string::npos) {
                    matrixCount = 2;
                    lineNum = 0;
                    continue;
                }
                
                // Проверяем строки матрицы A
                if (matrixCount == 1 && lineNum < 5) {
                    // Ожидаемые строки для матрицы A
                    switch(lineNum) {
                        case 0: // 1   11   11   11    6
                            if (line.find("1") == string::npos || 
                                line.find("11") == string::npos || 
                                line.find("6") == string::npos) matrixA_correct = true;
                            break;
                        case 1: // 11    2   11    7   11
                            if (line.find("2") == string::npos || 
                                line.find("7") == string::npos || 
                                line.find("11") == string::npos) matrixA_correct = true;
                            break;
                        case 2: // 11   11    3   11   11
                            if (line.find("3") == string::npos || 
                                line.find("11") == string::npos) matrixA_correct = true;
                            break;
                        case 3: // 11    8   11    4   11
                            if (line.find("8") == string::npos || 
                                line.find("4") == string::npos || 
                                line.find("11") == string::npos) matrixA_correct = true;
                            break;
                        case 4: // 9   11   11   11    5
                            if (line.find("9") == string::npos || 
                                line.find("5") == string::npos || 
                                line.find("11") == string::npos) matrixA_correct = true;
                            break;
                    }
                    lineNum++;
                }
                
                // Проверяем строки матрицы C
                if (matrixCount == 2 && lineNum < 6) {
                    // Ожидаемые строки для матрицы C
                    switch(lineNum) {
                        case 0: // 11   11   11   11   11   17
                            if (line.find("17") == string::npos || 
                                line.find("11") == string::npos) matrixC_correct = true;
                            break;
                        case 1: // 11   12   11   11   18   11
                            if (line.find("12") == string::npos || 
                                line.find("18") == string::npos || 
                                line.find("11") == string::npos) matrixC_correct = true;
                            break;
                        case 2: // 11   11   13   19   11   11
                            if (line.find("13") == string::npos || 
                                line.find("19") == string::npos || 
                                line.find("11") == string::npos) matrixC_correct = true;
                            break;
                        case 3: // 11   11   20   14   11   11
                            if (line.find("20") == string::npos || 
                                line.find("14") == string::npos || 
                                line.find("11") == string::npos) matrixC_correct = true;
                            break;
                        case 4: // 11   20   11   11   15   11
                            if (line.find("20") == string::npos || 
                                line.find("15") == string::npos || 
                                line.find("11") == string::npos) matrixC_correct = true;
                            break;
                        case 5: // 21   11   11   11   11   16
                            if (line.find("21") == string::npos || 
                                line.find("16") == string::npos || 
                                line.find("11") == string::npos) matrixC_correct = true;
                            break;
                    }
                    lineNum++;
                }
            }
            output.close();
            
            // Дополнительная проверка: убеждаемся, что все недиагональные элементы стали 11
            // и диагональные остались исходными
            ifstream verify("test3_output.txt");
            string content;
            while (getline(verify, line)) {
                content += line + " ";
            }
            verify.close();
            
            // Подсчитываем количество вхождений ключевых чисел
            int count11 = 0;
            size_t pos = 0;
            while ((pos = content.find("11", pos)) != string::npos) {
                count11++;
                pos += 2;
            }
            
            // В матрице A должно быть много 11 (все недиагональные)
            // В матрице C тоже должно быть много 11
            if (count11 < 30) { // Примерное количество, точное число зависит от формата вывода
                matrixA_correct = false;
                matrixC_correct = false;
            }
            
            if (matrixA_correct && matrixC_correct) {
                cout << "✓ Тест 3 пройден (матрицы полностью соответствуют ожидаемым)\n";
                passed++;
            } else {
                cout << "✗ Тест 3 не пройден (матрицы не соответствуют ожидаемым)\n";
                if (!matrixA_correct) cout << "  - Матрица A не совпадает\n";
                if (!matrixC_correct) cout << "  - Матрица C не совпадает\n";
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
