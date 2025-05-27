import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'services/websocket_service.dart';
import 'services/theme_notifier.dart';
import 'screens/home_screen.dart';
import 'screens/scores_screen.dart';
import 'models/group_model.dart';

void main() {
  runApp(
    MultiProvider(
      providers: [
        ChangeNotifierProvider(create: (_) => WebSocketService()),
        ChangeNotifierProvider(create: (_) => ThemeNotifier()),
        ChangeNotifierProvider(create: (context) => GroupModel()),
      ],
      child: const MyApp(),
    ),
  );
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    final themeNotifier = Provider.of<ThemeNotifier>(context);

    return MaterialApp(
      title: 'Ciblerie',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primarySwatch: Colors.blue,
        brightness: Brightness.light,
        appBarTheme: const AppBarTheme(
          backgroundColor: Colors.white,
          foregroundColor: Colors.black87,
        ),
      ),
      darkTheme: ThemeData(
        brightness: Brightness.dark,
        appBarTheme: const AppBarTheme(
          backgroundColor: Color(0xFF1E1E1E),
          foregroundColor: Colors.white,
        ),
      ),
      themeMode: themeNotifier.themeMode,
      home: const HomeScreen(),
      routes: {
        '/scores': (context) => const ScoresScreen(), // ← Route vers ScoresScreen
      },
    );
  }
}
