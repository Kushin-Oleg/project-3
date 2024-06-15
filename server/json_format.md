# я принимаю jwt токены!!!


1)server.Post("/getkey", get_secret); получение кода
post -> ip:8090/getkey

я принимаю:
"SECRET" : <значение>

ответ сервера: "secret poluchen"

SECRET - это кодовое слово на котором будет основа шифрования данных которые ты мне отправляешь(jwt token)

я сохраняю у себя этот секрет и ты его тоже и шифруешь этим ключём все jwt токены

Эта хуета принимает голый пост запрос(да хуйня по безопасности)

2) server.Post("/create_user", reg_user_jwt); регистрация

я принимаю: json  стакими данными:

"command" : "create/login user" \
"email" : <значение> \
"password" : <значение>

ответ сервера: "user created"

3/4) server.Post("/login_user", log_user_1);
     server.Post("/login_user_code", log_user_2);

3) ты мне отправляешь json с такими данными:

"command" : "create/login user" \
"email" : <значение> \
"password" : <значение> 

ответ сервера: "message sent to user email"

4) ты мне отправляешь json с такими данными:

"command" : "get code" \
"code" : <значением>

ответ сервера: "user login" или "user not login"

5) server.Post("/to_do_create", to_do_create);

ты мне отправляешь json с такими данными:

"command" : "to do create" \
"userId" : ___ \
"name" : ___ \
"deadline" : ___ \
predmet" : ___ \
"opisanie" : ___    \
"data" : ___   \
"teacher" : ___     \
"group" : ___  \
"isCompleted" : ___

ответ сервера: "to do created"

6) server.Post("/to_do_scan", to_do_scan);

ты мне отправляешь json с такими данными:

"command" : "to do scan" \
"group" : <значение>

ответ сервера: json массив со всеми картачками по этой группе

7) server.Post("/to_do_is_complete", to_do_is_complite);

ты мне отправляешь json с такими данными:

"command" : "to do complete" \
"userId" : email \
"to_do_id" : <значение>
"isCompleted" :  <значение>

ответ сервера: "to do completed"

8) server.Post("/del_to_do", to_do_del);

ты мне отправляешь json с такими данными:

"command" : "to do del" \
"to_do_id" : <значение>

ответ сервера: "to do deleted"

`Примечание : удаление происходит сразу и карточки и to do complited`

9) в разработке


