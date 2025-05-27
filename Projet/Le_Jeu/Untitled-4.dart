// [Remplacer le ValueListenableBuilder existant par :]
ValueListenableBuilder<Map<int, String>>(
  valueListenable: ws.pseudonymsNotifier,
  builder: (context, pseudos, _) {
    return ValueListenableBuilder<Map<int, int>>(
      valueListenable: ws.scoresNotifier,
      builder: (context, scores, _) {
        return Column(
          children: [
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                _buildScoreCard('${pseudos[0]} : ${scores[0] ?? 0}', ...),
                SizedBox(width: spacing),
                _buildScoreCard('${pseudos[1]} : ${scores[1] ?? 0}', ...),
              ],
            ),
            SizedBox(height: spacing),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                _buildScoreCard('${pseudos[2]} : ${scores[2] ?? 0}', ...),
                SizedBox(width: spacing),
                _buildScoreCard('${pseudos[3]} : ${scores[3] ?? 0}', ...),
              ],
            ),
          ],
        );
      },
    );
  },
)
