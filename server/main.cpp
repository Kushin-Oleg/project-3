#include "httplib.h"
#include "toolbox.h"

using namespace httplib;

int main(){
    Server server; //создание веб-сервера

    //прием secret для jwt токена
    server.Post("/getkey", get_secret);

    //создание пользователя
    server.Post("/create_user", reg_user_jwt);

    //авторизация через существующий аккаунт
    server.Post("/login_user", log_user_1);
    server.Post("/login_user_code", log_user_2);

    //создание листа to do
    server.Post("/to_do_create", to_do_create);

    //проверка новых листов to do и их отправка
    server.Post("/to_do_scan", to_do_scan);

    //помечается как завершенная задача
    server.Post("/to_do_is_complete", to_do_is_complite);

    //удаляем задачу
    server.Post("/del_to_do", to_do_del);

    //создаём расписание
    server.Post("create raspisanie", add_raspisanie);

    server.listen("localhost", 8090); //создание прослушиваемого порта веб-сервера
}