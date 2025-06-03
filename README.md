# Sobre o projeto

## Responsabilidades

### Back-end

- Modelagem (todos)
  - Makefile (Mateus)
- Registro e Leaderboard (Pedro Augusto)
- Base do jogo (Renato)

### Front-end

- Arte (Renato e Rafael)
- Interface (Cauã)

### Manutenção e colaboração

- Revisão (Cauã)
- Documentação
  - Geral (Mateus)
  - Gerada automaticamente pelo Doxygen
- Testes (todos)

## Ferramentas utilizadas

- C++
- Cartões CRC
- Doctest
- Doxygen
- Git e GitHub
- LaTeX
- Makefile

## Estrutura de arquivos

- assets: recursos utilizados pelo programa como imagens, sprites, fontes etc.
- bin: executáveis gerados pela compilação, criados durante a compilação pelo Makefile.
- include: arquivos de cabeçalho (`.hpp`) do projeto.
- obj: arquivos objeto (`.o`) criados durante a compilação.
- src: arquivos de código-fonte (`.cpp`).
- tests: arquivos de teste para validação do código.
- .gitignore: arquivos e pastas que o Git deve ignorar.
- Makefile: instruções para automatizar a compilação do projeto.

## Padronização e convenções

- Idiomas
  - Inglês: código, comentários e mensagens de commit.
  - Português: README e documentação geral.
- Cases
  - camelCase: variáveis
  - PascalCase: classes, construtores, arquivos "`.cpp`" (exceto `main`) e "`.hpp`"
- Mensagens de commit
  - Prefixos
    - feat: nova funcionalidade.
    - fix: correção de bug.
    - docs: alterações na documentação.
    - style: mudanças de formatação e estilo do código, sem alterações de lógica.
    - refactor: refatoração do código.
    - test: adição ou alteração de testes.
  - Mensagem
    - `<tipo>: <resumo breve>` (até 50 caracteres)
      - Caso o resumo ultrapasse 50 caracteres.
        - `<tipo>: <resumo breve>`
          - `<descrição detalhada>`
    - Utilize verbos no infinito e no presente.
      - add, update etc.
    - Caso tenha dificuldade com inglês, digite em português e posteriormente o commit será refatorado.
  - Exemplos
    - `feat: add hitbox implementation for obstacles`
    - `fix: leaderboard counting logic`
      - `'Leaderboard was counting the score twice...'`
