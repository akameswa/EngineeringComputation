#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    vector<string> lunch = {
        "Pizza from Mineo's",
        "Tofu Tikka Masala from Prince of India",
        "Crispy Salmon Roll from Sushi Fuku",
        "Sub from Uncle Sam's",
        "Fried rice from How Lee",
        "Sandwiches from La Prima",
        "Find free food on campus"
    };

    srand(time(nullptr));

    for (int i = 0; i < lunch.size(); ++i) {
        int j = rand() % lunch.size();
        swap(lunch[i], lunch[j]);
    }

    const char* days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    for (int i = 0; i < 7; ++i) {
        cout << days[i] << " " << lunch[i] << endl;
    }

    return 0;
}