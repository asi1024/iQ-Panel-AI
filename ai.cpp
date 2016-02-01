#include <bits/stdc++.h>

using namespace std;

struct Board {
  array<array<int,5>,5> board;
  int status, score, next;
  Board(string json) {
    for (char &c: json)
      if (!isdigit(c)) c = ' ';
    istringstream is(json);
    is >> status;
    for (int i = 0; i < 5; ++i)
      for (int j = 0; j < 5; ++j)
        is >> board[i][j];
    is >> score >> next;
  }
};

int main() {
  string json;
  while (cin >> json) {
    Board board(json);
    if (board.status == 0) break;
    int detach = rand() % 5, attach = rand() % 5;
    cout << detach << " " << attach << endl;
  }
  return 0;
}
