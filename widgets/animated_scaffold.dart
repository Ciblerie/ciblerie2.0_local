import 'package:flutter/material.dart';

class AnimatedScaffold extends StatefulWidget {
  final PreferredSizeWidget? appBar;
  final Widget child;
  final Color? backgroundColor;
  final Widget? floatingActionButton;

  const AnimatedScaffold({
    super.key,
    this.appBar,
    required this.child,
    this.backgroundColor,
    this.floatingActionButton,
  });

  @override
  State<AnimatedScaffold> createState() => _AnimatedScaffoldState();
}

class _AnimatedScaffoldState extends State<AnimatedScaffold> with TickerProviderStateMixin {
  late AnimationController _controller;
  late Animation<double> _fadeAnimation;
  late Animation<double> _scaleAnimation;

  @override
  void initState() {
    super.initState();
    _controller = AnimationController(
      duration: const Duration(milliseconds: 600),
      vsync: this,
    );

    _fadeAnimation = Tween<double>(begin: 0, end: 1).animate(
      CurvedAnimation(parent: _controller, curve: Curves.easeOut),
    );

    _scaleAnimation = Tween<double>(begin: 0.8, end: 1).animate(
      CurvedAnimation(parent: _controller, curve: Curves.easeOut),
    );

    _controller.forward();
  }

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: widget.appBar,
      backgroundColor: widget.backgroundColor,
      floatingActionButton: widget.floatingActionButton,
      body: SafeArea(
        child: FadeTransition(
          opacity: _fadeAnimation,
          child: ScaleTransition(
            scale: _scaleAnimation,
            child: widget.child,
          ),
        ),
      ),
    );
  }
}
