#include <iostream>
#include <vector>

using namespace std;

struct knight {
    int r;
    int c;
    int h;
    int w;
    int k;
};

int L, N, Q;
int map[41][41];
int knight_map[41][41];
knight knights[31];
vector<int> health; 
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void input() {
    cin >> L >> N >> Q;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            cin >> map[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        int r, c, h, w, k;
        cin >> r >> c >> h >> w >> k;
        knight tmp = {r - 1, c - 1, h, w, k};
        knights[i] = tmp;
        health.push_back(k);

        for(int ii = r; ii < r + h; ii++) {
            for(int jj = c; jj < c + w; jj++) {
                knight_map[ii - 1][jj - 1] = i + 1;
            }
        }
    }
}

void move(int n, int d) {
    knight& cur = knights[n];
    if (d == 0) {
        for (int i = cur.c; i < cur.c + cur.w; i++) {
            knight_map[cur.r + cur.h - 1][i] = 0;
            knight_map[cur.r - 1][i] = n + 1;
        }
    }
    else if (d == 1) {
        for (int i = cur.r; i < cur.r + cur.h; i++) {
            knight_map[i][cur.c] = 0;
            knight_map[i][cur.c + cur.w - 1] = n + 1;
        }
    }
    else if (d == 2) {
        for (int i = cur.c; i < cur.c + cur.w; i++) {
            knight_map[cur.r][i] = 0;
            knight_map[cur.r + cur.h - 1][i] = n + 1;
        }
    }
    else {
        for (int i = cur.r; i < cur.r + cur.h; i++) {
            knight_map[i][cur.c + cur.w - 1] = 0;
            knight_map[i][cur.c - 1] = n + 1;
        }
    }
    cur.r += dx[d];
    cur.c += dy[d];
}

bool push(bool is_first, int n, int d) {
    knight& cur = knights[n];
    if (d == 0) {
        if(cur.r == 0) {
            return false;
        }
        
        for (int i = cur.c; i < cur.c + cur.w; i++) {
            if (knight_map[cur.r - 1][i] && knights[knight_map[cur.r - 1][i] - 1].k > 0) {
                if (!push(false, knight_map[cur.r - 1][i] - 1, d)){
                    return false;
                }
            }
            if (map[cur.c - 1][i] == 2) {
                    return false;
            }
        }
    }
    else if (d == 1) {
        if(cur.c + cur.w == L) {
            return false;
        }
        for (int i = cur.r; i < cur.r + cur.h; i++) {
            if (knight_map[i][cur.c + cur.w] && knights[knight_map[i][cur.c + cur.w] - 1].k > 0) {
                if (!push(false, knight_map[i][cur.c + cur.w] - 1, d)) {
                    return false;
                }
            }
            if (map[i][cur.c + cur.w] == 2) {
                    return false;
            }
        }
    }
    else if (d == 2) {
        if(cur.r + cur.h == L) {
            return false;
        }
        for (int i = cur.c; i < cur.c + cur.w; i++) {
            if (knight_map[cur.r + cur.h][i] && knights[knight_map[cur.r + cur.h][i] - 1].k > 0) {
                if (!push(false, knight_map[cur.r + cur.h][i] - 1, d)) {
                    return false;
                }
                
            }
            if (map[cur.r + cur.h][i] == 2) {
                    return false;
                }
        }
    }
    else {
        if(cur.c == 0) {
            return false;
        }
        for (int i = cur.r; i < cur.r + cur.h; i++) {
            if (knight_map[i][cur.c - 1] && knights[knight_map[i][cur.c - 1] - 1].k > 0) {
                if (!push(false, knight_map[i][cur.c - 1] - 1, d)) {
                    return false;
                }   
            }
            if (map[i][cur.c - 1] == 2) {
                    return false;
            }
        }
    }
    move(n, d);
    if (!is_first) {
        int bomb_cnt = 0;
        for (int i = cur.r; i < cur.r + cur.h; i++) {
            for(int j = cur.c; j < cur.c + cur.w; j++) {
                if(map[i][j] == 1)
                    bomb_cnt++;
            }
        }
        cur.k -= bomb_cnt;
    }
    return true;
}

void simulate() {
    for (int i = 0; i < Q; i++) {
        int index, d;
        cin >> index >> d;
        if(knights[index].k <= 0)
            continue;
        push(true, index, d);
    }
}

void result() {
    int ans = 0;
    for(int i = 0; i < N; i++) {
        if(knights[i].k > 0) {
            ans += health[i] - knights[i].k;
        }
    }
    cout<<ans;
}

int main() {
    input();
    simulate();
    result();
    return 0;
}