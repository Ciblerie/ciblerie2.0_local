import 'package:flutter/material.dart';

class GroupModel with ChangeNotifier {
  String _selectedGroup = 'A'; // Groupe sélectionné par défaut

  String get selectedGroup => _selectedGroup;

  void setSelectedGroup(String group) {
    _selectedGroup = group;
    notifyListeners(); // Notifie les écouteurs du changement
  }
}
