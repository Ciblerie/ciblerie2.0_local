class Grade {
  final int id;
  final String name;
  final int tier;
  final int stars;
  final int maxStars;
  final String icon;
  final int? promotionTo;
  final int? demotionTo;
  final String demotionRule;

  Grade({
    required this.id,
    required this.name,
    required this.tier,
    required this.stars,
    required this.maxStars,
    required this.icon,
    required this.promotionTo,
    required this.demotionTo,
    required this.demotionRule,
  });

  factory Grade.fromJson(Map<String, dynamic> json) {
    return Grade(
      id: json['id'],
      name: json['name'],
      tier: json['tier'],
      stars: json['stars'],
      maxStars: json['maxStars'],
      icon: json['icon'],
      promotionTo: json['promotionTo'],
      demotionTo: json['demotionTo'],
      demotionRule: json['demotionRule'],
    );
  }

  Map<String, dynamic> toJson() {
    return {
      'id': id,
      'name': name,
      'tier': tier,
      'stars': stars,
      'maxStars': maxStars,
      'icon': icon,
      'promotionTo': promotionTo,
      'demotionTo': demotionTo,
      'demotionRule': demotionRule,
    };
  }

  bool get isMaxed => promotionTo == null;
  bool get isFirst => demotionTo == null;
}
