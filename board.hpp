#include <algorithm>
#include <array>
#include <cassert>
#include <random>
#include <string>
#include <vector>

const int height = 6;
const int width = 5;
const int init_height = 2;

const double init_two_rate = 0.4;
const double two_rate = 0.2;
const double three_rate = 0.05;

class Board {
  std::array<std::array<int,width>,height> board;
  std::mt19937 rnd;
  int score, next, steps;
  bool status;
  void next_gen() {
    int max_piece = 0;
    for (auto &ary: board)
      max_piece = std::max(max_piece, *std::max_element(begin(ary), end(ary)));
    double x = std::uniform_real_distribution<>(0.0, 1.0)(rnd);
    if (max_piece <= 2)
      next = 1;
    else if (x < three_rate)
      next = std::uniform_int_distribution<>(2, max_piece - 1)(rnd);
    else if (x < two_rate)
      next = 2;
    else
      next = 1;
  }
  void push(std::vector<int> cand) {
    int pos = cand[std::uniform_int_distribution<>(0, (int)cand.size() - 1)(rnd)];
    for (int i = height - 2; i >= 0; --i)
      board[i+1][pos] = board[i][pos];
    board[0][pos] = next;
    next_gen();
  }
public:
  Board() : rnd(std::random_device()()), score(0), next(0), steps(0), status(true) {
    for (int i = 0; i < height; ++i)
      for (int j = 0; j < width; ++j)
        board[i][j] = 0;
    std::uniform_real_distribution<> unif(0.0, 1.0);
    for (int i = 0; i < init_height; ++i)
      for (int j = 0; j < width; ++j)
        board[i][j] = (unif(rnd) < init_two_rate) + 1;
    next_gen();
  }
  std::string to_json() {
    std::string res = "{\"status\":" + std::to_string((int)status) + ",[";
    for (int i = 0; i < height - 1; ++i) {
      res += "[";
      for (int j = 0; j < width; ++j)
        res += std::to_string(board[i][j]) + (j == width - 1 ? "]" : ",");
      res += (i == height - 2 ? "]," : ",");
    }
    res += "\"score\":" + std::to_string(score) + ",";
    res += "\"next\":" + std::to_string(next) + "}\n";
    return res;
  }
  void output() {
    printf("=== #%d ===\n", steps);
    printf("Score : %d\n", score);
    printf("Next : %d\n", next);
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j)
        if (i < height - 1 || board[i][j] > 0) printf("%2d ", board[i][j]);
        else printf("   ");
      puts("");
    }
    puts("");
  }
  bool play(int detach, int attach) {
    assert (status);
    ++steps;
    int num = -1, combo = 1;
    for (int i = height - 1; i >= 0; --i) {
      if (board[i][detach] != 0) {
        num = board[i][detach];
        board[i][detach] = 0;
        break;
      }
    }
    if (num == -1) return false;
    for (int i = height - 2; i >= 0; --i) {
      if (board[i][attach] == 0) {
        if (i == 0) board[0][attach] = num;
        continue;
      }
      if (board[i][attach] != num) {
        board[i+1][attach] = num;
        break;
      }
      board[i][attach] = 0;
      score += combo * num;
      ++num; combo *= 2;
    }
    std::vector<int> cand;
    for (int i = 0; i < width; ++i)
      if (board[height-1][i] == 0 && i != attach) cand.push_back(i);
    if (cand.empty()) {
      for (int i = 0; i < width; ++i)
        if (i != attach) cand.push_back(i);
    }
    push(cand);
    for (int i = 0; i < width; ++i)
      if (board[height-1][i] != 0) { status = false; return false; }
    return true;
  }
  int final_score() {
    int res = score;
    for (int i = 0; i < height; ++i)
      for (int j = 0; j < width; ++j)
        res += board[i][j] * (6 - i);
    return res;
  }
};
