# so_long

<p align="center">
  <img src="https://img.shields.io/badge/42-Porto-blue" alt="42 Porto"/>
  <img src="https://img.shields.io/badge/Norma-inge--pushswap-lightgrey" alt="Norminette"/>
  <img src="https://img.shields.io/badge/Language-C-00599C" alt="C"/>
  <img src="https://img.shields.io/badge/Graphics-MinilibX-orange" alt="MiniLibX"/>
</p>

## 📖 Sobre o projeto

**so_long** é um projeto da 42 Porto que introduz a programação gráfica em C, através da biblioteca **MinilibX**. O objetivo é criar um pequeno jogo 2D onde o jogador se move num mapa, recolhe todos os coletáveis e alcança a saída, com o menor número de movimentos possível.

Este projeto trabalha:

- **Parsing e validação de mapas** (ficheiros `.ber`)
- **Estruturas de dados** para representar o mapa e o estado do jogo
- **Gestão de memória** (nada de leaks, sobretudo em janelas/imagens)
- Primeiro contacto com **gráficos e eventos** (MinilibX / X11)

---

## 🎮 Regras do jogo

- O mapa é definido num ficheiro de texto com extensão **`.ber`**.
- Componentes obrigatórios do mapa:

| Símbolo | Significado |
|---------|-------------|
| `0` | Chão (espaço livre) |
| `1` | Parede |
| `P` | Posição inicial do jogador (exatamente 1) |
| `C` | Coletável (pelo menos 1) |
| `E` | Saída (exatamente 1) |

- O mapa deve estar **rodeado de paredes** (`1`) em todo o perímetro.
- O mapa deve ser **retangular** (todas as linhas com o mesmo comprimento).
- Tem de existir um **caminho válido** do jogador até todos os coletáveis e até à saída (flood fill).
- Se o mapa for inválido, o programa deve terminar com uma mensagem de erro clara, **sem crashar**.

### Objetivo do jogador

1. Mover-se pelo mapa (`W`, `A`, `S`, `D` ou setas, conforme implementação).
2. Apanhar **todos os coletáveis**.
3. Chegar à **saída** só depois de recolher todos os coletáveis.
4. Fechar a janela (`ESC` ou botão de fechar) deve terminar o programa **sem leaks**.

### Contador de movimentos

A cada tecla de movimento válida pressionada, o número de movimentos deve ser incrementado e impresso no terminal (`printf` no `stdout`).

---

## ⚙️ Compilação

```bash
make
```

O `Makefile` deve conter, no mínimo, as regras `all`, `clean`, `fclean` e `re`, e compilar (ou usar) a MinilibX corretamente.

---

## ▶️ Utilização

```bash
./so_long maps/map.ber
```

Exemplo de mapa válido (`map.ber`):

```
1111111111
10000000C1
1011111101
100C0000E1
10111P1101
1111111111
```

---

## 🧠 Arquitetura sugerida

1. **Parsing** — ler o ficheiro `.ber`, validar extensão e conteúdo linha a linha.
2. **Validação do mapa**:
   - retangularidade
   - paredes no perímetro
   - exatamente 1 `P` e 1 `E`
   - pelo menos 1 `C`
   - apenas caracteres válidos
   - conectividade via **flood fill** (algoritmo recursivo ou com pilha/fila) desde `P` até todos os `C` e a `E`
3. **Inicialização gráfica** — abrir janela MinilibX, carregar texturas (chão, parede, jogador, coletável, saída).
4. **Render do mapa** — desenhar cada tile na posição correta.
5. **Loop de eventos**:
   - `mlx_hook` / `mlx_key_hook` para movimento
   - `mlx_hook` para fechar janela (`X`) e tecla `ESC`
   - atualizar posição do jogador, verificar colisões com paredes
   - verificar recolha de coletáveis e condição de vitória
6. **Cleanup** — libertar todas as imagens, dados do mapa e destruir janela/display ao sair (`mlx_destroy_image`, `mlx_destroy_window`, `mlx_destroy_display`, `free`).

---

## 📁 Estrutura sugerida do projeto

```
so_long/
├── Makefile
├── README.md
├── maps/
│   ├── map.ber
│   └── map_invalid.ber
├── textures/
│   ├── wall.xpm
│   ├── floor.xpm
│   ├── player.xpm
│   ├── collectible.xpm
│   └── exit.xpm
├── includes/
│   └── so_long.h
├── src/
│   ├── main.c
│   ├── parsing.c
│   ├── map_validation.c
│   ├── flood_fill.c
│   ├── render.c
│   ├── events.c
│   └── cleanup.c
├── minilibx/       # ou dependência do sistema
└── libft/          # (se usada)
```

---

## 🧪 Testes recomendados

- Mapa válido pequeno, médio e grande.
- Mapa sem paredes no perímetro.
- Mapa sem jogador / com mais de um jogador.
- Mapa sem saída / com mais de uma saída.
- Mapa sem coletáveis.
- Mapa não retangular.
- Mapa com caracteres inválidos.
- Coletável ou saída **inacessível** (testar flood fill).
- Fechar a janela com `ESC` e com o botão de fechar (X).
- Verificar leaks com `valgrind`:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./so_long maps/map.ber
```

> ⚠️ A MinilibX/X11 pode gerar "leaks" residuais da própria biblioteca — normalmente aceites pela avaliação, desde que não sejam leaks do teu código.

## 📜 Licença

Projeto realizado no âmbito do currículo da 42 Porto, para fins educativos.
