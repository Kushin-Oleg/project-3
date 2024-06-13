#ifndef SERVER_TOOLBOX_H
#define SERVER_TOOLBOX_H
#endif  //SERVER_TOOLBOX_H

#include "httplib.h"

#include "jwt-cpp/jwt.h"

#include "nlohmann/json.hpp"

#include "mongocxx/instance.hpp"
#include "mongocxx/client.hpp"
#include "mongocxx/uri.hpp"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include "parsing.h"

#include "xlnt/xlnt.hpp"

#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SecureSMTPClientSession.h> // Используем SecureSMTPClientSession для TLS
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/SharedPtr.h>
#include <Poco/RegularExpression.h>

#include <chrono>
#include <random>
#include <iostream>
#include <vector>
#include <map>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

/////////////////////////////////
mongocxx::instance inst{};                                      //пинициализируем mongodb в коде
mongocxx::uri uri("mongodb://localhost:27017");         //подключаем mongodb к коду по URL ссылке
mongocxx::client client(uri);                        //создаём клиентскую часть

auto database = client["server"];                     //подключаемся к определённой базе данных
auto collection_rasp = database["raspisanie"];             //подключаемся к коллекции raspisanie
auto collection_user = database["user"];                   //подключаемя к коллекции user
auto collection_to_do = database["to do"];                 //подключаемя к коллекции to do
/////////////////////////////////


std::string secret_glob;                     //переменная для хранения ключа jwt токена

std::string code;

//структура для платформы пользователя
struct platform{
    std::string id;
    std::string email;
    std::string password;
};

//структура самого пользователя
struct user{
    std::string group;
    std::string role;
    platform pl;
};

//функция для создания случайной строки
static std::string rand_str(int length){
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string randomString;

    std::random_device random_gen;
    std::mt19937 gen(random_gen());
    std::uniform_int_distribution<> dis(0, chars.size());

    int char_i = dis(gen);
    for (int i = 0; i < length; i++) {
        randomString += chars[char_i];
    }
    return randomString;
}

std::string rand_int(int length){
    const std::string chars = "0123456789";
    std::string randomString;

    std::random_device random_gen;
    std::mt19937 gen(random_gen());
    std::uniform_int_distribution<> dis(0, chars.size());

    int char_i = dis(gen);
    for (int i = 0; i < length; i++) {
        randomString += chars[char_i];
    }
    return randomString;
}

std::string confirmationCode = rand_int(6);

//прием secret по post запросу
void get_secret(const httplib::Request& req, httplib::Response& res){
    secret_glob = req.has_param("SECRET") ? req.get_param_value("SECRET") : "";
    std::cout << "jwt secret: " << secret_glob << "\n";
}

//функция для создания jwt токена
std::string jwt_generate(std::string& secret) {
    try {
        auto payload = jwt::create()
                .set_type("JWT")
                .set_issuer("web-server")
                        //своё поставить
                .set_payload_claim("test", jwt::claim(std::string("sdadad")))

                .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds(long(60)));
        std::string token = payload.sign(jwt::algorithm::hs256{secret});

        std::cout << "JWT токен успешно сгенерирован";
        return token;
    }
    catch (const std::exception& e){
        std::cerr << "Ошибка при создании JWT: " << e.what() << std::endl;
        return "";
    }
}

//функция для расшифровки jwt токена
auto jwt_decode(std::string& token){
    try{
        auto verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{ secret_glob });

        auto decoded_token = jwt::decode(token);
        verifier.verify(decoded_token);

        std::string data1 = "create/login user";
        std::string data2 = "get code";
        std::string data3 = "to do create";

        //извлечение данных
        if(data1 == decoded_token.get_payload_claim("command").as_string()){
            std::string email = decoded_token.get_payload_claim("email").as_string();
            std::string password = decoded_token.get_payload_claim("password").as_string();

            std::vector<std::string> data {email, password};

            return data;
        }

        if(data2 == decoded_token.get_payload_claim("command").as_string()){
            code = decoded_token.get_payload_claim("code").as_string();
        }

        if(data3 == decoded_token.get_payload_claim("command").as_string()){
            std::string name = decoded_token.get_payload_claim("name").as_string();
            std::string deadline = decoded_token.get_payload_claim("predmet").as_string();
            std::string predmet = decoded_token.get_payload_claim("predmet").as_string();
            std::string opisanie = decoded_token.get_payload_claim("opisanie").as_string();
            std::string time = decoded_token.get_payload_claim("time").as_string();
            std::string sozdatel = decoded_token.get_payload_claim("sozdatel").as_string();

            std::vector<std::string> data {name, deadline, predmet, opisanie, time, sozdatel};

            return data;
        }

        std::cout << "JWT токен успешно расшифрован";
    }
    catch (const jwt::error::token_verification_error& e){
        std::cerr << "Token verification failed: " << e << std::endl;
    }
}

void add_raspisanie(){
    parsing();
}

