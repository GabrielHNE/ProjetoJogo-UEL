# Projeto-JOGO-em-C---UEL
Projeto de Téc. de Programação da UEL - Turma Ciência da Computação 2019. Desenvolvimento de jogo em C.


## README DO PROJETO

### JOGO - PACMAN EM C

#### Grupo formado pelos alunos:
- Gabriel H. N. Espindola;
- Henrique Tsuneda;
- Lucca Motta;
- João Gabriel;

#### PROPOSTA
 - Aplicar os conceitos de programação ministrados no primeiro semestre em diferentes ambientes dentro de um jogo.

#### FUNCIONAMENTO DO JOGO
O jogo a ser criado é baseado no famoso jogo PACMAN no qual o personagem principal tem como objetivo capturar todos os pontos
espalhados pelo mapa. Para dificultar o objetivo do jogador, existem 4 fantasmas que tentam "matar" o personagem principal
(jogador), entretanto existe um tipo de ponto que possibilita o jogador "matar" os fantasmas, mas após alguns segundos eles voltam.
Ao comer todos os pontos do mapa sem morrer mais do que 3 vezes o jogo é finalizado como vitória.

#### REGRAS, PONTUAÇÕES E PADRÕES
- **Geral**: 
	- 1 jogador
	- 1 nível;
	- 4 fantasmas;
	- Dimensão do mapa de 30x30 (não sei exatamente qual medida);
- **Caracteres para escrever o Mapa baseado em inteiros:**
	- 0 = "vazio" (Permitido andar mas nao contabiliza pontos);
	- 1 = * (Permitido andar e contabiliza pontos - 10pts); 
	- 2 = o (Super ponto - 50 pts + possibilidade de matar os fantasmas);
	- 3 = "teleporta para o outro lado";
	- 4 = "" canto inferior esquerdo (%c 200); //precisa alterar daqui para baixo
	- 5 = "|" vertical (%c 186);
	- 6 = "-" horizontal (%c 205);
	- 7 = "" canto superior direito (%c 187);
	- 8 = "" canto superior esquerdo (%c 201);
	- 9 = "" canto inferior direito (%c 188)
