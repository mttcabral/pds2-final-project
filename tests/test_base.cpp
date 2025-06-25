#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "base.hpp"
#include <vector>

TEST_CASE("Testando a Classe Profile")
{
    Profile p1("John Doe", "johnd", 100, 5);
    Profile p2("Jane Doe", "janed");
    Profile p3;

    SUBCASE("Construtores")
    {
        CHECK(p1.getName() == "John Doe");
        CHECK(p1.getNickname() == "johnd");
        CHECK(p1.getMaxDistance() == 100);
        CHECK(p1.getPlays() == 5);

        CHECK(p2.getName() == "Jane Doe");
        CHECK(p2.getNickname() == "janed");
        CHECK(p2.getMaxDistance() == 0);
        CHECK(p2.getPlays() == 1);

        CHECK(p3.getName() == "");
        CHECK(p3.getNickname() == "");
        CHECK(p3.getMaxDistance() == 0);
        CHECK(p3.getPlays() == 0);
    }

    SUBCASE("Setters")
    {
        p3.setPlays(10);
        p3.setMaxDistance(200);
        CHECK(p3.getPlays() == 10);
        CHECK(p3.getMaxDistance() == 200);

        // setMaxDistance só deve atualizar se a nova distância for maior
        p3.setMaxDistance(150);
        CHECK(p3.getMaxDistance() == 200);
    }

    SUBCASE("Operadores")
    {
        Profile p4("John Doe", "johnd", 200, 5);
        Profile p5("Outra Pessoa", "johnd", 100, 1);
        CHECK(p1 < p4);
        CHECK(p4 > p1);
        CHECK(p1 == p5);
    }
}

TEST_CASE("Testando a Classe Base")
{
    Base b;
    Profile p1("Jogador Um", "p1", 1000, 10);
    Profile p2("Jogador Dois", "p2", 2000, 20);
    Profile p3("Jogador Tres", "p3", 500, 5);

    SUBCASE("Adicionando e encontrando perfis")
    {
        CHECK(b.updateProfiles(p1));
        CHECK(b.inBase("p1"));
        CHECK(b.inBase(p1));
        CHECK_FALSE(b.inBase("p2"));

        CHECK(b.updateProfiles(p2));
        CHECK(b.inBase("p2"));
    }

    SUBCASE("Atualizando perfis existentes")
    {
        b.updateProfiles(p1);
        Profile p1_atualizado("Jogador Um", "p1", 1200, 1);
        b.updateProfiles(p1_atualizado);

        b.saveBase("test_base.csv");
        Base b_recarregado("test_base.csv");
        CHECK(b_recarregado.inBase("p1"));
    }

    SUBCASE("Removendo perfis")
    {
        b.updateProfiles(p1);
        b.updateProfiles(p2);
        CHECK(b.removeProfile("p1"));
        CHECK_FALSE(b.inBase("p1"));
        CHECK(b.inBase("p2"));
        CHECK_FALSE(b.removeProfile("perfil_inexistente"));
    }

    SUBCASE("Obtendo os melhores perfis")
    {
        b.updateProfiles(p1);
        b.updateProfiles(p2);
        b.updateProfiles(p3);

        std::vector<Profile *> melhores_perfis = b.getBestProfiles();
        CHECK(melhores_perfis.size() == 3);
        CHECK(melhores_perfis[0]->getNickname() == "p2");
        CHECK(melhores_perfis[1]->getNickname() == "p1");
        CHECK(melhores_perfis[2]->getNickname() == "p3");

        for (Profile *p : melhores_perfis)
        {
            delete p;
        }
    }
}