#include "doctest.h"
#include "cooldown.hpp"

TEST_CASE("Testando a Classe Cooldown")
{
    Cooldown cd(2.0f); // 2 segundos de cooldown

    SUBCASE("Inicialização")
    {
        CHECK(cd.isCooldownUp());
        CHECK(cd.getRechargeTime() == doctest::Approx(2.0f * FPS));
    }

    SUBCASE("Iniciando e atualizando o cooldown")
    {
        cd.restartCooldown();
        CHECK_FALSE(cd.isCooldownUp());
        CHECK(cd.getCurrentTimeLeft() > 0);

        for (int i = 0; i < (2 * FPS); ++i)
        {
            cd.updateCooldown();
        }
        CHECK(cd.isCooldownUp());
    }

    SUBCASE("Reiniciar cooldown")
    {
        cd.restartCooldown();
        cd.refreshCooldown();
        CHECK(cd.isCooldownUp());
    }
}