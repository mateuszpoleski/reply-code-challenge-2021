#include <bits/stdc++.h>
using namespace std;

int W;
int H;
int N;
int M;
int R;

struct Building
{
    int x;
    int y;
    float latency;
    float speed;
    float score;
    bool reached;
};

struct Antenna
{
    int x;
    int y;
    float range;
    float speed;
    int id;
};

vector<Building> buildings;
vector<Antenna> antennas;
vector<vector<int>> city;

void solution1()
{
    sort(buildings.begin(), buildings.end(), [](Building left, Building right) {
        return left.score > right.score;
    });
    //random_shuffle(buildings.begin(), buildings.end());
    sort(antennas.begin(), antennas.end(), [](Antenna left, Antenna right) {
        return left.speed + left.range > right.speed + right.range;
        // return left.range > right.range;
        // return left.speed > right.speed;
    });

    int j = 0;
    for (int i = 0; i < M; i++)
    {
        while (buildings[j].reached)
        {
            j++;
        }
        int x = buildings[j].x + (2 * (rand() % (int)floor(antennas[i].range)) - (int)floor(antennas[i].range));
        antennas[i].x = x;
        antennas[i].y = buildings[j].y;
        buildings[j].reached = true;
        for (int k = 0; k < N; k++)
        {
            if ((float)(std::abs(buildings[k].x - antennas[i].x) + std::abs(buildings[k].y - antennas[i].y)) <= 0.5 * antennas[i].range)
                buildings[k].reached = true;
        }
    }
    /*sort(antennas.begin(), antennas.end(), [](Antenna left, Antenna right) {
        return left.id < right.id;
    });*/
}

int antenna_score(int x, int y, int range)
{
    int row_start = max(x - range / 2, 0);
    int row_end = min(W, x + range / 2);
    int col_start = max(y - range / 2, 0);
    int col_end = min(H, y + range / 2);
    int score = 0;
    for (int i = row_start; i < row_end; i++)
    {
        for (int j = col_start; j < col_end; j++)
        {
            if (city[i][j] > -1 && !buildings[city[i][j]].reached && (float)(std::abs(buildings[city[i][j]].x - x) + std::abs(buildings[city[i][j]].y - y)) <= range)
            {
                score++;
            }
        }
    }
    /*for (auto building : buildings)
    {
        if (!building.reached && std::abs(building.x - x) + std::abs(building.y - y) < range)
            score++;
    }*/
    return score;
}
void reach_buildings(int x, int y, int range)
{

    int row_start = max(x - range / 2, 0);
    int row_end = min(W, x + range / 2);
    int col_start = max(y - range / 2, 0);
    int col_end = min(H, y + range / 2);
    for (int i = row_start; i < row_end; i++)
    {
        for (int j = col_start; j < col_end; j++)
        {
            if (city[i][j] > -1 && (float)(std::abs(buildings[city[i][j]].x - x) + std::abs(buildings[city[i][j]].y - y)) <= range)
                buildings[city[i][j]].reached = true;
        }
    }
}

void solution2()
{
    sort(antennas.begin(), antennas.end(), [](Antenna left, Antenna right) {
        return left.range > right.range;
    });
    for (int i = 0; i < M; i++)
    {
        if (i % 2 == 0)
            cerr << i << " " << antennas[i].range << endl;
        int best_score = -1;
        for (int j = 0; j < N; j++)
        {
            if (buildings[j].reached)
                continue;
            int curr_score = antenna_score(buildings[j].x, buildings[j].y, antennas[i].range);
            if (best_score < curr_score)
            {
                best_score = curr_score;
                antennas[i].x = buildings[j].x;
                antennas[i].y = buildings[j].y;
            }
            reach_buildings(antennas[i].x, antennas[i].y, antennas[i].range);
        }
    }
}

int main()
{
    srand(time(NULL));
    cin >> W >> H;
    cin >> N >> M >> R;
    buildings.resize(N);
    antennas.resize(M);
    city.resize(W, vector<int>(H, -1));
    for (int i = 0; i < N; i++)
    {
        cin >> buildings[i].x;
        cin >> buildings[i].y;
        cin >> buildings[i].latency;
        cin >> buildings[i].speed;
        buildings[i].reached = false;
        buildings[i].score = (float)(buildings[i].speed + buildings[i].latency) * ((float)rand() / (float)RAND_MAX);
        city[buildings[i].x][buildings[i].y] = i;
        // buildings[i].score = buildings[i].speed + buildings[i].latency;
    }

    for (int i = 0; i < M; i++)
    {
        cin >> antennas[i].range;
        antennas[i].id = i;
        cin >> antennas[i].speed;
        antennas[i].x = -1;
        antennas[i].y = -1;
    }

    solution2();

    int valid = 0;
    for (int i = 0; i < M; i++)
    {
        if (antennas[i].x > -1)
    }
    cout << M << endl;
    for (int i = 0; i < M; i++)
    {
        cout << antennas[i].id << " ";
        cout << antennas[i].x << " ";
        cout << antennas[i].y << endl;
    }
}
