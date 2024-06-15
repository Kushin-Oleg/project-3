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
#include <Poco/Net/SecureSMTPClientSession.h> // Используем SecureSMTPClientSession для TLS
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/SharedPtr.h>
#include <Poco/RegularExpression.h>
#include <Poco/Net/Context.h>
#include <Poco/AutoPtr.h>
#include <Poco/Exception.h>

#include "MultipartParser.h"

#include <string>
#include <fstream>
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
auto collection_to_do_complited = database["to do complited"];
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

int generate_unique_random(const std::vector<int>& existing_numbers) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99999999);

    int random_number;
    do {
        random_number = dis(gen);
    } while (std::find(existing_numbers.begin(), existing_numbers.end(), random_number) != existing_numbers.end());

    return random_number;
}

std::string confirmationCode = rand_int(6);

//прием secret по post запросу
void get_secret(const httplib::Request& req, httplib::Response& res){
    secret_glob = req.has_param("SECRET") ? secret_glob = req.get_param_value("SECRET") : "not";
    std::cout << "jwt secret: " << secret_glob << "\n";
    res.set_content("secret poluchen", "text/plain");
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
        std::string data4 = "to do scan";
        std::string data5 = "to do complete";
        std::string data6 = "to do del";

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
            std::string deadline = decoded_token.get_payload_claim("deadline").as_string();
            std::string predmet = decoded_token.get_payload_claim("predmet").as_string();
            std::string opisanie = decoded_token.get_payload_claim("opisanie").as_string();
            std::string data = decoded_token.get_payload_claim("data").as_string();
            std::string teacher = decoded_token.get_payload_claim("teacher").as_string();
            std::string group = decoded_token.get_payload_claim("group").as_string();
            std::string isCompleted = decoded_token.get_payload_claim("isCompleted").as_string();

            std::vector<std::string> vecd {name, deadline, predmet, opisanie, data, teacher, group, isCompleted};

            return vecd;
        }

        if(data4 == decoded_token.get_payload_claim("command").as_string()){
            std::string group = decoded_token.get_payload_claim("group").as_string();

            std::vector<std::string> data {group};

            return data;
        }

        if(data5 == decoded_token.get_payload_claim("command").as_string()){
            std::string userId = decoded_token.get_payload_claim("userId").as_string();
            std::string to_do_id = decoded_token.get_payload_claim("to_do_id").as_string();
            std::string isCompleted = decoded_token.get_payload_claim("isCompleted").as_string();

            std::vector<std::string> data {userId, to_do_id, isCompleted};

            return data;
        }

        if(data6 == decoded_token.get_payload_claim("command").as_string()){
            std::string to_do_id = decoded_token.get_payload_claim("to_do_id").as_string();

            std::vector<std::string> data {to_do_id};

            return data;
        }

        std::cout << "JWT токен успешно расшифрован";
    }
    catch (const jwt::error::token_verification_error& e){
        std::cerr << "Token verification failed: " << e << std::endl;
    }
    return std::vector<std::string>{};
}

