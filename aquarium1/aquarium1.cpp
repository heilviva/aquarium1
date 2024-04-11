#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Fish {
public:
    string type;
    int size;
    int stepsToDie;
    int stepsToReproduce;

    Fish(string type, int size, int stepsToDie, int stepsToReproduce)
        : type(type), size(size), stepsToDie(stepsToDie), stepsToReproduce(stepsToReproduce) {}

    void eatAlgae() {
        cout << type << " Рыбка ест водоросли" << endl;
    }

    void reproduce() {
        cout << type << " Рыбка размножается" << endl;
    }

    void die() {
        cout << type << " Рыбка умерла" << endl;
    }
};

class Algae {
public:
    int quality;

    Algae(int quality) : quality(quality) {}

    void grow() {
        cout << "Водоросли растут" << endl;
        quality += 2; // Увеличиваем качество водорослей
    }

    void decrease() {
        if (quality > 0) {
            cout << "Водоросли уменьшаются" << endl;
            quality -= 1; // Уменьшаем качество водорослей
        }
        else {
            cout << "Водорослей больше нет" << endl;
        }
    }
};

class Aquarium {
public:
    vector<Fish> fishes;
    Algae algae;

    Aquarium(int algaeQuantity) : algae(algaeQuantity) {}

    void addFish(Fish fish) {
        fishes.push_back(fish);
    }

    void simulate(int steps) {
        for (int i = 0; i < steps; i++) {
            vector<int> toRemove;
            for (int j = 0; j < fishes.size(); j++) {
                Fish& fish = fishes[j];

                // Обработка смерти от старости или отсутствия водорослей
                if (fish.stepsToDie == 0 || (fish.type == "Prey" && algae.quality <= 0)) {
                    fish.die();
                    toRemove.push_back(j);
                    continue;
                }
                else {
                    fish.stepsToDie--;
                }

                // Размножение
                if (fish.stepsToReproduce == 0) {
                    fish.reproduce();
                    fishes.push_back(Fish(fish.type, fish.size, fish.stepsToDie, fish.stepsToReproduce));
                    fish.stepsToReproduce = fish.size; // Сброс счетчика размножения
                }
                else {
                    fish.stepsToReproduce--;
                }

                // Взаимодействие с водорослями
                if (fish.type == "Prey" && algae.quality > 0) {
                    algae.decrease();
                }
            }

            // Удаление съеденных или умерших рыб
            for (int idx = toRemove.size() - 1; idx >= 0; idx--) {
                fishes.erase(fishes.begin() + toRemove[idx]);
            }

            algae.grow(); // Водоросли растут после каждого шага
        }
    }

    void displayState() {
        cout << "Текущее состояние аквариума:" << endl;
        cout << "Количество рыбок: " << fishes.size() << endl;
        for (Fish& fish : fishes) {
            cout << "Тип рыбки: " << fish.type << ", Размер: " << fish.size << ", Шагов до смерти: " << fish.stepsToDie << ", Шагов до размножения: " << fish.stepsToReproduce << endl;
        }
        cout << "Количество водорослей: " << algae.quality << endl;
    }
};

int main() {
    int algaeQuantity, predatorSize, preySize;
    string predatorType, preyType;

    cout << "Введите количество водорослей в аквариуме: ";
    cin >> algaeQuantity;

    cout << "Введите тип и размер хищника: ";
    cin >> predatorType >> predatorSize;

    cout << "Введите тип и размер добычи: ";
    cin >> preyType >> preySize;

    Fish predator(predatorType, predatorSize, 2, 4);
    Fish prey(preyType, preySize, 3, 5);

    Aquarium aquarium(algaeQuantity);
    aquarium.addFish(predator);
    aquarium.addFish(prey);

    aquarium.displayState();
    aquarium.simulate(5);
}