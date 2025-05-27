import 'package:flutter/material.dart';

/// Gère les tailles dynamiques selon la largeur d’écran.

double getGradeIconSize(BuildContext context) {
  final width = MediaQuery.of(context).size.width;
  if (width < 400) return 150;       // 📱 petit smartphone
  if (width < 800) return 200;       // 📲 tablette / moyen écran
  return 240;                        // 🖥️ grand écran
}

double getFontSizeResponsive(BuildContext context) {
  final width = MediaQuery.of(context).size.width;
  if (width < 400) return 14;
  if (width < 800) return 16;
  return 18;
}

double getTitleFontSizeResponsive(BuildContext context) {
  final width = MediaQuery.of(context).size.width;
  if (width < 400) return 18;
  if (width < 800) return 22;
  return 26;
}

double getButtonWidth(BuildContext context) {
  final width = MediaQuery.of(context).size.width;
  if (width < 400) return 120;
  if (width < 800) return 160;
  return 200;
}

double getPaddingResponsive(BuildContext context) {
  final width = MediaQuery.of(context).size.width;
  if (width < 400) return 8;
  if (width < 800) return 12;
  return 16;
}

/// Exemple : espacement vertical dynamique
double getVerticalSpacing(BuildContext context) {
  final width = MediaQuery.of(context).size.width;
  if (width < 400) return 10;
  if (width < 800) return 14;
  return 20;
}