void register_user(const std::string& email, std::string& password){
    try {
        // Регулярное выражение для проверки email
        const std::string emailRegex = "^[a-zA-Z0-9]+@[a-zA-Z0-9]+\\.[a-zA-Z]{2,}$";
        Poco::RegularExpression regex(emailRegex);
        std::cout << "Регулярное выражение успешно создано\n";

        // Проверяем, соответствует ли email регулярному выражению
        if (regex.match(email)) {
            std::cout << "Email прошел проверку регулярным выражением\n";
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
        } else {
            std::cout << "Ваша почта введена не верно";
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка регулярного выражения: " << e.what() << std::endl;
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


void login_user(const std::string& email, const std::string& password) {
    try {
        // Создаем фильтр для поиска документа по email и паролю
        bsoncxx::builder::stream::document filter_builder;
        filter_builder << "email" << email << "password" << password;
        bsoncxx::document::value filter = filter_builder << bsoncxx::builder::stream::finalize;

        // Выполняем запрос к коллекции
        mongocxx::stdx::optional<bsoncxx::document::value> result = collection_user.find_one(filter.view());

        // Проверяем, найден ли документ
        if (result) {
            // Создаем и настраиваем сообщение электронной почты
            Poco::Net::MailMessage message;
            message.setSender("your_email@gmail.com");
            message.addRecipient(Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT, email));
            message.setSubject("Подтверждение регистрации");
            message.setContent("Ваш код подтверждения: " + confirmationCode);

            // Устанавливаем сессию для отправки письма
            Poco::Net::SecureSMTPClientSession session("smtp.mail.ru", 465);
            session.login(Poco::Net::SMTPClientSession::AUTH_LOGIN, "tr_sda@mail.ru", "server_sender");

            // Создание TLS-соединения
            Poco::AutoPtr<Poco::Net::Context> pContext = new Poco::Net::Context(
                    Poco::Net::Context::CLIENT_USE, "", "", "", // режим клиента
                    Poco::Net::Context::VERIFY_NONE, 9,
                    false, // принимаем любой сертификат (ненадёжно, но и так сойдет :) )
                    "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
            );
            Poco::Net::SSLManager::instance().initializeClient(nullptr, nullptr, pContext);

            // Запуск TLS с использованием контекста
            session.startTLS(pContext);
            session.sendMessage(message); // отправка письма

            std::cout << "Письмо отправлено (для повторной авторизации)!" << std::endl;
        } else {
            std::cout << "Неправильный email или пароль." << std::endl;
        }
    } catch (const Poco::Exception& exc) {
        std::cerr << "Ошибка отправки письма: " << exc.displayText() << std::endl;
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

    std::vector<int> existing_numbers;
    auto cursor = collection_to_do.find({});
    for (auto&& doc : cursor) {
        if (doc["to_do_id"]) {
            existing_numbers.push_back(doc["to_do_id"].get_int32());
        }
    }

    bsoncxx::document::value doc_value = document{}
            << "to_do_id" << generate_unique_random(existing_numbers)
            << "name" << data[0]
            << "deadline" << data[1]
            << "predmet" << data[2]
            << "opisanie" << data[3]
            << "data" << data[4]
            << "teacher" << data[5]
            << "group" << data[6]
            << "isCompleted" << data[7]
            << finalize;

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = collection_to_do.insert_one(doc_value.view());

    res.set_content("to do created", "text/plain");
}

void to_do_scan(const httplib::Request& req, httplib::Response& res){
    std::string jwt = req.has_param("JWT") ? req.get_param_value("JWT") : ""; //проверка на присутствие данных на JWT

    std::vector<std::string> data = jwt_decode(jwt);

    bsoncxx::builder::stream::document filter_builder;
    filter_builder << "group" << data[0];

    auto cursor = collection_to_do.find(filter_builder.view());

    std::vector<std::string> jsonArray;

    for (auto&& doc : cursor) {
        // Преобразование BSON документа в JSON строку
        std::string json_doc = bsoncxx::to_json(doc);
        // Добавление JSON строки в массив
        jsonArray.push_back(json_doc);
    }

    // Преобразование массива JSON строк в один JSON массив
    std::string json_array = "[";
    for (size_t i = 0; i < jsonArray.size(); ++i) {
        json_array += jsonArray[i];
        if (i < jsonArray.size() - 1) {
            json_array += ",";
        }
    }
    json_array += "]";

    res.set_content(json_array, "application/json");
}

void to_do_is_complite(const httplib::Request& req, httplib::Response& res){
    std::string jwt = req.has_param("JWT") ? req.get_param_value("JWT") : ""; //проверка на присутствие данных на JWT

    std::vector<std::string> data = jwt_decode(jwt);

    bsoncxx::document::value doc_value = document{}
            << "userId" << data[0]
            << "to_do_id" << data[1]
            << "isCompleted" << data[2]
            << finalize;

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = collection_to_do_complited.insert_one(doc_value.view());

    res.set_content("to do completed", "text/plain");
}

void to_do_del(const httplib::Request& req, httplib::Response& res){
    std::string jwt = req.has_param("JWT") ? req.get_param_value("JWT") : ""; //проверка на присутствие данных на JWT

    std::vector<std::string> data = jwt_decode(jwt);

    bsoncxx::builder::stream::document filter_builder;
    filter_builder << "to_do_id" << data[0];

    auto result1 = collection_to_do.delete_one(filter_builder.view());
    auto result2 = collection_to_do_complited.delete_one(filter_builder.view());

    if (result1) {
        std::cout << "Deleted " << result1->deleted_count() << " document(s)" << std::endl;
    } else {
        std::cout << "No documents matched the filter." << std::endl;
    }

    if (result2) {
        std::cout << "Deleted " << result2->deleted_count() << " document(s)" << std::endl;
    } else {
        std::cout << "No documents matched the filter." << std::endl;
    }

    res.set_content("to do deleted", "text/plain");
}

void add_raspisanie(const httplib::Request& req, httplib::Response& res){
    auto file = req.get_file_value("file");
    if (!file.content.empty()) {
        // Сохраняем содержимое файла
        std::ofstream outfile("rasp/", std::ios::binary);
        outfile.write(file.content.data(), file.content.size());
        outfile.close();
    } else {
        res.set_content("Failed to receive file", "text/plain");
    }

    parsing();





    res.set_content("raspisanie created", "text/plain");
}