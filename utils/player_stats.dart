import 'package:hive/hive.dart';

@HiveType(typeId: 0)
class PlayerStats extends HiveObject {
  @HiveField(0)
  int gamesPlayed;

  @HiveField(1)
  int totalScore;

  @HiveField(2)
  int bestScore;

  @HiveField(3)
  String group;

  PlayerStats({
    this.gamesPlayed = 0,
    this.totalScore = 0,
    this.bestScore = 0,
    this.group = "A",
  });

  void update(int newScore) {
    gamesPlayed++;
    totalScore += newScore;
    if (newScore > bestScore) {
      bestScore = newScore;
    }
  }
}