void register_user(const std::string& email, std::string& password){
    // Регулярное выражение для проверки email                                              //
    const std::string emailRegex = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";     //
                                                                                            // Это все проверка на почту
    // Создаем объект регулярного выражения                                                 // что она написана нормально
    Poco::RegularExpression regex(emailRegex);                                       //
                                                                                            //
    // Проверяем, соответствует ли email регулярному выражению
    if (regex.match(email)){
        bsoncxx::document::value doc_value = document{}
                << "group" << "student"
                << "email" << email
                << "platform" << open_document
                    << "id" << rand_str(20)
                    << "password" << password
                << close_document
                << finalize;

        // Вставка документа в коллекцию
        bsoncxx::stdx::optional<mongocxx::result::insert_one> result = collection_user.insert_one(doc_value.view());

        if (result) {
            // Извлечение inserted_id как bsoncxx::oid
            bsoncxx::oid inserted_id = result->inserted_id().get_oid().value;

            std::cout << "Документ добавлен в коллекцию с ID: " << inserted_id.to_string() << std::endl;
        } else {
            std::cout << "Ошибка вставки документа в коллекцию" << std::endl;
        }
    }
    else {
        std::cout << "Ваша почта введена не верно";
    }
}

void reg_user_jwt(const httplib::Request& req, httplib::Response& res){
    std::string jwt = req.has_param("JWT") ? req.get_param_value("JWT") : ""; //проверка на присутствие данных на JWT

    std::vector<std::string> data = jwt_decode(jwt);

    std::string email = data[0];
    std::string password = data[1];

    register_user(email, password);

    res.set_content("user created" , "text/plain");
}


void login_user(const std::string& email, const std::string& password){
    try {
        // Создаем фильтр для поиска документа по имени файла
        bsoncxx::document::value filter = document{}
                << "email" << email // Условие поиска: поле "email" = email
                << "password" << password
                << finalize;

        // Выполняем запрос к коллекции
        mongocxx::stdx::optional<bsoncxx::document::value> result = collection_user.find_one(filter.view());

        // Проверяем, найден ли документ (т.е. существует ли файл)
        if(static_cast<bool>(result)) { // Возвращаем true, если файл найден, иначе false

            Poco::Net::MailMessage message;  //создаём электронное письмо
            message.setSender(
                    "your_email@gmail.com"); // почта с которой будет отправлен пользователю код подтверждения
            message.addRecipient(Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT, email));
            message.setSubject("Подтверждение регистрации"); //тема отправляемого сообщения
            message.setContent("Ваш код подтверждения: " + confirmationCode); // код подтверждения

            Poco::Net::SecureSMTPClientSession session("smtp.gmail.com", 587); //сессия отправки письма
            session.login(Poco::Net::SMTPClientSession::AUTH_LOGIN, "your_email@gmail.com",
                          "your_password"); // аутентификация почты-отправителя

            // Создание TLS-соединения
            Poco::AutoPtr<Poco::Net::Context> pContext = new Poco::Net::Context(
                    Poco::Net::Context::CLIENT_USE, "", "", "", // находимся в режиме клиента
                    Poco::Net::Context::VERIFY_NONE, 9,
                    false, // принимаем любой сертификат (ненадёжно но и так сойдет :) )
                    "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH" //виды сертификатов?
            );
            Poco::Net::SSLManager::instance().initializeClient(nullptr, nullptr, pContext);

            // Запуск TLS с использованием контекста
            session.startTLS(pContext);

            session.sendMessage(message); //отправка письма с кодом

            std::cout << "письмо отправлено(для повторной авторизации)!"
                      << std::endl; //уведоиление об успешной отправке письма
        }
    }
    catch (const Poco::Exception& exc) {
        std::cerr << "ошибка отправки письма: " << exc.displayText() << std::endl;
    }
}

void log_user_1(const httplib::Request& req, httplib::Response& res){
    std::string jwt = req.has_param("JWT") ? req.get_param_value("JWT") : ""; //проверка на присутствие данных на JWT

    std::vector<std::string> data = jwt_decode(jwt);

    std::string email = data[0];
    std::string password = data[1];

    login_user(email, password);
    res.set_content("message sent to user email" , "text/plain");
}

void log_user_2(const httplib::Request& req, httplib::Response& res){
    std::string jwt = req.has_param("JWT") ? req.get_param_value("JWT") : ""; //проверка на присутствие данных на JWT

    jwt_decode(jwt);

    if (code == confirmationCode){
        res.set_content("user login", "text/plain");
    }
    else {
        res.set_content("user not login", "text/plain");
    }
}

void del_user(){

}

void to_do_create(const httplib::Request& req, httplib::Response& res){
    std::string jwt = req.has_param("JWT") ? req.get_param_value("JWT") : ""; //проверка на присутствие данных на JWT

    std::vector<std::string> data = jwt_decode(jwt);

    bsoncxx::document::value doc_value = document{}
            << "name" << data[0]
            << "deadline" << data[1]
            << "predmet" << data[2]
            << "opisanie" << data[3]
            << "time" << data[4]
            << "sozdatel" << data[5]
            << finalize;

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = collection_to_do.insert_one(doc_value.view());
}

void to_do_scan(){
    
}
