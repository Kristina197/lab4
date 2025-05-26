#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Функция для определения победителя по методу Борда (с учетом ничьей)
string bordaWinner(const vector<string>& candidates, const vector<vector<string>>& votes) {
    map<string, int> scores;
    
    // Инициализация счетчиков для всех кандидатов
    for (const auto& candidate : candidates) {
        scores[candidate] = 0;
    }
    
    int n = candidates.size();
    
    // Подсчет баллов для каждого кандидата
    for (const auto& vote : votes) {
        for (int position = 0; position < vote.size(); ++position) {
            string candidate = vote[position];
            scores[candidate] += (n - 1 - position);
        }
    }
    
    // Вывод баллов для наглядности
    cout << "Баллы по методу Борда:\n";
    for (const auto& [candidate, score] : scores) {
        cout << candidate << ": " << score << " баллов\n";
    }
    
    // Поиск максимального количества баллов
    int maxScore = -1;
    for (const auto& [candidate, score] : scores) {
        if (score > maxScore) {
            maxScore = score;
        }
    }
    
    // Сбор всех кандидатов с максимальным количеством баллов
    vector<string> winners;
    for (const auto& [candidate, score] : scores) {
        if (score == maxScore) {
            winners.push_back(candidate);
        }
    }
    
    // Если несколько победителей - объявляем ничью
    if (winners.size() > 1) {
        string result = "Ничья";
        return result;
    }
    
    // Иначе возвращаем единственного победителя
    return winners[0];
}

// Функция для определения победителя по методу Кондорсе
string condorcetWinner(const vector<string>& candidates, const vector<vector<string>>& votes) {
    int nVoters = votes.size();
    
    for (const auto& candidate : candidates) {
        bool beatsAll = true;
        
        for (const auto& opponent : candidates) {
            if (candidate == opponent) continue;
            
            // Подсчет, сколько избирателей предпочитают candidate над opponent
            int preferred = 0;
            for (const auto& vote : votes) {
                auto candPos = find(vote.begin(), vote.end(), candidate) - vote.begin();
                auto oppPos = find(vote.begin(), vote.end(), opponent) - vote.begin();
                
                if (candPos < oppPos) {
                    preferred++;
                }
            }
            
            if (preferred <= nVoters / 2) {
                beatsAll = false;
                break;
            }
        }
        
        if (beatsAll) {
            return candidate;
        }
    }
    
    return "Нет победителя";
}

void runTest(const string& testName, const vector<string>& candidates, const vector<vector<string>>& votes) {
    cout << "\nТест: " << testName << endl;
    cout << "Кандидаты: ";
    for (const auto& c : candidates) cout << c << " ";
    cout << "\nГолоса:\n";
    for (const auto& v : votes) {
        for (const auto& c : v) cout << c << " ";
        cout << "\n";
    }
    
    string bordaWin = bordaWinner(candidates, votes);
    string condorcetWin = condorcetWinner(candidates, votes);
    
    cout << "Победитель по методу Борда: " << bordaWin << endl;
    cout << "Победитель по методу Кондорсе: " << condorcetWin << endl;
    
    if (bordaWin != condorcetWin && condorcetWin != "Нет победителя") {
        cout << "Методы дали разные результаты - это возможно при определенных распределениях голосов" << endl;
    }
}

int main() {
    vector<string> candidates = {"Петя", "Вася", "Оля"};
    vector<string> twoCandidates = {"Петя", "Вася"};
    
    // Тест 1: Все избиратели имеют одинаковые предпочтения
    runTest("1. Единогласное голосование", 
            candidates, 
            {{"Петя", "Вася", "Оля"}, {"Петя", "Вася", "Оля"}, {"Петя", "Вася", "Оля"}});
    
    // Тест 2: Парадокс Кондорсе (нет победителя по Кондорсе)
    runTest("2. Ничья", 
            candidates, 
            {{"Петя", "Вася", "Оля"}, {"Вася", "Оля", "Петя"}, {"Оля", "Петя", "Вася"}});
    
    // Тест 3: Разные победители у методов
    runTest("3. Разные победители", 
            candidates, 
            {{"Петя", "Вася", "Оля"}, {"Петя", "Вася", "Оля"}, {"Петя", "Вася", "Оля"},{"Вася", "Оля","Петя"},{"Вася", "Оля","Петя"}});
    
    // Тест 4: Один избиратель
    runTest("4. Один избиратель", 
            candidates, 
            {{"Вася", "Петя", "Оля"}});
    
    // Тест 5: Два кандидата (с ничьей)
    runTest("5. Два кандидата (ничья)", 
            twoCandidates, 
            {{"Петя", "Вася"}, {"Вася", "Петя"}});
    
    return 0;
}