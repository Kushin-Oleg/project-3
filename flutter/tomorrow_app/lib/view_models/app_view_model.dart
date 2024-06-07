import 'package:flutter/material.dart';

import '../models/task_models.dart';
import '../models/user_model.dart';

class AppViewModel extends ChangeNotifier {
  List<Task> tasks = <Task>[];
  User user = User("Gay Power");
}
