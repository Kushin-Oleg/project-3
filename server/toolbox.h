#ifndef SERVER_TOOLBOX_H
#define SERVER_TOOLBOX_H
#endif //SERVER_TOOLBOX_H

#include "httplib.h"
#include "jwt-cpp/jwt.h"
#include "json.hpp"
#include <chrono>
#include <random>
#include <iostream>
#include <map>


class serv{
private:
    std::string ip;
    std::string secret;
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

    //функция для создания jwt токена
    std::string jwt_generate() {
        try {
            auto payload = jwt::create()
                    .set_type("JWT")
                    .set_issuer("web-server")
                    .set_payload_claim("test", jwt::claim(std::string("sdadad")))
                    .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds(long(60)));
            std::string token = payload.sign(jwt::algorithm::hs256{secret});
            return token;
        }
        catch (const std::exception& e){
            std::cerr << "Ошибка при создании JWT: " << e.what() << std::endl;
            return "";
        }
    }

    //функция для расшифровки jwt токена
    void jwt_decode(std::string token){
        try{
            auto verifier = jwt::verify()
                    .allow_algorithm(jwt::algorithm::hs256{ secret });
            auto decoded_token = jwt::decode(token);
            verifier.verify(decoded_token);

            //извлечение данных

        }
        catch (const jwt::error::token_verification_error& e){
            std::cerr << "Token verification failed: " << e << std::endl;
        }
    }





};