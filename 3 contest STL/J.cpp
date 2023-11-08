#include <iostream>
#include <set>
#include <unordered_map>

struct Track {
  int p = 0;
  int id = 0;
};

struct Cmp {
  bool operator()(Track l, Track gr) const {
    return l.p > gr.p || (l.p == gr.p && l.id < gr.id);
  }
};

struct Time {
  int time = -100000;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::unordered_map<std::string, Time> user_time;
  std::unordered_map<int, int> scores;
  std::set<Track, Cmp> songs;
  std::string command, ip;
  int score = 0, current_time = 0, track_id = 0;
  Track track;
  track.p = 0;
  for (int i = 1; i < 100001; ++i) {
    track.id = i;
    songs.insert(track);
  }
  while (std::cin >> command) {
    if (command[0] == 'V') {
      std::cin >> ip >> track_id >> score >> current_time;
      if (current_time - user_time[ip].time < 600) {
        std::cout << scores[track_id] << "\n";
      } else {
        songs.extract({scores[track_id], track_id});
        scores[track_id] += score;
        std::cout << scores[track_id] << "\n";
        user_time[ip].time = current_time;
        songs.insert({scores[track_id], track_id});
      }
    }
    if (command[0] == 'G') {
      auto song = *songs.begin();
      std::cout << song.id << " " << song.p << "\n";
      songs.extract(song);
      songs.insert({-1, song.id});
      scores[song.id] = -1;
    }
    if (command[0] == 'E') {
      break;
    }
  }
  std::cout << "OK\n";
  return 0;
}