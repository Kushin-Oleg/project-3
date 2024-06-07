import 'package:flutter/material.dart';

class Tasks extends StatelessWidget {
  const Tasks({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        body: SafeArea(
          bottom: false,
          child: Column(
            children: [
              // голова
              Expanded(flex: 1, child: Container(color: Colors.red)),

              //рот
              Expanded(flex: 1, child: Container(color: Colors.green)),

              //жопа
              Expanded(flex: 7, child: Container(color: Colors.blue)),
            ],
          ),
        ),
        floatingActionButton: Container(
          width: 50,
          height: 50,
          color: Colors.black,
        ));
  }
}
