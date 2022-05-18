#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "war_match.h"
#include "card.h"

struct _s_match {
  card card;
  war_match next;
};

war_match match_new(void) {
  war_match new = calloc(1, sizeof(struct _s_match));
  //tener cuidado con estos NULL, verificar si estan bien
  new->card = NULL;
  new->next = NULL;
  return new;
}

war_match match_add(war_match match, card c) {//me tengo que fijar el orden de las cartas, estoy agregando
  war_match add_m = calloc(1, sizeof(struct _s_match));
  add_m->card = c;
  add_m->next = match;
  match = add_m;
  return match;
}

unsigned int match_size(war_match match) {//calcula la cantidad de cartas 1 por jugador
  unsigned int counter = 0;
  war_match aux = match;
  while(aux != NULL){
    ++counter;
    aux = aux->next;
  }
  return counter-1;
}

unsigned int match_length(war_match match) {//calcula la cantidad de manos son dos cartas por mano, tener cuidado con div 2
  unsigned int counter = 0;
  if(is_match_correct(match) == true){
    if(match != NULL){
    war_match aux = match;
      while(aux != NULL){
        ++counter;
        aux = aux->next;
      }
    } 
  } 
  return counter/2;
}

bool is_match_correct(war_match match) {
  //tengo un problema aca
  if(match != NULL){
    bool start_fst = card_player(match->card) == 1;
    bool size_even = match_size(match) % 2 == 0;
    bool fst_one_next_snd = true;
    war_match aux = match;
    while(aux != NULL && fst_one_next_snd){
      if(card_player(aux->card) == 1 && aux->next->card != NULL){
        aux = aux->next;
        if(card_player(aux->card) != 2){
          fst_one_next_snd = false;
        }
      }else{
        fst_one_next_snd = false;
      }
    }
    return fst_one_next_snd && start_fst && size_even;
  } else{
    return true;
  }
}

static unsigned int player_score(war_match match, unsigned int player) {
  /*COMPLETAR:Calcula el puntaje de 'player' en el partido 'match'*/
  unsigned int player1 = 0;
  unsigned int player2 = 0;
  war_match aux = match;
  //Yo asumo que empieza el jugaro uno.
    while(aux != NULL){
      if(card_wins(aux->card, aux->next->card)){
        player1 += card_match_points(aux->card, aux->next->card); 
      }else{
        player2 += card_match_points(aux->card, aux->next->card);
      }
      aux = aux->next->next;
    }
    if(player == 1){
      return player1;
    }else{
      return player2;
    }
}

unsigned int winner_total_points(war_match match) {
 unsigned int total = 0;
 if(is_match_correct(match) == true){
   if(player_score(match, 1) >= player_score(match,2)){
     total = player_score(match,1);
   } else if(player_score(match, 1) < player_score(match, 2)){
     total = player_score(match, 2);
   }
 }
 return total;
}

card * match_to_array(war_match match) {
  war_match aux = match;
  unsigned int size = match_size(match);
  card * array = calloc(size, sizeof(card));
  for(unsigned int i = 0; aux != NULL; ++i){
    array[i] = aux->card;
    aux = aux->next;
  }
  return array;
}

void match_dump(war_match match) {
  card *array = match_to_array(match);
  for (unsigned int i=0u; i < match_size(match); i++) {
    card_dump(array[i]);
  }
  free(array);
}

war_match match_destroy(war_match match) {
  war_match aux;
  while(match != NULL){
    aux = match;
    match = match->next;
    card_destroy(aux->card);
    free(aux);
    aux = NULL;
  }
  return match;
}

/*static bool is_match_color_balanced(war_match match) {/
  assert(is_match_correct(match));
  unsigned int rojo = 0;
  unsigned int negros = 0;
  war_match aux = match;
  while(aux != NULL){
    if(card_suit(aux->fst_player)== "d" || card_suit(aux->fst_player) == "c"){
      ++rojo;
    } else{
      ++ negros;
    }
    aux = aux->next;
  }
  return rojo == negros;
}
*/