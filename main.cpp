#include <iostream>
#include <vector>
#include <string>

#define MOD(x, n) ((-1 % 2 < 0) ? ((x) % (n)) >= 0 ? ((x) % (n)) : (n) + ((x) % (n)) : ((x) % (n)))


using namespace std;

int x, y;
int currentlayer = 0;
int outputlayer = 1;
long int iterations;
int map[27][27][2];
void display(int currentlayer);
void tick();
void load();

int main() {
    cin >> x;
    cin >> y;
    cin >> iterations;

    load();
    for (long int j = 0; j < iterations; j++) {
        tick();
    }
    display(currentlayer);
    return 0;
}
void load(){
    string temp;
    for (size_t xpos = 0; xpos < x; xpos++)
    {
        cin >> temp;
        for (size_t i = 0; i < y; i++)
        {
            if (temp[i] == '-'){
                map[xpos + 1][i + 1][0] = 0;
            }
            else{
                map[xpos + 1][i + 1][0] = 1;
            }
        }
    }
    for (int i = 1; i < 26; i++){
        map[0][i][0] = map[x][i][0];
        map[i][0][0] = map[i][y][0];
        map[x + 1][i][0] = map[1][i][0];
        map[i][y + 1][0] = map[i][1][0];
    }
                                            // Copy Corners - Torus
    map[0][0][0] = map[x][y][0];
    map[x + 1][y + 1][0] = map[x][y][0];
    map[0][y + 1][0] = map[x][1][0];
    map[x + 1][0][0] = map[1][y][0];

}
int check(int xPos, int yPos, int layer) {
    int numAdj = 0;
    numAdj = map[xPos - 1][yPos - 1][layer] + map[xPos - 1][yPos + 1][layer] + map[xPos - 1][yPos][layer] + map[xPos][yPos - 1][layer] + map[xPos][yPos + 1][layer] + map[xPos + 1][yPos - 1][layer] + map[xPos + 1][yPos][layer] + map[xPos + 1][yPos + 1][layer];
    if (numAdj == 2)
    {
        return map[xPos][yPos][layer];
    }
    else if (numAdj == 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void tick() {
    for (int i = 1; i < 26; i++){
        map[0][i][currentlayer] = map[x][i][currentlayer];
        map[i][0][currentlayer] = map[i][y][currentlayer];
        map[x + 1][i][currentlayer] = map[1][i][currentlayer];
        map[i][y + 1][currentlayer] = map[i][1][currentlayer];
    }
    // Copy Corners - Torus
    map[0][0][currentlayer] = map[x][y][currentlayer];
    map[x + 1][y + 1][currentlayer] = map[x][y][currentlayer];
    map[0][y + 1][currentlayer] = map[x][1][currentlayer];
    map[x + 1][0][currentlayer] = map[1][y][currentlayer];

    for (size_t xpos = 1; xpos <= x; xpos++)
    {
        for (size_t i = 1; i <= y; i++)
        {
            map[xpos][i][outputlayer] = check(xpos, i, currentlayer);
        }
    }

    int temp = currentlayer;
    currentlayer = outputlayer;
    outputlayer = temp;
    //cout<<endl;
    //display(currentlayer);
    //system("Pause");
}

void display(int currentlayer) {
    for (size_t xpos = 1; xpos <= x; xpos++)
    {
        for (size_t i = 1; i <= y; i++)
        {
            if (map[xpos][i][currentlayer] == 0){
                cout << '-';
            }
            else{
                cout << '*';
            }
        }
        cout<<endl;
    }
}