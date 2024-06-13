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

class serv{
private:
    std::string ip;                         //переменная для хранения айпи
    std::string secret;                     //переменная для хранения ключа jwt токена

    //структура для платформы пользователя
    struct platform{
        std::string id;
        std::string login;
        std::string password;
    };

    //структура самого пользователя
    struct user{
        std::string group;
        std::string name;
        std::string role;
        platform pl;
    };

public:
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

    static std::string rand_int(int length){
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

    //функция для создания jwt токена
    std::string jwt_generate() {
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
    void jwt_decode(std::string& token){
        try{
            auto verifier = jwt::verify()
                    .allow_algorithm(jwt::algorithm::hs256{ secret });
            auto decoded_token = jwt::decode(token);
            verifier.verify(decoded_token);

            //извлечение данных


            std::cout << "JWT токен успешно расшифрован";
        }
        catch (const jwt::error::token_verification_error& e){
            std::cerr << "Token verification failed: " << e << std::endl;
        }
    }

    static void add_raspisanie(){
        parsing();
    }

    static auto register_user(const std::string& email, std::string& password, const std::string& name, const std::string& login){
        // Регулярное выражение для проверки email                                              //
        const std::string emailRegex = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";     //
                                                                                                // Это все проверка на почту
        // Создаем объект регулярного выражения                                                 // что он написана нормально
        Poco::RegularExpression regex(emailRegex);                                       //
                                                                                                //
        // Проверяем, соответствует ли email регулярному выражению
        if (regex.match(email)){
            bsoncxx::document::value doc_value = document{}
            << "group" << "student"
            << "name" << name
            << "email" << email
            << "platform" << open_document
                    << "id" << rand_str(20)
                    << "login" << login
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
            return "Ваша почта введена не верно";
        }
    }

    static void login_user(const std::string& email){
        try {
            // Создаем фильтр для поиска документа по имени файла
            bsoncxx::document::value filter = document{}
                    << "email" << email // Условие поиска: поле "email" = email
                    << finalize;

            // Выполняем запрос к коллекции
            mongocxx::stdx::optional<bsoncxx::document::value> result = collection_user.find_one(filter.view());

            // Проверяем, найден ли документ (т.е. существует ли файл)
            if(static_cast<bool>(result)) { // Возвращаем true, если файл найден, иначе false
                std::string confirmationCode = rand_int(6);

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

    void del_user(){

    }

    void change_user(){

    }

    
};