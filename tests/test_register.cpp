#include "doctest.h"
#include "register.hpp"
#include <stdexcept>

TEST_CASE("Testando Funções de Validação")
{
    SUBCASE("validateNameChars")
    {
        CHECK_THROWS_AS(validateNameChars("Inválido!"), std::invalid_argument);
        CHECK_NOTHROW(validateNameChars("Nome Valido"));
    }

    SUBCASE("validateNicknameChars")
    {
        CHECK_THROWS_AS(validateNicknameChars("Inválido!"), std::invalid_argument);
        CHECK_NOTHROW(validateNicknameChars("nick_valido_123"));
    }

    SUBCASE("validateNameSize")
    {
        CHECK_THROWS_AS(validateNameSize("cur"), std::range_error);
        CHECK_THROWS_AS(validateNameSize("estenomeemuimuitolongoecomcertezavaiquebrar"), std::range_error);
        CHECK_NOTHROW(validateNameSize("NomeValido"));
    }

    SUBCASE("validateNicknameSize")
    {
        CHECK_THROWS_AS(validateNicknameSize("cur"), std::range_error);
        CHECK_THROWS_AS(validateNicknameSize("estenicknameemuimuitolongo"), std::range_error);
        CHECK_NOTHROW(validateNicknameSize("nick_valido"));
    }
}